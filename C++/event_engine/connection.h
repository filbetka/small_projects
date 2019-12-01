#ifndef CONNECTION_H
#define CONNECTION_H

#include "object.h"


struct Connection
{

    // variables
    Object* sender;
    Object* receiver;

    int signal;
    int slot;

    // help methods
    Connection(
        Object* sender, int signal,
        Object* receiver, int slot);

    bool operator == (const Connection& connection);

};


#endif //CONNECTION_H
