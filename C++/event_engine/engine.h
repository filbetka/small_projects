#ifndef ENGINE_H
#define ENGINE_H

#include "events.h"


class Engine
{

    public:

        Engine();

    private:

        bool is_active;

    public:

        void Close();
        int Execute();

};


#endif //ENGINE_H
