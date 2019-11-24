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

/**
 * @brief Server_Socket::Server_Socket
 * @param port - server port where
 * server will be available.
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

/**
 * @brief Server_Socket::Create_Socket
 * @details Create and validate socket.
 * @return if successful
 */

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

/**
 * @brief Server_Socket::Reuse_Address
 * @details Set and validate reuse address option.
 * @return if successful
 */

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

/**
 * @brief Server_Socket::Reuse_Port
 * @details Set and validate reuse port option.
 * @return if successful
 */

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

/**
 * @brief Server_Socket::Bind_Socket_IPv4
 * @details Bind server data to socket for IPv4.
 * @return if successful
 */

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

/**
 * @brief Server_Socket::Bind_Socket_IPv6
 * @details Bind server data to socket for IPv6.
 * @return if successful
 */

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

/**
 * @brief Server_Socket::Set_Keep_Alive
 * @details Set keep alive option to socket.
 * @return if successful
 */

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

/**
 * @brief Server_Socket::Set_Listen_Socket
 * @details Enable listen clients queue.
 * @return if successful
 */

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

/**
 * @brief Server_Socket::Accept_IPv4
 * @details Accept and display information
 * about new client that connected to server.
 * @return server connection object
 */

auto Server_Socket::Accept_IPv4() const
        -> Server_Connection*
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

/**
 * @brief Server_Socket::Accept_IPv6
 * @details Accept and display information
 * about new client that connected to server.
 * @return server connection object
 */

auto Server_Socket::Accept_IPv6() const
        -> Server_Connection*
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
 * @details Make all operations to open server.
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
 * @return connection object for service
 */

auto Server_Socket::Connection_Accept() const
        -> Server_Connection*
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

/**
 * @brief Server_Socket::Set_Address_Family
 * @param _family - address family (IPv4, IPv6)
 */

void Server_Socket::Set_Address_Family(ADDRESS_FAMILY _family)
{
    family = _family;
}

/**
 * @brief Server_Socket::Is_IPv4
 * @return if family address is IPv4
 */

bool Server_Socket::Is_IPv4() const
{
    return family == IP_V4;
}

/**
 * @brief Server_Socket::Is_IPv6
 * @return if family address is IPv6
 */

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

/**
 * @brief Server_Socket::C_Address_Family
 * @return Linux C macro value for address family.
 */

int Server_Socket::C_Address_Family() const
{
    if (this->Is_IPv6())
        return PF_INET6;

    return PF_INET;
}
