#include "network_server.h"
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
 * @class Network_Server
 * @details The class create network server
 * for selected port.
 */

Network_Server::Network_Server(int port)
{
    // set values
    server_socket = -1;
    server_port = port;

    server_connect = -1;
    connections_number = 10;
    read_timeout_ms = 100;
}

Network_Server::~Network_Server()
{
    if (this->Is_Open())
        this->Connection_Close();
}

/**
 * @brief Network_Server::Connection_Open
 * @return if open was succeed
 */

bool Network_Server::Connection_Open()
{
    // create socket
    server_socket = socket(
        PF_INET,
        SOCK_STREAM,
        IPPROTO_TCP);

    // error create socket
    if (server_socket < 0)
    {
        cerr << "Network_Server::Connection_Open: "
                "cannot create socket";

        return false;
    }

    // set socked data
    sockaddr_in socket_data = {};
    memset(&socket_data, 0, sizeof(socket_data));
    socket_data.sin_family = AF_INET;
    socket_data.sin_port = htons(server_port);
    socket_data.sin_addr.s_addr = INADDR_ANY;

    int status = bind(
        server_socket,
        (sockaddr*) &socket_data,
        sizeof(socket_data));

    // error set socked data
    if (status < 0)
    {
        int yes=1;
        status = setsockopt(
            server_socket,
            SOL_SOCKET,
            SO_REUSEADDR,
            &yes, sizeof(yes));

        if (status < 0)
        {
            cerr << "Network_Server::Connection_Open: "
                    "error bind failed";

            close(server_socket);
            return false;
        }
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
        cerr << "Network_Server::Connection_Open: "
                "error set keep alive";

        close(server_socket);
        return false;
    }

    // enable listen
    status = listen(
        server_socket,
        connections_number);

    if (status < 0)
    {
        cerr << "Network_Server::Connection_Open: "
                "error listen failed";

        close(server_socket);
        return false;
    }

    is_open = true;
    return true;
}

/**
 * @brief Network_Server::Connection_Close
 * @details Close connection and socket
 */

void Network_Server::Connection_Close()
{
    if (this->Is_Connected())
    {
        // send finish connection signal to client
        if (shutdown(server_connect, SHUT_RDWR) < 0)
            cerr << "Network_Server::Connection_Close: "
                    "cannot shutdown socket";

        // close connection
        close(server_connect);
    }

    // change status
    is_connected = false;
    is_open = false;

    // close socket
    close(server_socket);
}

/**
 * @brief Network_Server::Connection_Accept
 * @details Accept new connections
 */

void Network_Server::Connection_Accept()
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
        cerr << "Network_Server::Connection_Accept: "
                "Accept failed";

        close(new_connect);
        return;
    }

    // show information about accept
    cout << "New client with IP: ";
    cout << inet_ntoa(client.sin_addr);
    cout << endl;

    // close old connection
    close(server_connect);

    // everything ok
    server_connect = new_connect;
    is_connected = true;
}

/**
 * @brief Network_Server::Disconnect
 * @details Close wifi server
 */

void Network_Server::Disconnect()
{
    // send finish connection signal to client
    if (shutdown(server_connect, SHUT_RDWR) < 0)
        cerr << "Network_Server::Connection_Close: "
                "cannot shutdown socket";

    close(server_connect);
    is_connected = false;
}

/**
 * @brief Network_Server::Write
 * @param data - data to write
 * @details Write data to client
 */

void Network_Server::Write(string data)
{
    int status = 0;

    // send text
    status = write(
        server_connect,
        data.c_str(),
        data.length());

    // check if error
    if (status < 0)
    {
        cerr << "Network_Server::Write: "
                "connection error";
    }
}

/**
 * @brief Network_Server::Read
 * @param bytes_number - number of bytes for read
 * @return read bytes as string
 * @details Read data from client in the number of bytes
 * specified in the parameter
 */

string Network_Server::Read()
{
    int socket_fd = server_connect;
    int status = 0;

    int timeout_sec = read_timeout_ms / 1000;
    int timeout_ms = read_timeout_ms - timeout_sec * 1000;

    fd_set read_set;
    timeval timeout = {};
    timeout.tv_sec = timeout_sec;
    timeout.tv_usec = timeout_ms;

    FD_ZERO(&read_set);
    FD_SET(socket_fd, &read_set);

    status = select(
        FD_SETSIZE,
        &read_set,
        nullptr,
        nullptr,
        &timeout);

    if (status < 0)
    {
        cerr << "Network_Server::Read: select error";
        cerr << strerror(errno);
        return "";
    }

    if (status == 0) // timeout
        usleep(10000); // 10 ms

    if (not FD_ISSET(socket_fd, &read_set))
        return "";

    // read data
    char buffer[4096] = {0};
    status = read(socket_fd, buffer, 4096);

    // check if error
    if (status < 0)
    {
        cerr << "Network_Server::Read: read string";
        cerr << strerror(errno);
        return "";
    }

    // return read data
    return string(buffer, status);
}

/**
 * @brief Network_Server::Write
 * @param data - data to write
 * @param size - size of data
 * @details Write data to client
 */

void Network_Server::Write(char* data, size_t size)
{
    int status = 0;

    // send text
    status = write(
        server_connect,
        data,
        size);

    // check if error
    if (status < 0)
    {
        cerr << "Network_Server::Write: "
                "connection error";
    }
}

/**
 * @brief Network_Server::Read
 * @param buffer
 * @param size
 */

void Network_Server::Read(char* buffer, size_t size)
{
    int status = 0;

    // read data
    status = read(
        server_connect,
        buffer,
        size);

    // check if error
    if (status < 0)
    {
        cerr << "Network_Server::Read: "
                "connection error";
    }
}

/**
 * @brief Network_Server::Set_Connections_Number
 * @param number - number of connections
 * @details Set size of connections queue.
 * It is maximum connections number.
 */

void Network_Server::Set_Connections_Number(int number)
{
    connections_number = number;
}

/**
 * @brief Network_Server::Set_Read_Timeout
 * @param timeout_ms - read timeout in ms
 * @details Read methods use this to break waiting.
 */

void Network_Server::Set_Read_Timeout(int timeout_ms)
{
    read_timeout_ms = timeout_ms;
}
