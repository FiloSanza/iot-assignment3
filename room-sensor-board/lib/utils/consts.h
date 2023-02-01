#ifndef __CONSTS_H_INCLUDED
#define __CONSTS_H_INCLUDED

#include "types.h"

// Wifi
constexpr const char* WIFI_SSID = "Filippo's Iphone";
constexpr const char* WIFI_PASSWORD = "0123456789";

// Light Sensor
constexpr int VIN = 5;
constexpr int LIGHT_SENSOR_RESITOR = 1000; // ms

// Scheduler
constexpr int MAX_NUMBER_OF_TASKS = 4;
constexpr int UPDATE_VALUES_PERIOD = 1000; // ms

// Pins
constexpr pin_t LED_PIN = 1; 
constexpr pin_t PIR_PIN = 0; 
constexpr pin_t LIGHT_SENSOR_PIN = A0; 

// Comm pool
constexpr int MAX_NUMBER_OF_COMMS = 4;

// MQTT
constexpr const char* MQTT_SERVER = "172.20.10.7:1883";
constexpr const char* MQTT_TOPIC = "smart-room";

#endif