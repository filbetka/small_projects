#include "server_socket.h"
#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

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
    family = IP_V4;
}

Server_Socket::~Server_Socket()
{
    if (this->Is_Open())
        this->Server_Close();
}

bool Server_Socket::Create_Socket()
{
    // create socket
    server_socket = socket(
        this->C_Address_Family(),
        SOCK_STREAM,
        0);

    // error create socket
    if (server_socket < 0)
    {
        cerr << "Server_Socket::Create_Socket: "
                "cannot create socket\n";

        return false;
    }

    return true;
}

bool Server_Socket::Reuse_Address()
{
    int enable = 1;
    int status;
    status = setsockopt(
        server_socket,
        SOL_SOCKET,
        SO_REUSEADDR,
        &enable, sizeof(int));

    if (status < 0)
    {
        cerr << "Server_Socket::Reuse_Address: "
                "reuse address failed\n";

        close(server_socket);
        return false;
    }

    return true;
}

bool Server_Socket::Reuse_Port()
{
    int enable = 1;
    int status;
    status = setsockopt(
        server_socket,
        SOL_SOCKET,
        SO_REUSEPORT,
        &enable, sizeof(int));

    if (status < 0)
    {
        cerr << "Server_Socket::Reuse_Port: "
                "reuse port failed\n";

        close(server_socket);
        return false;
    }

    return true;
}

bool Server_Socket::Bind_Socket_IPv4()
{
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
        cerr << "Server_Socket::Bind_Socket: "
                "bind socket failed\n";

        close(server_socket);
        return false;
    }

    return true;
}

bool Server_Socket::Bind_Socket_IPv6()
{
    // set socked data
    sockaddr_in6 socket_data = {};
    memset(&socket_data, 0, sizeof(socket_data));
    socket_data.sin6_family = AF_INET6;
    socket_data.sin6_port = htons(server_port);
    socket_data.sin6_addr = in6addr_any;

    int status = bind(
        server_socket,
        (sockaddr*) &socket_data,
        sizeof(socket_data));

    // error set socked data
    if (status < 0)
    {
        cerr << "Server_Socket::Bind_Socket: "
                "bind socket failed\n";

        close(server_socket);
        return false;
    }

    return true;
}

bool Server_Socket::Set_Keep_Alive()
{
    // set the option active
    int enable = 1;
    int status;
    status = setsockopt(
        server_socket,
        SOL_SOCKET,
        SO_KEEPALIVE,
        &enable,
        sizeof(enable));

    if (status < 0)
    {
        cerr << "Server_Socket::Set_Keep_Alive: "
                "set keep alive failed\n";

        close(server_socket);
        return false;
    }

    return true;
}

bool Server_Socket::Set_Listen_Socket()
{
    // enable listen
    int status = listen(
        server_socket,
        connections_number);

    if (status < 0)
    {
        cerr << "Server_Socket::Set_Listen_Socket: "
                "set listen socket failed\n";

        close(server_socket);
        return false;
    }

    return true;
}

Server_Connection* Server_Socket::Accept_IPv4() const
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
        return nullptr;
    }

    // show information about accept
    cout << "\nNew client with IP: ";
    cout << inet_ntoa(client.sin_addr);
    cout << endl;

    // create connection object
    auto connection = new Server_Connection(new_connect);
    connection->Set_Client_Address(
        inet_ntoa(client.sin_addr));

    return connection;
}

Server_Connection* Server_Socket::Accept_IPv6() const
{
    sockaddr_in6 client = {};
    int length = sizeof(sockaddr_in6);

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
        return nullptr;
    }

    char ip_address[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET6, &client.sin6_addr,
        ip_address, INET6_ADDRSTRLEN);

    // show information about accept
    cout << "\nNew client with IP: ";
    cout << ip_address;
    cout << endl;

    // create connection object
    auto connection = new Server_Connection(new_connect);
    connection->Set_Client_Address(ip_address);
    return connection;
}

/**
 * @brief Server_Socket::Server_Open
 * @return if open was succeed
 */

bool Server_Socket::Server_Open()
{
    if (this->Is_Open())
        return true;

    if (not this->Create_Socket()) return false;
    if (not this->Reuse_Address()) return false;
    if (not this->Reuse_Port()) return false;

    if (this->Is_IPv6())
    {
        if (not this->Bind_Socket_IPv6())
            return false;
    }

    else
    {
        if (not this->Bind_Socket_IPv4())
            return false;
    }

    if (not this->Set_Keep_Alive()) return false;
    if (not this->Set_Listen_Socket()) return false;

    is_open = true;
    return true;
}

/**
 * @brief Server_Socket::Server_Close
 * @details Close connection and socket
 */

void Server_Socket::Server_Close()
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
 * @return connection for service
 */

Server_Connection* Server_Socket::Connection_Accept() const
{
    if (this->Is_IPv6())
        return this->Accept_IPv6();

    return this->Accept_IPv4();
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

void Server_Socket::Set_Address_Family(ADDRESS_FAMILY _family)
{
    family = _family;
}

bool Server_Socket::Is_IPv4() const
{
    return family == IP_V4;
}

bool Server_Socket::Is_IPv6() const
{
    return family == IP_V6;
}

/**
 * @brief Server_Socket::Is_Open
 * @return true if medium is open
 */

bool Server_Socket::Is_Open() const
{
    return is_open;
}

int Server_Socket::C_Address_Family() const
{
    if (this->Is_IPv6())
        return PF_INET6;

    return PF_INET;
}
