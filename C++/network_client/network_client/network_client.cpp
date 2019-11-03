#include "network_client.h"
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>
#include <cerrno>

/**
 * @class Network_Client
 * @details The class management network access
 * by client with TCP/IP protocol. The client
 * is service for all address family (IPv4, IPv6).
 */

/**
 * @brief Network_Client::Network_Client
 * @param address - IP address to connect
 * @param port - port number to connect
 */

Network_Client::Network_Client(string address, int port):
    client_socket(move(address), port)
{
    read_timeout_ms = 100;
}

Network_Client::~Network_Client()
{
    if (client_socket.Is_Connected())
        this->Connection_Close();
}

/**
 * @brief Network_Client::Connection_Open
 * @return if connection has been opened
 */

bool Network_Client::Connection_Open()
{
    return client_socket.Connection_Open();
}

/**
 * @brief Network_Client::Connection_Close
 * @details Close connection and socket
 */

void Network_Client::Connection_Close()
{
    client_socket.Connection_Close();
}

/**
 * @brief Network_Client::Is_Connected
 * @return connection is active with server.
 */

bool Network_Client::Is_Connected() const
{
    return client_socket.Is_Connected();
}

/**
 * @brief Network_Client::Write
 * @param data - data to write
 * @details Write data to server
 */

void Network_Client::Write(const string& data)
{
    int status = 0;

    // send text
    status = send(
        client_socket.Connection(),
        data.c_str(),
        data.length(),
        MSG_NOSIGNAL);

    // write error
    if (status < 0)
    {
        cerr << "Network_Client::Write: "
                "Connection error\n";

        this->Connection_Close();
    }
}

/**
 * @brief Network_Client::Read
 * @details Read data from server
 * @return red bytes as string
 */
#include <array>
string Network_Client::Read()
{
    int socket_fd = client_socket.Connection();
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
        cerr << "Network_Client::Read: select error\n";
        cerr << strerror(errno) << endl;
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
        cerr << "Network_Client::Read: read string\n";
        cerr << strerror(errno) << endl;
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
    status = send(
        client_socket.Connection(),
        data, size,
        MSG_NOSIGNAL);

    // write error
    if (status < 0)
    {
        cerr << "Network_Client::Write: "
                "Connection error\n";

        this->Connection_Close();
    }
}

/**
 * @brief Network_Client::Read
 * @param buffer - data container
 * @param size - data size to read
 * @details Read data from server
 */

void Network_Client::Read(char* buffer, size_t size)
{
    int status = 0;

    // read data
    status = read(
        client_socket.Connection(),
        buffer,
        size);

    // check if error
    if (status < 0)
    {
        cerr << "Wifi_Client::Read: "
                "Connection error\n";

        this->Connection_Close();
    }
}

/**
 * @brief Network_Client::Set_Read_Timeout
 * @param timeout_ms - read timeout in ms
 * @details Read methods use this to break waiting.
 */

void Network_Client::Set_Read_Timeout(int timeout_ms)
{
    read_timeout_ms = timeout_ms;
}
