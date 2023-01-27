#include "motor.h"

namespace Components {
    Motor::Motor() {}
    Motor::Motor(pin_t pin) {
        servo.attach(pin);
    }

    Motor::~Motor() {
        servo.detach();
    }

    void Motor::moveTo(int angle) {
        servo.write(angle);
    }

    int Motor::read() {
        return servo.read();
    }
}