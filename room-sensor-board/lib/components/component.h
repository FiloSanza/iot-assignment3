#ifndef _COMPONENT_H_INCLUDED
#define _COMPONENT_H_INCLUDED

namespace Components {
    template<typename T>
    class ReadableComponent {
    public:
        virtual T read() = 0;
    };
};

#endif