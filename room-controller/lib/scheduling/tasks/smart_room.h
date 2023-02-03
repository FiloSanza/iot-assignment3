#ifndef __SMART_ROOM_H_INCLUDED
#define __SMART_ROOM_H_INCLUDED

#include <ArduinoJson.h>

#include "led.h"
#include "motor.h"
#include "consts.h"
#include "logger.h"
#include "MsgService.h"
#include "task.h"

namespace Tasks {

    class SmartRoom : public Scheduling::PeriodicTask {
    public:
        SmartRoom() = default;
        SmartRoom(
            Components::Led* lighting_subsystem,
            Components::Motor* roller_blinds,
            MsgServiceBT* msg_serviceBT,
            timestamp_t period
        );

        void init();
        void tick();
    private:
        Components::Led* lighting_subsystem;
        Components::Motor* roller_blinds;
        MsgServiceBT* msg_serviceBT;
        DynamicJsonDocument* doc;
        Logger::Message* log_msg;
        Msg* msg;

        void updateRoom(Logger::Message* log_msg, Msg* msg);
    };
}

#endif