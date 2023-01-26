#ifndef _RECEIVER_H_INCLUDED
#define _RECEIVER_H_INCLUDED

namespace Comms {
    class Receiver {
    public:
        virtual void send(const char* msg) = 0;
    };
}

#endif