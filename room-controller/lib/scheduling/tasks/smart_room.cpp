#include "smart_room.h"
#include "logger.h"

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

        Logger::Message log_msg;

        lighting_subsystem->turnOn();
        log_msg.setTag(SmartRoomMessageTag::LightOff)
            .setDescription("Lightning subsystem update")
            .log();

        // if (MsgServiceBT.isMsgAvailable()) {
        //     Msg* msg = MsgServiceBT.receiveMsg();    
        //     updateRoom(msg);
        // }

        // if (MsgService.isMsgAvailable()) {
        //     Msg* msg = MsgService.receiveMsg();    
        //     updateRoom(msg);
        // }
    }

    void SmartRoom::updateRoom(Msg* msg) {
        Logger::Message log_msg;
        if (msg->getContent() == "movement"){
            roller_blinds->moveTo(SERVO_UPPER_BOUND);
        } else if (msg->getContent() == "light_on") {
            lighting_subsystem->turnOn();
            log_msg.setTag(SmartRoomMessageTag::LightOn)
                .setDescription("Lightning subsystem update")
                .log();
        } else if (msg->getContent() == "light_off") {
            lighting_subsystem->turnOff();
            log_msg.setTag(SmartRoomMessageTag::LightOff)
                .setDescription("Lightning subsystem update")
                .log();
        }
    }
    
}