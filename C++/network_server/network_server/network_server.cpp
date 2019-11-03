#include "network_server.h"
#include <iostream>

/**
 * @class Network_Server
 * @details The class create network server
 * for selected port.
 */

Network_Server::Network_Server(int port):
    server_socket(port), listener(server_socket)
{
    max_connections = 10;
    read_timeout_ms = 100;
}

/**
 * @brief Network_Server::Server_Open
 * @return if open was succeed
 */

bool Network_Server::Server_Open()
{
    if (server_socket.Is_Open()) return true;
    return server_socket.Server_Open();
}

/**
 * @brief Network_Server::Server_Close
 * @details Close connection and socket
 */

void Network_Server::Server_Close()
{
    // close all connections
    for (auto connection : connections)
        connection->Disconnect();

    // close server
    server_socket.Server_Close();

    // join listener thread
    listener.Join();
}

bool Network_Server::Is_Open() const
{
    return server_socket.Is_Open();
}

void Network_Server::Connection_Accept(bool async)
{
    if (not server_socket.Is_Open())
    {
        cerr << "Network_Server::Connection_Accept: "
                "socket is not open";

        return;
    }

    // async calling accept
    if (async)
    {
        listener.Start();
        while (not listener.Is_Running());
        return;
    }

    else
    {
        // accept new connection
        Server_Connection* connection(
            server_socket.Connection_Accept());

        // added to connections list
        connection->Set_Read_Timeout(read_timeout_ms);
        connections.push_back(connection);
    }
}

void Network_Server::Waiting_For_Accept(int ms)
{
    while (ms > 0)
    {
        if (not listener.Is_Running())
        {
            // join listener thread
            listener.Join();

            // get new connection
            Server_Connection* connection(
                listener.Accepted_Connection());

            // added to connections list
            connection->Set_Read_Timeout(read_timeout_ms);
            connections.push_back(connection);
            listener.Clear();

            break;
        }

        ms -= 10;
        this_thread::sleep_for(
            chrono::milliseconds(10));
    }
}

bool Network_Server::Waiting_Completed()
{
    if (not listener.Is_Empty())
    {
        // join listener thread
        listener.Join();

        // get new connection
        Server_Connection* connection(
            listener.Accepted_Connection());

        // added to connections list
        connection->Set_Read_Timeout(read_timeout_ms);
        connections.push_back(connection);
        listener.Clear();
    }

    return not listener.Is_Running();
}

Server_Connection* Network_Server
    ::Connection(int number) const
{
    if (connections.size() <= number)
    {
        cerr << "Network_Server::Connection: "
                "the connection not exists";

        return nullptr;
    }

    return connections[number];
}

Connections_List Network_Server::Connections()
{
    Connections_List active;
    for (auto connection : connections)
    {
        if (connection->Validate())
            active.push_back(connection);

        else delete connection;
    }

    connections = active;
    return connections;
}

/**
 * @brief Network_Server::Set_Connections_Number
 * @param number - number of connections
 * @details Set size of connections queue.
 * It is maximum connections number.
 */

void Network_Server::Set_Connections_Number(int number)
{
    if (server_socket.Is_Open())
    {
        cerr << "Network_Server::Set_Connections_Number: "
                "trying change number with open connection";

        return;
    }

    max_connections = number;
    server_socket.Set_Connections_Number(number);
}

/**
 * @brief Network_Server::Set_Read_Timeout
 * @param timeout_ms - read timeout in ms
 * @details Read methods use this to break waiting.
 */

void Network_Server::Set_Read_Timeout(int timeout_ms)
{
    for (auto connection : connections)
        connection->Set_Read_Timeout(timeout_ms);

    read_timeout_ms = timeout_ms;
}

void Network_Server::Set_Address_Family(
    Server_Socket::ADDRESS_FAMILY family)
{
    if (server_socket.Is_Open())
    {
        cerr << "Network_Server::Set_Address_Family: "
                "trying change address family "
                "with open connection";

        return;
    }

    server_socket.Set_Address_Family(family);
}
