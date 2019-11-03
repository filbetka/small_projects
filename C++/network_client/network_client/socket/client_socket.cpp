#include "client_socket.h"
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

/**
 * @class Client_Socket
 * @details Socket service class.
 * The object can open and close connection
 * for every address family (IPv4, IPv6).
 */

/**
 * @brief Client_Socket::Client_Socket
 * @param address - IP address to connect
 * @param port - port number to connect
 */

Client_Socket::Client_Socket(string address, int port)
{
    client_address = move(address);
    client_port = port;
    client_socket = -1;
    is_connected = false;

    if (this->Is_IPv6())
        address_family = AF_INET6;

    else address_family = AF_INET;
}

Client_Socket::~Client_Socket()
{
    if (this->Is_Connected())
        this->Connection_Close();
}

/**
 * @brief Client_Socket::Create_Socket
 * @details Create and validate socket
 * @return if successful
 */

bool Client_Socket::Create_Socket()
{
    // create socket
    client_socket = socket(
        address_family, SOCK_STREAM, 0);

    if (client_socket < 0)
    {
        cerr << "Client_Socket::Connection_Open: "
                "create socket error\n";

        return false;
    }

    return true;
}

/**
 * @brief Client_Socket::Set_Timeout
 * @details Create and validate timeout option
 * @return if successful
 */

bool Client_Socket::Set_Timeout()
{
    // timeout
    int status = 0;
    timeval tv = {};
    tv.tv_sec = 1;
    tv.tv_usec = 0;

    status = setsockopt(
        client_socket,
        SOL_SOCKET,
        SO_RCVTIMEO,
        (const char*) &tv,
        sizeof(tv));

    if (status < 0)
    {
        cerr << "Client_Socket::Connection_Open: "
                "error set keep alive\n";

        close(client_socket);
        return false;
    }

    return true;
}

/**
 * @brief Client_Socket::Connect_IPv4
 * @details Connect and validate for IPv4 family
 * @return if successful
 */

bool Client_Socket::Connect_IPv4()
{
    // create socket data
    sockaddr_in data = {};
    int status = 0;

    memset(&data, 0, sizeof(data));
    data.sin_family = address_family;
    data.sin_port = htons(client_port);

    // convert data to binary
    status = inet_pton(
        address_family,
        client_address.c_str(),
        &data.sin_addr);

    if (status <= 0)
    {
        cerr << "Client_Socket::Connection_Open: "
                "invalid address or address "
                "not supported\n";

        return false;
    }

    // open connection
    status = connect(
        client_socket,
        (sockaddr*) &data,
        sizeof(data));

    if (status < 0)
    {
        cerr << "Client_Socket::Connection_Open: "
                "Connection failed\n";

        return false;
    }

    return true;
}

/**
 * @brief Client_Socket::Connect_IPv6
 * @details Connect and validate for IPv6 family
 * @return if successful
 */

bool Client_Socket::Connect_IPv6()
{
    // create socket data
    sockaddr_in6 data = {};
    int status = 0;

    memset(&data, 0, sizeof(data));
    data.sin6_family = address_family;
    data.sin6_port = htons(client_port);

    // convert data to binary
    status = inet_pton(
        address_family,
        client_address.c_str(),
        &data.sin6_addr);

    if (status <= 0)
    {
        cerr << "Client_Socket::Connection_Open: "
                "invalid address or address "
                "not supported\n";

        return false;
    }

    // open connection
    status = connect(
        client_socket,
        (sockaddr*) &data,
        sizeof(data));

    if (status < 0)
    {
        cerr << "Client_Socket::Connection_Open: "
                "Connection failed\n";

        return false;
    }

    return true;
}

/**
 * @brief Client_Socket::Connection_Open
 * @details Make all operations to open connection
 * @return if successful
 */

bool Client_Socket::Connection_Open()
{
    // connection is open
    if (this->Is_Connected())
        return true;

    if (not this->Create_Socket()) return false;
    if (not this->Set_Timeout()) return false;

    if (this->Is_IPv6())
    {
        if (not this->Connect_IPv6())
            return false;
    }

    else
    {
        if (not this->Connect_IPv4())
            return false;
    }

    is_connected = true;
    return true;
}

/**
 * @brief Client_Socket::Connection_Close
 * @details Close connection with server.
 */

void Client_Socket::Connection_Close()
{
    is_connected = false;

    close(client_socket);
    client_socket = -1;
}

/**
 * @brief Client_Socket::Is_Connected
 * @return connection is active with server.
 */

bool Client_Socket::Is_Connected() const
{
    return is_connected;
}

/**
 * @brief Client_Socket::Is_IPv4
 * @return address is IPv4 family.
 */

bool Client_Socket::Is_IPv4() const
{
    return (client_address.find('.') != std::string::npos);
}

/**
 * @brief Client_Socket::Is_IPv6
 * @return address is IPv6 family.
 */

bool Client_Socket::Is_IPv6() const
{
    return (client_address.find(':') != std::string::npos);
}

/**
 * @brief Client_Socket::Connection
 * @return connection number for service.
 * This is a file descriptor to write and read data.
 */

int Client_Socket::Connection() const
{
    return client_socket;
}