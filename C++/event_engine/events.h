#ifndef EVENTS_H
#define EVENTS_H

#include "connection.h"
#include <list>


class Events
{

    private:

        Events() = default;

    private:

        list<Connection> connections;

    public:

        void Add_Connection(Connection connection);
        void Remove_Connection(Connection connection);
        auto Get_Connections() -> list<Connection>;

    public:

        static Events* Get_Instance();

};


#endif //EVENTS_H
