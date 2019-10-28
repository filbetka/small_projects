#include "server_connection.h"
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <cerrno>

/**
 * @class Server_Connection
 * @details
 */

Server_Connection::Server_Connection(int connection)
{
    // save connection number
    server_connection = connection;
    read_timeout_ms = 100;
    is_connected = true;

    // validate state
    if (connection <= 0)
        is_connected = false;
}

bool Server_Connection::Validate()
{
    return server_connection != -1;
}

/**
 * @brief Server_Connection::Disconnect
 * @details
 */

void Server_Connection::Disconnect()
{
    if (not this->Validate())
    {
        cerr << "Server_Connection::Disconnect: "
                "bad connection number\n";

        return;
    }

    if (this->Is_Connected())
    {
        // send finish connection signal to client
        if (shutdown(server_connection, SHUT_RDWR) < 0)
            cerr << "Server_Connection::Disconnect: "
                    "cannot shutdown socket\n";

        // close connection
        close(server_connection);
    }

    server_connection = -1;
    is_connected = false;
}

bool Server_Connection::Is_Connected()
{
    return is_connected;
}

/**
 * @brief Server_Connection::Write
 * @param data - data to write
 * @details Write data to client
 */

void Server_Connection::Write(const string& data)
{
    if (not this->Validate())
    {
        cerr << "Server_Connection::Write: "
                "bad connection number\n";

        return;
    }

    int status = 0;

    // send text
    status = send(
        server_connection,
        data.c_str(),
        data.length(),
        MSG_NOSIGNAL);

    // check if error
    if (status < 0)
    {
        this->Disconnect();
        cerr << "Server_Connection::Write: "
                "connection error\n";
    }
}

/**
 * @brief Server_Connection::Read
 * @param bytes_number - number of bytes for read
 * @return read bytes as string
 * @details Read data from client in the number of bytes
 * specified in the parameter
 */

string Server_Connection::Read()
{
    if (not this->Validate())
    {
        cerr << "Server_Connection::Read: "
                "bad connection number\n";

        return "";
    }

    int socket_fd = server_connection;
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
        cerr << "Server_Connection::Read: select error\n";
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
        cerr << "Server_Connection::Read: read string\n";
        cerr << strerror(errno) << endl;
        return "";
    }

    // return read data
    return string(buffer, status);
}

/**
 * @brief Server_Connection::Write
 * @param data - data to write
 * @param size - size of data
 * @details Write data to client
 */

void Server_Connection::Write(char* data, size_t size)
{
    if (not this->Validate())
    {
        cerr << "Server_Connection::Write: "
                "bad connection number\n";

        return;
    }

    int status = 0;

    // send text
    status = send(
        server_connection,
        data, size,
        MSG_NOSIGNAL);

    // check if error
    if (status < 0)
    {
        this->Disconnect();
        cerr << "Server_Connection::Write: "
                "connection error\n";
    }
}

/**
 * @brief Server_Connection::Read
 * @param buffer
 * @param size
 */

void Server_Connection::Read(char* buffer, size_t size)
{
    if (not this->Validate())
    {
        cerr << "Server_Connection::Read: "
                "bad connection number\n";

        return;
    }

    int status = 0;

    // read data
    status = read(
        server_connection,
        buffer,
        size);

    // check if error
    if (status < 0)
    {
        cerr << "Server_Connection::Read: "
                "connection error\n";
    }
}

/**
 * @brief Server_Connection::Set_Read_Timeout
 * @param timeout_ms
 */

void Server_Connection::Set_Read_Timeout(int timeout_ms)
{
    read_timeout_ms = timeout_ms;
}