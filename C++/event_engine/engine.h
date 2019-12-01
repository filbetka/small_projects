#ifndef ENGINE_H
#define ENGINE_H

#include "events.h"


class Engine
{

    public:

        Engine();

    private:

        bool is_active;

    private:

        bool Have_Signal(const Object* obj, int signal);
        int Count_Signals(const Object* obj, int signal);

    public:

        void Close();
        int Execute();

};


#endif //ENGINE_H
