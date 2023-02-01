from typing import List
import serial
import json

class SerialLine():
    def __init__(self, port, baudrate, timeout) -> None:
        self.arduino = serial.Serial(port=port, baudrate=baudrate, timeout=timeout)
    
    def write_byte(self, data: str):
        try:
            data += "\n"
            self.arduino.write(data.encode())
        except Exception:
            pass
    
    def read(self) -> List:
        msgs = []
        while True:
            line = ''
            try:
                line = self.arduino.read_until(b"\n").decode()[:-1]
            except Exception:
                pass
            
            if len(line) == 0:
                break

            try:
                msgs.append(json.loads(line))
            except Exception:
                # Need to handle "half lines"
                print(f"DESERIALIZER EXCEPTION: {line}")
                pass

        return msgs