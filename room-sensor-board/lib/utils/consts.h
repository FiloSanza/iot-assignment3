#ifndef __CONSTS_H_INCLUDED
#define __CONSTS_H_INCLUDED

#include "types.h"

// Wifi
constexpr char* WIFI_SSID = "...";
constexpr char* WIFI_PASSWORD = "...";

// Light Sensor
constexpr int VIN = 5;
constexpr int LIGHT_SENSOR_RESITOR = 1000; // ms

// Scheduler
constexpr int MAX_NUMBER_OF_TASKS = 4;
constexpr int UPDATE_VALUES_PERIOD = 1000; // ms

// Pins
constexpr pin_t LED_PIN = 3; 
constexpr pin_t PIR_PIN = 4; 
constexpr pin_t LIGHT_SENSOR_PIN = 5; 

// Comm pool
constexpr int MAX_NUMBER_OF_COMMS = 4;

// MQTT
constexpr char* MQTT_SERVER = "...";
constexpr char* MQTT_TOPIC = "...";

#endif