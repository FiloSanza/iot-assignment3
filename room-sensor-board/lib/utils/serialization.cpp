#include "serialization.h"
#include <ArduinoJson.h>

namespace Serialize {
    void Json::serialize(const RoomReading& value, char* output, size_t size) {
        DynamicJsonDocument json(128);

        json["light"] = value.light;   
        json["pir"] = value.pir ? 1 : 0; 
        
        serializeJson(json, output, size);
    }
}