#include "update_values.h"
#include "consts.h"
#include "types.h"
#include "serialization.h"

namespace Tasks {
    UpdateValues::UpdateValues(
        void (*mqtt_callback)(const char*),
        Components::Led* led, 
        Components::Pir* pir, 
        Components::LightSensor* light_sensor
    ) : mqtt_callback(mqtt_callback),
        led(led),
        pir(pir),
        light_sensor(light_sensor) {
        this->setPeriodAndRestartTimer(UPDATE_VALUES_PERIOD);
    }

    void UpdateValues::init() {}

    void UpdateValues::tick() {
        if (!this->canRun()) {
            return;
        }

        this->markExecutedNow();

        RoomReading value = {
            this->light_sensor->read(),
            this->pir->read()
        };

        if (value.pir) {
            this->led->turnOn();
        } else {
            this->led->turnOff();
        }

        String data = Serialize::Json::serialize(value);

        this->mqtt_callback(data.c_str());
    }
}