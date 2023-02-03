#ifndef _LOGGER_H_INCLUDED
#define _LOGGER_H_INCLUDED

#include "types.h"

namespace Logger {

    class Message {
    public:
        Message();

        Message& setLight(int light);
        Message& setAngle(int angle);
        Message& setBt(int bt);
        
        void log() const;
        String getLight() const;
        String getAngle() const;
        String getBt() const;

    private:
        String bt;
        String light;
        String angle;
    };

    class Logger {
    public:
        static Logger& getInstance();
        
        Logger();
        
        void log(const Message& msg);
    };
}

#endif