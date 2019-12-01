#ifndef CONNECTION_H
#define CONNECTION_H

#include "object.h"


struct Connection
{

    // variables
    const Object* sender;
    const Object* receiver;

    int signal;
    int slot;

    // help methods
    Connection(
        const Object* sender, int signal,
        const Object* receiver, int slot);

    bool operator == (const Connection& connection);

};


#endif //CONNECTION_H
