#ifndef __LED_H_INCLUDED
#define __LED_H_INCLUDED

#include <Arduino.h>
#include "types.h"

namespace Components {
    /**
     * On/Off led.
     */
    class Led {
    public:
        Led();
        Led(pin_t pin);

        void turnOn();
        void turnOff();
        void switchState();
        
        bool isOn() const; 

    protected:
        pin_t pin;
        bool is_on = false;
    };
}

#endif
