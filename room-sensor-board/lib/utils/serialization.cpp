#include "serialization.h"
#include <ArduinoJson.h>

namespace Serialize {
    String Json::serialize(const RoomReading& value) {
        DynamicJsonDocument json(128);

        String str;

        json["light"] = value.light;   
        json["pir"] = value.pir ? 1 : 0; 
        
        serializeJson(json, str);

        return str;
    }
}