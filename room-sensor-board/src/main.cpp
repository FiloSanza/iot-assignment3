#include <Arduino.h>

#include "components.h"
#include "scheduler.h"
#include "tasks/update_values.h"
#include "comm_pool.h"
#include "mqtt.h"
#include "wifi.h"

Comms::CommPool* comm_pool;
Components::Led* led;
Components::Pir* pir;
Components::LightSensor* light_sensor;
Scheduling::Scheduler* scheduler;

void setup() {
    Serial.begin(9600);

    Comms::WiFiClient::connect(WIFI_SSID, WIFI_PASSWORD);

    comm_pool = new Comms::CommPool();
    comm_pool->addRecv(new Comms::MqttRecv(MQTT_SERVER, MQTT_TOPIC));

    led = new Components::Led(LED_PIN);
    pir = new Components::Pir(PIR_PIN);
    light_sensor = new Components::LightSensor(LIGHT_SENSOR_PIN);

    scheduler = new Scheduling::Scheduler();
    scheduler->schedule(new Tasks::UpdateValues(comm_pool, led, pir, light_sensor));
}

void loop() {
    scheduler->tick();
}