#ifndef __LIGHT_SENSOR_H_INCLUDED
#define __LIGHT_SENSOR_H_INCLUDED

#include <Arduino.h>
#include "component.h"
#include "types.h"

namespace Components {
    class LightSensor : public ReadableComponent<float> {
    public:
        LightSensor(pin_t pin);

        float read();

    private:
        pin_t pin;
    };
}

#endif