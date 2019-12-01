#include "object.h"
#include "events.h"


Object::Object()
{
}

void Object::Signal(int type)
{
    signals.push_back(type);
}

void Object::Slots(int slot)
{
}

void Object::Connect(
    const Object* sender, int signal,
    const Object* receiver, int slot)
{
    Events::Get_Instance()
        ->Add_Connection(
            Connection(
                sender, signal,
                receiver, slot
            )
        );
}
