#ifndef _LOGGER_H_INCLUDED
#define _LOGGER_H_INCLUDED

#include "types.h"

namespace Logger {

    class Message {
    public:
        Message();

        Message& setData(String data);
        Message& setTimestamp(timestamp_t timestamp);
        Message& setDescription(String desc);
        Message& setTag(uint32_t tag);
        
        void log() const;
        String getData() const;
        timestamp_t getTimestamp() const;
        String getDescription() const;
        uint32_t getTag() const;

    private:
        String data;
        String desc;
        timestamp_t timestamp;
        uint32_t tag = -1;
    };

    class Logger {
    public:
        static Logger& getInstance();
        
        Logger();
        
        void log(const Message& msg);
    };
}

#endif