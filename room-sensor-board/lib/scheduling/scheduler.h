#ifndef __SCHEDULER_H_INCLUDED
#define __SCHEDULER_H_INCLUDED

#include "consts.h"
#include "task.h"

namespace Scheduling {
    class Scheduler {
    public:
        Scheduler();

        /**
         * Schedule a job, returns true if there are available
         * slots for the new task, false otherwise. 
         */
        bool schedule(Task* task);
        void tick();
    private:
        uint16_t last_idx;
        Task* tasks[MAX_NUMBER_OF_TASKS];
    };
}

#endif