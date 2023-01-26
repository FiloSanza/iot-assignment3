#ifndef __PIR_H_INCLUDED
#define __PIR_H_INCLUDED

#include <Arduino.h>
#include "component.h"
#include "types.h"

namespace Components {
    class Pir : public ReadableComponent<bool> {
    public:
        Pir();
        Pir(pin_t pin);

        bool read();
        timestamp_t getLastDetectedAt() const;

    private:
        pin_t pin;
        bool last_state;
        timestamp_t last_detected_at;
    };
}

#endif