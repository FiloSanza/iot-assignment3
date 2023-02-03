#include "smart_room.h"
#include "logger.h"

namespace Tasks {
    SmartRoom::SmartRoom(
        Components::Led* lighting_subsystem,
        Components::Motor* roller_blinds,
        MsgServiceBT* msg_serviceBT,
        timestamp_t period
    ) : lighting_subsystem(lighting_subsystem),
        roller_blinds(roller_blinds),
        msg_serviceBT(msg_serviceBT) {
            doc = new DynamicJsonDocument(32);
            log_msg = new Logger::Message();
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
            msg = msg_serviceBT->receiveMsg(); 
            log_msg->setBt(1);   
            updateRoom(log_msg, msg);
        }

        if (MsgService.isMsgAvailable()) {
            msg = MsgService.receiveMsg();  
            log_msg->setBt(0);
            updateRoom(log_msg, msg);
        }
    }

    void SmartRoom::updateRoom(Logger::Message* log_msg, Msg* msg) {
        DeserializationError error = deserializeJson(*doc, msg->getContent());
        if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
        }

        if (doc->containsKey("light")) {
            if ((*doc)["light"] == 1) {
                lighting_subsystem->turnOn();
            } else {
                lighting_subsystem->turnOff();
            }
        } 
        if (doc->containsKey("angle")) {
            int angle =  map((*doc)["angle"], 0, 100, 0, 180);
            roller_blinds->moveTo(angle);
        }
        log_msg->setLight(lighting_subsystem->isOn() ? 1 : 0)
            .setAngle(roller_blinds->read())
            .log();
    }
    
}