#include "logger.h"

#include <Arduino.h>

namespace Logger {
    Message::Message() : timestamp(millis()) {}

    Message& Message::setData(String data) {
        this->data = data;
        return *this;
    }

    Message& Message::setTag(uint32_t tag) {
        this->tag = tag;
        return *this;
    }

    Message& Message::setTimestamp(timestamp_t timestamp) {
        this->timestamp = timestamp;
        return *this;
    }

    Message& Message::setDescription(String desc) {
        this->desc = desc;
        return *this;
    }

    void Message::log() const {
        Logger::getInstance().log(*this);
    }

    String Message::getData() const {
        return data;
    }

    uint32_t Message::getTag() const {
        return tag;
    }

    String Message::getDescription() const {
        return desc;
    }

    timestamp_t Message::getTimestamp() const {
        return timestamp;
    }

    Logger::Logger() {}

    Logger& Logger::getInstance() {
        static Logger instance = Logger();
        return instance;
    }

    void Logger::log(const Message& msg) {

        String str = 
            "{\"data\": \"" + msg.getData() + "\"" +
            ", \"desc\": \"" + msg.getDescription() + "\"" +
            ", \"time\": " + String(msg.getTimestamp()) +
            ", \"tag\": " + String(msg.getTag()) + " }";

        Serial.println(str);
    }
}