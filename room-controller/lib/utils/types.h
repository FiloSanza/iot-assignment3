#ifndef _ENUMS_H_INCLUDED
#define _ENUMS_H_INCLUDED

#include <inttypes.h>
#include <Arduino.h>

typedef uint8_t pin_t;
typedef unsigned long timestamp_t;

enum SmartRoomMessageTag : uint32_t {
    Light = 0,
    Valve = 1
};

#endif