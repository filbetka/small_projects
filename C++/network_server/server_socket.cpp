#include "server_socket.h"
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

/**
 * @class Server_Socket
 * @details The class create network server
 * for selected port.
 */

Server_Socket::Server_Socket(int port)
{
    // set values
    server_socket = -1;
    server_port = port;

    connections_number = 10;
    is_open = false;
}

Server_Socket::~Server_Socket()
{
    if (this->Is_Open())
        this->Connection_Close();
}

/**
 * @brief Server_Socket::Connection_Open
 * @return if open was succeed
 */

bool Server_Socket::Connection_Open()
{
    // create socket
    server_socket = socket(
        PF_INET,
        SOCK_STREAM,
        0);//IPPROTO_TCP);

    // error create socket
    if (server_socket < 0)
    {
        cerr << "Server_Socket::Connection_Open: "
                "cannot create socket\n";

        return false;
    }

    int enable = 1;
    int status;
    status = setsockopt(
        server_socket,
        SOL_SOCKET,
        SO_REUSEADDR,
        &enable, sizeof(int));

    if (status < 0)
    {
        cerr << "Server_Socket::Connection_Open: "
                "setsockopt reuse address failed\n";

        close(server_socket);
        return false;
    }

    status = setsockopt(
        server_socket,
        SOL_SOCKET,
        SO_REUSEPORT,
        &enable, sizeof(int));

    if (status < 0)
    {
        cerr << "Server_Socket::Connection_Open: "
                "setsockopt reuse port failed\n";

        close(server_socket);
        return false;
    }

    // set socked data
    sockaddr_in socket_data = {};
    memset(&socket_data, 0, sizeof(socket_data));
    socket_data.sin_family = AF_INET;
    socket_data.sin_port = htons(server_port);
    socket_data.sin_addr.s_addr = INADDR_ANY;

    status = bind(
        server_socket,
        (sockaddr*) &socket_data,
        sizeof(socket_data));

    // error set socked data
    if (status < 0)
    {
        cerr << "Server_Socket::Connection_Open: "
                "error bind failed\n";

        close(server_socket);
        return false;
    }

    // set the option active
    int option_value = 1;
    status = setsockopt(
        server_socket,
        SOL_SOCKET,
        SO_KEEPALIVE,
        &option_value,
        sizeof(option_value));

    if (status < 0)
    {
        cerr << "Server_Socket::Connection_Open: "
                "error set keep alive\n";

        close(server_socket);
        return false;
    }

    // enable listen
    status = listen(
        server_socket,
        connections_number);

    if (status < 0)
    {
        cerr << "Server_Socket::Connection_Open: "
                "error listen failed\n";

        close(server_socket);
        return false;
    }

    is_open = true;
    return true;
}

/**
 * @brief Server_Socket::Connection_Close
 * @details Close connection and socket
 */

void Server_Socket::Connection_Close()
{
    // close socket
    if (this->Is_Open())
        close(server_socket);

    server_socket = -1;
    is_open = false;
}

/**
 * @brief Server_Socket::Connection_Accept
 * @details Accept new connections
 * @return connection number for service
 */

int Server_Socket::Connection_Accept()
{
    sockaddr_in client = {};
    int length = sizeof(sockaddr_in);

    // accept client
    int new_connect = accept(
        server_socket,
        (sockaddr*) &client,
        (socklen_t*) &length);

    // error accept
    if (new_connect < 0)
    {
        cerr << "Server_Socket::Connection_Accept: "
                "Accept failed\n";

        close(new_connect);
        return new_connect;
    }

    // show information about accept
    cout << "New client with IP: ";
    cout << inet_ntoa(client.sin_addr);
    cout << endl;

    return new_connect;
}

/**
 * @brief Server_Socket::Set_Connections_Number
 * @param number - number of connections
 * @details Set size of connections queue.
 * It is maximum connections number.
 */

void Server_Socket::Set_Connections_Number(int number)
{
    connections_number = number;
}

/**
 * @brief Server_Socket::Is_Open
 * @return true if medium is open
 */

bool Server_Socket::Is_Open()
{
    return is_open;
}