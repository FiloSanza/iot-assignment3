#include "pir.h"

namespace Components
{
    Pir::Pir() {}
    Pir::Pir(pin_t pin) : pin(pin), last_state(false), last_detected_at(0) {}

    bool Pir::read() {
        bool value = digitalRead(pin) == HIGH;

        if (value) {
            last_detected_at = millis();
        }

        last_state = value;
        return value;
    }

    timestamp_t Pir::getLastDetectedAt() const {
        return last_detected_at;
    }
}