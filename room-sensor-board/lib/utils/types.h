#ifndef _ENUMS_H_INCLUDED
#define _ENUMS_H_INCLUDED

#include <inttypes.h>
#include <Arduino.h>

typedef uint8_t pin_t;
typedef unsigned long timestamp_t;

struct RoomReading {
    float light;
    bool pir;
};

#endif