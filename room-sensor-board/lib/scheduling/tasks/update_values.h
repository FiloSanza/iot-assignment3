#ifndef _UPDATE_VALUES_H_INCLUDED
#define _UPDATE_VALUES_H_INCLUDED

#include "task.h"
#include "light_sensor.h"
#include "pir.h"
#include "led.h"
#include "comm_pool.h"

namespace Tasks {
    class UpdateValues : public Scheduling::PeriodicTask {
    public:
        UpdateValues(
            Comms::CommPool* pool, 
            Components::Led* led, 
            Components::Pir* pir, 
            Components::LightSensor* light_sensor
        );
        void init();
        void tick();
    private:
        Comms::CommPool* pool;

        Components::Led* led;
        Components::Pir* pir;
        Components::LightSensor* light_sensor;
    };
}

#endif