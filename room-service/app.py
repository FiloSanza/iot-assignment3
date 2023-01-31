from flask import Flask, request
from flask_cors import CORS
import arduino_comm
import json
import db

app = Flask(__name__)
CORS(app)
database = db.InMemoryDB()
arduino = arduino_comm.SerialLine(port="/dev/ttyACM0", baudrate=9600, timeout=0.1)

@app.route('/get_logs', methods=['GET'])
def get_logs():
    database.write_all(arduino.read())
    return json.dumps(database.read(), default=lambda msg: msg.__dict__)

@app.route('/update_light', methods=['POST'])
def update_light():
    lvl = request.get_json()["light"]
    s = f'{{"light":{lvl}}}'
    arduino.write_byte(s)
    
    return s
    
@app.route('/update_servo', methods=['POST'])
def update_servo():
    angle = request.get_json()["angle"]
    s = f'{{"angle":{angle}}}'
    arduino.write_byte(s)

    return s