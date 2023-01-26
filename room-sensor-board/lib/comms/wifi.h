#ifndef _WIFI_CONNECTION_H_INCLUDED
#define _WIFI_CONNECTION_H_INCLUDED

#include "ESP8266WiFi.h"

namespace Comms {
    class WiFiClient {
    public:
        static void connect(const char* ssid, const char* password);
    };
}

#endif