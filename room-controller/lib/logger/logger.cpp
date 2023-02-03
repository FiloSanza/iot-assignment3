#include "logger.h"

#include <Arduino.h>

namespace Logger {
    Message::Message() {}

    Message& Message::setLight(int light) {
        this->light = light;
        return *this;
    }

    Message& Message::setAngle(int angle) {
        this->angle = angle;
        return *this;
    }

    Message& Message::setBt(int bt) {
        this->bt = bt;
        return *this;
    }

    void Message::log() const {
        Logger::getInstance().log(*this);
    }

    String Message::getLight() const {
        return light;
    }

    String Message::getAngle() const {
        return angle;
    }

    String Message::getBt() const {
        return bt;
    }

    Logger::Logger() {}

    Logger& Logger::getInstance() {
        static Logger instance = Logger();
        return instance;
    }

    void Logger::log(const Message& msg) {

        String str = 
            "{ \"light\": \"" + msg.getLight() + "\"" +
            ", \"angle\": \"" + msg.getAngle() + "\"" +
            ", \"bt\": \"" + msg.getBt() + "\"" + " }";

        Serial.println(str);
    }
}