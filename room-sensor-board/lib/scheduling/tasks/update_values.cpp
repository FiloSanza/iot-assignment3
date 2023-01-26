#include "update_values.h"
#include "consts.h"
#include "types.h"
#include "serialization.h"

namespace Tasks {
    UpdateValues::UpdateValues(
        Comms::CommPool* pool,
        Components::Pir* pir, 
        Components::LightSensor* light_sensor
    ) : pool(pool),
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

        char buffer[64];
        RoomReading value = {
            this->light_sensor->read(),
            this->pir->read()
        };

        if (value.pir) {
            this->led->turnOn();
        } else {
            this->led->turnOff();
        }

        Serialize::Json::serialize(value, buffer);

        this->pool->send(buffer);
    }
}