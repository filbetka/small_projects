#include "object.h"
#include "events.h"
#include <algorithm>


Object::Object()
{
}

void Object::Signal_Done(int signal)
{
    auto index = find(signals.begin(),
        signals.end(), signal);

    if (index != signals.end())
    {
        signals.erase(index);
    }
}

void Object::Signal(int type)
{
    signals.push_back(type);
}

void Object::Slots(int slot)
{
}

void Object::Connect(
    Object* sender, int signal,
    Object* receiver, int slot)
{
    Events::Get_Instance()
        ->Add_Connection(
            Connection(
                sender, signal,
                receiver, slot
            )
        );
}
