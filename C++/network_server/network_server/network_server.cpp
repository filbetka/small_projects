#include "network_server.h"
#include <iostream>

/**
 * @class Network_Server
 * @details The class is network TCP/IP server.
 * It provides API for accepts new client connections
 * also in another thread.
 */

/**
 * @brief Network_Server::Network_Server
 * @param port - server port where
 * server will be available.
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
 * @details Close connections and socket
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

/**
 * @brief Network_Server::Is_Open
 * @return If server socket is opened.
 */

bool Network_Server::Is_Open() const
{
    return server_socket.Is_Open();
}

/**
 * @brief Network_Server::Connection_Accept
 * @param async - if accept connection asynchronously
 * @details Waiting and accept new client connection.
 */

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

/**
 * @brief Network_Server::Waiting_For_Accept
 * @param ms - milliseconds
 * @details It's for async accept method
 * (Network_Server::Connection_Accept(true)).
 * The method waiting with checking if
 * new connection came and accept that.
 */

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

/**
 * @details Network_Server::Accept_Listener_Finished
 * @details It's for async accept method
 * (Network_Server::Connection_Accept(true)).
 * The method check if accept listener finished
 * and save the connection to connections list.
 * @return if accept listener finished.
 */

bool Network_Server::Accept_Listener_Finished()
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

/**
 * @brief Network_Server::Connections
 * @return list of client connections.
 */

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
 * @brief Network_Server::Connection
 * @param ip - client ip address
 * @return connection object with the ip address.
 */

Server_Connection* Network_Server
    ::Connection(const string& ip) const
{
    for (auto connection : connections)
        if (connection->Client_Address() == ip)
            return connection;

    cerr << "Network_Server::Connection: "
            "no one connection with ip\n";

    return nullptr;
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

/**
 * @brief Network_Server::Set_Address_Family
 * @param family - server address family (IPv4, IPv6).
 */

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
