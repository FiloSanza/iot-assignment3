from typing import List
import serial
from message import Message

class SerialLine():
    def __init__(self, port, baudrate, timeout) -> None:
        self.arduino = serial.Serial(port=port, baudrate=baudrate, timeout=timeout)
    
    def write_byte(self, data: int):
        try:
            self.arduino.write(bytes([data]))
        except Exception:
            pass
    
    def read(self) -> List[Message]:
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
                msgs.append(Message.from_json(line))
            except Exception:
                pass

        return msgs