#include <Arduino.h>

#include "components.h"
#include "scheduler.h"
#include "tasks/update_values.h"
#include "PubSubClient.h"
#include "wifi.h"

Components::Led* led;
Components::Pir* pir;
Components::LightSensor* light_sensor;
Scheduling::Scheduler* scheduler;

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void mqtt_send_msg(const char* msg) {
    while(!client.connected()) {
        String clientId = String("esiot-2122-client-")+String(random(0xffff), HEX);
        if (!client.connect(clientId.c_str())) {
            delay(1000);
            Serial.println("TRYING TO CONNECT TO BROKER.");
        }
    }
    Serial.println(msg);
    client.publish(MQTT_TOPIC, msg);
}

void setup() {
    Serial.begin(9600);

    Comms::WiFiClient::connect(WIFI_SSID, WIFI_PASSWORD);
    client.setServer(MQTT_SERVER, 1883);

    led = new Components::Led(LED_PIN);
    pir = new Components::Pir(PIR_PIN);
    light_sensor = new Components::LightSensor(LIGHT_SENSOR_PIN);

    scheduler = new Scheduling::Scheduler();
    scheduler->schedule(new Tasks::UpdateValues(mqtt_send_msg, led, pir, light_sensor));
}

void loop() {
    scheduler->tick();
}