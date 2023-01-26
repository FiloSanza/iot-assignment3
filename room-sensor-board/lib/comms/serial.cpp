#include "serial.h"

#include "Arduino.h"

namespace Comms {
    void SerialRecv::send(const char* msg) const {
        Serial.println(msg);
    }
}