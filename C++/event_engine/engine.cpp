#include "engine.h"
#include <algorithm>


Engine::Engine()
{
    is_active = true;
}

bool Engine::Have_Signal(const Object* obj, int signal)
{
    auto signals = obj->signals;
    return find(signals.begin(), signals.end(), signal)
        != signals.end();
}

int Engine::Count_Signals(const Object* obj, int signal)
{
    auto signals = obj->signals;
    return count(signals.begin(), signals.end(), signal);
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

        // for every connection
        for (auto connection : connections)
        {
            // readable variables
            auto sender = connection.sender;
            auto signal = connection.signal;
            auto receiver = connection.receiver;
            auto slot = connection.slot;

            // check if sender have signal
            if (this->Have_Signal(sender, signal))
            {
                // call slots for signal
                sender->Signal_Done(signal);
                receiver->Slots(slot);
            }
        }
    }

    return 0;
}
