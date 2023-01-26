#include "comm_pool.h"

namespace Comms {
    void CommPool::addRecv(Receiver* recv) {
        if (this->last_idx < MAX_NUMBER_OF_COMMS) {
            this->pool[this->last_idx] = recv;
            this->last_idx++;
        }
    }

    void CommPool::send(const char* msg) {
        for (int i=0; i<this->last_idx; i++) {
            this->pool[i]->send(msg);
        }
    }
}