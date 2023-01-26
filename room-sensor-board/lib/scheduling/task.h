#ifndef __TASK_H_INCLUDED
#define __TASK_H_INCLUDED

#include "types.h"

namespace Scheduling {
    class Task {
    public:
        bool isEnabled() const;
        void disable();
        void enable();

        virtual void init() = 0;
        virtual void tick() = 0;
    protected:
        bool is_enabled = true;
    };

    class PeriodicTask : public Task {
    public:
        bool canRun();
        void setPeriod(timestamp_t period);
        void markExecutedNow();
        void setPeriodAndRestartTimer(timestamp_t period);
    protected:
        timestamp_t last_execution;
        timestamp_t period;
    };
}

#endif