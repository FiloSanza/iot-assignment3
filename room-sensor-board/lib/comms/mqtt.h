#ifndef _MQTT_H_INCLUDED
#define _MQTT_H_INCLUDED

#include "PubSubClient.h"
#include "receiver.h"

namespace Comms {
    class MqttRecv : public Receiver {
    public:
        MqttRecv(const char* server_addr, const char* topic);

        void send(const char* msg);

    private:
        void reconnect();

        const char* topic;
        PubSubClient client;
    };
}

#endif