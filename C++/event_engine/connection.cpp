#include "connection.h"


Connection::Connection(
    Object* _sender, int _signal,
    Object* _receiver, int _slot):
        sender(_sender), signal(_signal),
        receiver(_receiver), slot(_slot)
{
}

bool Connection::operator == (
    const Connection& connection)
{
    return
        sender == connection.sender and
        receiver == connection.receiver and
        signal == connection.signal and
        slot == connection.slot;
}