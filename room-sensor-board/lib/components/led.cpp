#include "led.h"

namespace Components
{
    Led::Led() {}
    Led::Led(pin_t pin) : pin(pin) {
        pinMode(pin, OUTPUT);
    }

    void Led::turnOn() {
        if (!is_on) {
            is_on = true;
            digitalWrite(pin, HIGH);
        }
    }

    void Led::turnOff() {
         if (is_on) {
            is_on = false;
            digitalWrite(pin, LOW);
        }
    }
 
    void Led::switchState() {
        if (is_on) {
            turnOff();
        } else {
            turnOn();
        }
    }

    bool Led::isOn() const {
        return is_on;
    }
}