#ifndef _UPDATE_VALUES_H_INCLUDED
#define _UPDATE_VALUES_H_INCLUDED

#include "task.h"
#include "components.h"
#include "comm_pool.h"

namespace Tasks {
    class UpdateValues : public Scheduling::PeriodicTask {
    public:
        UpdateValues(Comms::CommPool* pool, Components::Pir* pir, Components::LightSensor* light_sensor);
        void init();
        void tick();
    private:
        Comms::CommPool* pool;

        Components::Pir* pir;
        Components::LightSensor* light_sensor;
    };
}

#endif