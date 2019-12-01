#include "engine.h"


Engine::Engine()
{
    is_active = true;
}

void Engine::Close()
{
    is_active = false;
}

int Engine::Execute()
{
    // get events list
    Events* events =
        Events::Get_Instance();

    // make events
    while (is_active)
    {
        auto connections =
            events->Get_Connections();

        for (auto connection : connections)
        {

        }
    }

    return 0;
}
