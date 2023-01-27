#include "smart_room.h"
#include "logger.h"

#include <ArduinoJson.h>

namespace Tasks {
    SmartRoom::SmartRoom(
        Components::Led* lighting_subsystem,
        Components::Motor* roller_blinds,
        timestamp_t period
    ) : lighting_subsystem(lighting_subsystem),
        roller_blinds(roller_blinds) {
            setPeriodAndRestartTimer(period);
        }

    void SmartRoom::init() {
        roller_blinds->moveTo(SERVO_LOWER_BOUND);
    }

    void SmartRoom::tick() {
        if (!canRun()) {
            return;
        }

        markExecutedNow();

        // if (MsgServiceBT.isMsgAvailable()) {
        //     Msg* msg = MsgServiceBT.receiveMsg();    
        //     updateRoom(msg);
        // }

        if (MsgService.isMsgAvailable()) {
            lighting_subsystem->turnOn();
            // Msg* msg = MsgService.receiveMsg();  
            // updateRoom(msg);
        }
    }

    void SmartRoom::updateRoom(Msg* msg) {
        Logger::Message log_msg;

        String json = msg->getContent();
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, json);

        if (doc.containsKey("light")) {
            if (doc["light"] == "1") {
                lighting_subsystem->turnOn();
                log_msg.setTag(SmartRoomMessageTag::LightOn);
            } else {
                lighting_subsystem->turnOff();
                log_msg.setTag(SmartRoomMessageTag::LightOff);
            }
            log_msg.setDescription("Lightning subsystem update").log();
        } else if (doc.containsKey("angle")) {
            lighting_subsystem->turnOff();
            log_msg.setTag(SmartRoomMessageTag::LightOff)
                .setDescription("Lightning subsystem update")
                .log();
        }
    }
    
}