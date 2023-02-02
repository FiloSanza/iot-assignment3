#include "smart_room.h"
#include "logger.h"

#include <ArduinoJson.h>

namespace Tasks {
    SmartRoom::SmartRoom(
        Components::Led* lighting_subsystem,
        Components::Motor* roller_blinds,
        MsgServiceBT* msg_serviceBT,
        timestamp_t period
    ) : lighting_subsystem(lighting_subsystem),
        roller_blinds(roller_blinds),
        msg_serviceBT(msg_serviceBT) {
            setPeriodAndRestartTimer(period);
        }

    void SmartRoom::init() {
        msg_serviceBT->init();
        roller_blinds->moveTo(SERVO_LOWER_BOUND);
    }

    void SmartRoom::tick() {
        if (!canRun()) {
            return;
        }

        markExecutedNow();

        if (msg_serviceBT->isMsgAvailable()) {
            Msg* msg = msg_serviceBT->receiveMsg();    
            updateRoom(msg);
        }

        if (MsgService.isMsgAvailable()) {
            Msg* msg = MsgService.receiveMsg();  
            updateRoom(msg);
        }
    }

    void SmartRoom::updateRoom(Msg* msg) {
        Logger::Message log_msg;

        String json = msg->getContent();
        DynamicJsonDocument doc(32);
        DeserializationError error = deserializeJson(doc, json);
        if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
        }

        if (doc.containsKey("light")) {
            if (doc["light"] == 1) {
                lighting_subsystem->turnOn();
            } else {
                lighting_subsystem->turnOff();
            }
            log_msg.setTag(SmartRoomMessageTag::Light)
                .setData(doc["light"])
                .setDescription("Lightning subsystem update")
                .log();
        } else if (doc.containsKey("angle")) {
            roller_blinds->moveTo(doc["angle"]);
            log_msg.setTag(SmartRoomMessageTag::Valve)
                .setData(doc["angle"])
                .setDescription("Roller blinds update")
                .log();
        }
    }
    
}