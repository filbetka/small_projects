#include "network_client.h"
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
 * @class Network_Client
 * @details The class management network ports
 * as client by TCP/IP protocol.
 */

/**
 * @brief Network_Client::Network_Client
 * @param address - IP address to connect
 * @param port - port number to connect
 */

Network_Client::Network_Client(string address, int port)
{
    client_address = move(address);
    client_port = port;
    client_socket = -1;
}

/**
 * @brief Network_Client::Connection_Open
 * @return if connection has been opened
 */

bool Network_Client::Connection_Open()
{
    // connection is open
    if (this->Is_Open())
        return true;

    // create socket
    client_socket = socket(
        AF_INET, SOCK_STREAM, 0);

    if (client_socket < 0)
    {
        cout << "Network_Client::Connection_Open: "
                "create socket error";

        return false;
    }

    // ...
    int status = 0;
    timeval tv = {};
    tv.tv_sec = 1;
    tv.tv_usec = 0;

    status = setsockopt(
        client_socket,
        SOL_SOCKET, SO_RCVTIMEO,
        (const char*) &tv, sizeof tv);

    if (status < 0)
    {
        cout << "Network_Client::Connection_Open: "
                "error set keep alive";

        close(client_socket);
        return false;
    }

    // create socket data
    sockaddr_in data = {};
    memset(&data, 0, sizeof(data));
    data.sin_family = AF_INET;
    data.sin_port = htons(client_port);

    // bind data with port
    status = inet_pton(
        AF_INET,
        client_address.c_str(),
        &data.sin_addr);

    if (status <= 0)
    {
        cout << "Network_Client::Connection_Open: "
                "invalid address or address not supported";

        return false;
    }

    // open connection
    status = connect(
        client_socket,
        (sockaddr*) &data,
        sizeof(data));

    if (status < 0)
    {
        cout << "Network_Client::Connection_Open: "
                "Connection failed";

        return false;
    }

    is_open = true;
    is_connected = true;
    return true;
}

/**
 * @brief Network_Client::Connection_Close
 * @details Close connection and socket
 */

void Network_Client::Connection_Close()
{
    is_open = false;
    is_connected = false;
    close(client_socket);
}

/**
 * @brief Network_Client::Write
 * @param data - data to write
 * @details Write data to server
 */

void Network_Client::Write(string data)
{
    int status = 0;

    // send text
    status = write(
        client_socket,
        data.c_str(),
        data.length());

    // write error
    if (status < 0)
    {
        cout << "Network_Client::Write: "
                "Connection error";

        this->Connection_Close();
    }
}

/**
 * @brief Network_Client::Read
 * @details Read data from server
 * @return red bytes as string
 */

string Network_Client::Read()
{
    int socket_fd = client_socket;
    int status = 0;

    fd_set read_set;
    timeval timeout = {};
    timeout.tv_sec=0;
    timeout.tv_usec=100000;

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
        cout << strerror(errno);
        cout << "Network_Client::Read: select error";
        return "";
    }

    // timeout
    if (status == 0)
        usleep(10000);

    // set select error
    if (not FD_ISSET(socket_fd, &read_set))
    {
        cout << "Network_Client::Read: select error";
        return "";
    }

    // read data
    char buffer[4096] = {0};
    status = recv(socket_fd, buffer, 4096, SOCK_NONBLOCK);

    // read error
    if (status < 0)
    {
        cout << strerror(errno);
        cout << "Network_Client::Read: read string";
        return "";
    }

    // return read data
    return string(buffer, status);
}

/**
 * @brief Network_Client::Write
 * @param data - data to write
 * @param size - data size to write
 * @details Write data to server
 */

void Network_Client::Write(char* data, size_t size)
{
    int status = 0;

    // send text
    status = write(
        client_socket,
        data,
        size);

    // write error
    if (status < 0)
    {
        cout << "Network_Client::Write: "
                "Connection error";

        this->Connection_Close();
    }
}

void Network_Client::Read(char* buffer, size_t size)
{
    int status = 0;

    // read data
    status = read(
        client_socket,
        buffer,
        size);

    // check if error
    if (status < 0)
    {
        cout << "Wifi_Client::Read: "
                "Connection error";

        this->Connection_Close();
    }
}
