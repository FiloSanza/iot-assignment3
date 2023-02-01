#ifndef _UPDATE_VALUES_H_INCLUDED
#define _UPDATE_VALUES_H_INCLUDED

#include "task.h"
#include "light_sensor.h"
#include "pir.h"
#include "led.h"

namespace Tasks {
    class UpdateValues : public Scheduling::PeriodicTask {
    public:
        UpdateValues(
            void (*mqtt_callback)(const char*), 
            Components::Led* led, 
            Components::Pir* pir, 
            Components::LightSensor* light_sensor
        );
        void init();
        void tick();
    private:
        void (*mqtt_callback)(const char*);

        Components::Led* led;
        Components::Pir* pir;
        Components::LightSensor* light_sensor;
    };
}

#endif