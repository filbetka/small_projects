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
    // create server socket and start listener
    bool opened = server_socket.Server_Open();
    if (opened) listener.Start();

    return opened;
}

/**
 * @brief Network_Server::Server_Close
 * @details Close connection and socket
 */

void Network_Server::Server_Close()
{
    server_socket.Server_Close();
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
    if (server_socket.Is_Open())
    {
        cerr << "Network_Server::Set_Read_Timeout: "
                "trying change timeout with "
                "open connection";

        return;
    }

    read_timeout_ms = timeout_ms;
}
