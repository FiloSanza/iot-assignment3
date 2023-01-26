#include "mqtt.h"

#include <ESP8266WiFi.h>

namespace Comms {
    MqttRecv::MqttRecv(const char* server_addr, const char* topic) {
        WiFiClient wifiClient;
        
        this->topic = topic;
        this->client = PubSubClient(wifiClient);
        this->client.setServer(server_addr, 1883);
    }

    void MqttRecv::send(const char* msg) {
        while(!this->client.connected()) {
            this->reconnect();
        }

        this->client.publish(this->topic, msg);
    }

    void MqttRecv::reconnect() {
        // Create a new clientId for the new connection attempt.
        char clientId[64];
        snprintf(clientId, 64, "room-sensor-board-%x", random(0xffff));

        if (!this->client.connect(clientId)) {
            delay(1000);
        }
    }
}