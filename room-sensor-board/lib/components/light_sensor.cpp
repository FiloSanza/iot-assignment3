#include "light_sensor.h"
#include "consts.h"

namespace Components {
    LightSensor::LightSensor(pin_t pin)
        : pin(pin) {}

    float LightSensor::read() {
        int value = analogRead(pin);

        // Convert to lux
        float vout = (float(value)) * (VIN / 1023.0f);
        float resistance = (LIGHT_SENSOR_RESITOR * (VIN - vout)) / vout;
        float lux = 500.0 / (resistance / 1000.0);
        return lux;
    }
}