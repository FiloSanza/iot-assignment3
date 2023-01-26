#ifndef _SERIAL_COMM_H_INCLUDED
#define _SERIAL_COMM_H_INCLUDED

#include "receiver.h"

namespace Comms {
    class SerialRecv : public Receiver {
    public:
        SerialRecv() {}

        void send(const char* msg) const;  
    };
}

#endif