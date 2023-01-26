#include "wifi.h"

#include <ESP8266WiFi.h>

namespace Comms {
    void WiFiClient::connect(const char* ssid, const char* password) {
        delay(10);

        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);

        while(WiFi.status() != WL_CONNECTED) {
            delay(500);
        }
    }
}