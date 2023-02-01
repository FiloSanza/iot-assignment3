from flask import Flask, request
from flask_cors import CORS
import arduino_comm
from datetime import datetime
from consts import *
import threading
import time
import json

app = Flask(__name__)
CORS(app)
arduino = arduino_comm.SerialLine(port="/dev/ttyACM0", baudrate=9600, timeout=0.1)

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

def update_data():
    while True:
        serial_data = arduino.read()

        lock.acquire()
        for msg in serial_data:
            # The light state has been updated
            if LIGHT_STATE in msg and msg[LIGHT_STATE] != data[LIGHT_STATE]:
                data[LIGHT_LOGS].append({
                    'state': msg[LIGHT_STATE],
                    'ts': datetime.now()
                })
                data[LIGHT_STATE] = msg[LIGHT_STATE]
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

    if state != data[LIGHT_STATE]:
        data[LIGHT_LOGS].append({
            'state': state,
            'ts': datetime.now()
        })
        data[LIGHT_STATE] = state

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