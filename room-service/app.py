from flask import Flask, request
from flask_cors import CORS
from flask_mqtt import Mqtt
import arduino_comm
from datetime import datetime
from consts import *
import threading
import time
import json

app = Flask(__name__)
CORS(app)
arduino = arduino_comm.SerialLine(port="/dev/ttyACM0", baudrate=9600, timeout=0.1)

app.config['MQTT_BROKER_URL'] = 'broker.hivemq.com'
app.config['MQTT_BROKER_PORT'] = 1883
app.config['MQTT_USERNAME'] = ''
app.config['MQTT_PASSWORD'] = ''
app.config['MQTT_KEEPALIVE'] = 5
app.config['MQTT_TLS_ENABLED'] = False

mqtt = Mqtt()

lock = threading.Lock()
data = {
    LIGHT_LOGS: [{
        'state': 0,
        'ts': datetime.now()
    }],
    PIR_STATE: 0,
    LIGHT_STATE: 0,
    ROLLERBLINDS_STATE: 0,
}


def update_light_state(state):
    if state != data[LIGHT_STATE]:
        data[LIGHT_LOGS].append({
            'state': state,
            'ts': datetime.now()
        })
        data[LIGHT_STATE] = state

@mqtt.on_connect()
def handle_connect(client, userdata, flags, rc):
    mqtt.subscribe('smart-room-drudi-sanzani')

@mqtt.on_message()
def handle_mqtt_message(client, userdata, message):
    topic, payload = message.topic, json.dumps(message.payload.decode())
    print(f"[{topic}]: {payload}")

    pir = payload.pir
    light_state = 1 if payload.pir and payload.light_level < LIGHT_THRESHOLD else 0
    
    lock.acquire()

    data[PIR_STATE] = pir

    # open if someone enters after 8
    if data[ROLLERBLINDS_STATE] == 0 and pir and datetime.hour >= 8:
        data[ROLLERBLINDS_STATE] = 100
        arduino.write_byte('{"angle":100}')

    if data[ROLLERBLINDS_STATE] > 0 and not pir and datetime.hour > 19:
        data[ROLLERBLINDS_STATE] = 0
        arduino.write_byte('{"angle":0}')

    update_light_state(light_state)

    lock.release()

def update_data():
    while True:
        serial_data = arduino.read()

        lock.acquire()
        for msg in serial_data:
            # The light state has been updated
            if LIGHT_STATE in msg:
                update_light_state(msg[LIGHT_STATE])
            # The rollerblind state changed
            elif ROLLERBLINDS_STATE in msg:
                data[ROLLERBLINDS_STATE] = msg[ROLLERBLINDS_STATE]
        lock.release()
        time.sleep(0.5)

serial_reads_thread = threading.Thread(target=update_data)
serial_reads_thread.start()

@app.route('/get_logs', methods=['GET'])
def get_logs():
    lock.acquire()
    response = json.dumps(data)
    lock.release()

    return response

@app.route('/update_light', methods=['POST'])
def update_light():
    lock.acquire()
    state = request.get_json()["light"]
    arduino.write_byte(f'{{"light":{state}}}')

    update_light_state(state)

    response = json.dumps(data)
    lock.release()
    
    return response
    
@app.route('/update_servo', methods=['POST'])
def update_servo():
    lock.acquire()
    angle = request.get_json()["angle"]
    arduino.write_byte(f'{{"angle":{angle}}}')
    data[ROLLERBLINDS_STATE] = angle

    response = json.dumps(data)
    lock.release()
    
    return response