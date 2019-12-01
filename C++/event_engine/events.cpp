#include "events.h"


void Events::Add_Connection(Connection connection)
{
    connections.push_back(connection);
}

void Events::Remove_Connection(Connection connection)
{
    connections.remove(connection);
}

auto Events::Get_Connections() -> list<Connection>
{
    return connections;
}

auto Events::Get_Instance() -> Events*
{
    static Events instance;
    return &instance;
}
