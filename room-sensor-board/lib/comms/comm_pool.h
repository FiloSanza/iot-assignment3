#ifndef _COMM_POOL_H_INCLUDED
#define _COMM_POOL_H_INCLUDED

#include "receiver.h"
#include "consts.h"

namespace Comms {
    class CommPool : public Receiver {
    public:
        CommPool() : last_idx(0) {}

        void addRecv(Receiver* recv);
        void send(const char* msg);
    private:
        int last_idx;
        Receiver* pool[MAX_NUMBER_OF_COMMS];
    };
}

#endif