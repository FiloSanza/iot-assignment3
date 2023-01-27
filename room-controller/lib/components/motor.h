#ifndef __SERVO_H_INCLUDED
#define __SERVO_H_INCLUDED

#include <Arduino.h>
#include <Servo.h>
#include "types.h"

namespace Components {
    class Motor {
    public:
        Motor();
        Motor(pin_t pin);
        ~Motor();

        void moveTo(int angle);
        int read();
    private:
        Servo servo;
    };
}

#endif