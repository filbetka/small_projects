#include "tcp_server.h"
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


Tcp_Server::Tcp_Server()
{
    server_socket = -1;
    server_connect = -1;
    server_port = -1;
    is_open = false;
}

bool Tcp_Server::Open()
{
    // create socket
    server_socket = socket(
        PF_INET, SOCK_STREAM, IPPROTO_TCP);

    // error create socket
    if (server_socket < 0)
    {
        std::cerr <<
            "Tcp_Server::Open: "
             "cannot create socket";

        return false;
    }

    // set socked data
    sockaddr_in socket_data{};
    memset(&socket_data, 0, sizeof(socket_data));
    socket_data.sin_family = AF_INET;
    socket_data.sin_port = htons(1100); // set port number
    socket_data.sin_addr.s_addr = INADDR_ANY;

    // error set socked data
    if (bind(server_socket, (sockaddr*)&socket_data,
            sizeof(socket_data)) < 0)
    {
        int yes=1;
        if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
        {
            std::cerr <<
                "Tcp_Server::Open: "
                "error bind failed";

            close(server_socket);
            return false;
        }
    }

    // set the option active
    int optval = 1;
    socklen_t optlen = sizeof(optval);
    if (setsockopt(server_socket, SOL_SOCKET,
                  SO_KEEPALIVE, &optval, optlen) < 0)
    {
        std::cerr <<
            "Tcp_Server::Open: "
            "error set keep alive";

        close(server_socket);
        return false;
    }

    // enable listen
    if (listen(server_socket, 3) < 0)
    {
        std::cerr <<
            "Tcp_Server::Open: "
            "error listen failed";

        close(server_socket);
        return false;
    }

    is_open = true;
    return true;
}


/**
 * @brief Wifi_Server::Connection_Close
 * @details Close connection and socket
 */

void Wifi_Server::Connection_Close()
{
    if (shutdown(server_connect, SHUT_RDWR) < 0)
        __LOG__("Wifi_Server::Connection_Close: "
                "cannot shutdown socket");

    // change status
    is_connected = false;
    is_open = false;

    // close connection and socket
    close(server_connect);
    close(server_socket);
}

/**
 * @brief Wifi_Server::Connection_Accept
 * @details Accept new connections
 */

void Wifi_Server::Connection_Accept()
{
    struct sockaddr_in client;
    int length = sizeof(struct sockaddr_in);

    // accept client
    int new_connect = accept(
        server_socket,
        (struct sockaddr *)&client,
        (socklen_t*)&length);

    __LOG__("");
    __LOG__("!!! ACCEPT\n");
    __LOG__(QString("CLIENT IP: ") +
        inet_ntoa(client.sin_addr));

    // error accept
    if(new_connect < 0)
    {
        __LOG__("Wifi_Server::Connection_Accept:"
                "Accept failed");

        close(new_connect);
        return;
    }

    // server is busy
    if (this->Check_Connection(client))
    {
        write(new_connect, "Port already in use\n", 21);
        close(new_connect);
        return;
    }
    else
    {
        // stop read thread
        emit Stop_Wifi_Read();
        OsSleep(20);

        // close old connection
        close(server_connect);

        // everything ok
        server_connect = new_connect;
        is_connected = true;
        emit New_Connection();
    }
}

/**
 * @brief Wifi_Server::Disconnect
 * @details Close wifi server
 */

void Wifi_Server::Disconnect()
{
    close(server_connect);
    emit End_Connection();
}

/**
 * @brief Wifi_Server::Check_Connection
 * @return if connection is realy opened.
 * Try send any data to media.
 */

bool Wifi_Server::Check_Connection(sockaddr_in new_client)
{
    static int loop = 0;
    __LOG__("Loop: " + QString::number(++loop));

    Server_Manager manager;
    QString current_ip = manager.Get_Ip_Address();
    QString new_ip = inet_ntoa(new_client.sin_addr);

    if (manager.Get_Limit_Enabled())
        if (current_ip != new_ip)
            return true;

    return false;
}

/**
 * @brief Wifi_Server::Write
 * @param data - data to write
 * @details Write data to client
 */

void Wifi_Server::Write(QByteArray data)
{
    int status = 0;

    // send text
    status = write(server_connect, data.data(), data.length());

    // check if error
    if (status < 0)
    {
        __LOG__("Wifi_Server::Write: "
                "connection error");
    }
}

/**
 * @brief Wifi_Server::Write
 * @param data - data to write
 * @param size - size of data
 * @details Write data to client
 */

void Wifi_Server::Write(char* data, size_t size)
{
    int status = 0;

    // send text
    status = write(server_connect, data, size);

    // check if error
    if (status < 0)
        __LOG__("Wifi_Server::Write: write data");
}

/**
 * @brief Wifi_Server::Read
 * @param buffer
 * @param size
 */

void Wifi_Server::Read(char* buffer, size_t size)
{
    int status = 0;

    // read data
    status = read(server_connect, buffer, size);

    // check if error
    if (status < 0)
    {
        __LOG__("Wifi_Server::Read: read data");
        return;
    }
}

/**
 * @brief Wifi_Server::Read
 * @param bytes_number - number of bytes for read
 * @return read bytes as string
 * @details Read data from client in the number of bytes
 * specified in the parameter
 */

QByteArray Wifi_Server::Read()
{
    int socket_fd = server_connect;
    int status = 0;

    fd_set read_set;
    timeval timeout;
    timeout.tv_sec=0;
    timeout.tv_usec=100000;

    FD_ZERO(&read_set);
    FD_SET(socket_fd, &read_set);

    status = select(FD_SETSIZE, &read_set, NULL, NULL, &timeout);
    if (status < 0)
    {
        __LOG__(strerror(errno));
        __LOG__("Wifi_Server::Read: select error");
        return "";
    }

    if (status == 0) // timeout
        OsSleep(10);

    if (not FD_ISSET(socket_fd, &read_set))
        return "";

    // read data
    char buffor[4096] = {0};
    OsSleep(10);
    status = recv(socket_fd, buffor, 4096, O_NONBLOCK);

    // check if error
    if (status < 0)
    {
        __LOG__(strerror(errno));
        __LOG__("Wifi_Server::Read: read string");
        return "";
    }

    // return read data
    return QByteArray(buffor, status);
}