#ifndef _SERIALIZATION_H_INCLUDED
#define _SERIALIZATION_H_INCLUDED

#include "types.h"

namespace Serialize {
    class Json {
    public:
        static String serialize(const RoomReading& value);
    };
}

#endif