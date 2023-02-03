from flask import Flask, request
from flask_cors import CORS
from flask_mqtt import Mqtt
import arduino_comm
from datetime import datetime
from consts import *
import threading
import json
import time

arduino = arduino_comm.SerialLine(port="/dev/ttyACM0", baudrate=9600, timeout=0.1)

app = Flask(__name__)
CORS(app)

# Mqtt configuration
app.config['MQTT_BROKER_URL'] = 'broker.hivemq.com' # See https://mosquitto.org/
app.config['MQTT_BROKER_PORT'] = 1883
app.config['MQTT_KEEPALIVE'] = 5  # Set KeepAlive time in seconds
app.config['MQTT_TLS_ENABLED'] = False  # If your server supports TLS, set it True
topic = 'smart-room-098'
mqtt = Mqtt(app)

lock = threading.Lock()
data = {
    LIGHT_LOGS: [{
        'state': 0,
        'ts': datetime.now().strftime("%d/%m/%Y %H:%M:%S")
    }],
    PIR_STATE: 0,
    LIGHT_STATE: 0,
    ROLLERBLINDS_STATE: 0,
}
bt_last_message = None

def update_light_state(state):
    if state == data[LIGHT_STATE]:
        return False
        
    data[LIGHT_LOGS].append({
        'state': state,
        'ts': datetime.now().strftime("%d/%m/%Y %H:%M:%S")
    })
    data[LIGHT_STATE] = state
    
    return True

@mqtt.on_connect()
def handle_connect(client, userdata, flags, rc):
    print(topic)
    mqtt.subscribe(topic)

@mqtt.on_message()
def handle_mqtt_message(client, userdata, message):
    
    global bt_last_message
    
    payload = json.loads(message.payload.decode())
    
    lock.acquire()
    if bt_last_message != None and (datetime.now() - bt_last_message).total_seconds() < TIME_THRESHOLD:
        lock.release()
        return

    pir = payload['pir']
    light_state = 1 if payload['pir'] and payload['light'] < LIGHT_THRESHOLD else 0
    
    data[PIR_STATE] = pir
    
    changes = {}

    # open if someone enters after 8
    if data[ROLLERBLINDS_STATE] == 0 and pir and datetime.now().hour >= 8:
        data[ROLLERBLINDS_STATE] = 100
        changes['angle'] = 100

    if data[ROLLERBLINDS_STATE] > 0 and not pir and datetime.now().hour > 19:
        data[ROLLERBLINDS_STATE] = 0
        changes['angle'] = 0
    
    if update_light_state(light_state):
        changes['light'] = light_state

    lock.release()
    
    update = json.dumps(changes)
    arduino.write_byte(update)

def update_data():
    
    global bt_last_message
    
    while True:
        serial_data = arduino.read()
        print(serial_data)
        lock.acquire()
        for msg in serial_data:
            # The light state has been updated
            if LIGHT_STATE in msg:
                update_light_state(msg[LIGHT_STATE])
            # The rollerblind state changed
            if ROLLERBLINDS_STATE in msg:
                data[ROLLERBLINDS_STATE] = msg[ROLLERBLINDS_STATE]
            # Update bluetooth last message
            if BLUETOOTH in msg and msg[BLUETOOTH] == '1':
                bt_last_message = datetime.now()
            
        lock.release()
        time.sleep(0.5)

@app.route('/data', methods=['GET'])
def get_data():
    lock.acquire()
    response = json.dumps(data)
    lock.release()

    return response

@app.route('/light', methods=['POST'])
def update_light():
    lock.acquire()
    state = request.get_json()["light"]
    arduino.write_byte(f'{{"light":{state}}}')

    update_light_state(state)

    response = json.dumps(data)
    lock.release()
    
    return response
    
@app.route('/rollerblinds', methods=['POST'])
def update_rollerblinds():
    lock.acquire()
    angle = request.get_json()["value"]
    arduino.write_byte(f'{{"angle":{angle}}}')
    data[ROLLERBLINDS_STATE] = angle

    response = json.dumps(data)
    lock.release()
    
    return response

    
serial_reads_thread = threading.Thread(target=update_data)
serial_reads_thread.start()