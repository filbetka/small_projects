#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include "../tools/server_connection.h"


class Server_Socket
{

    public:

        enum ADDRESS_FAMILY
        {
            IP_V4,
            IP_V6
        };

    public:

        explicit Server_Socket(int port);
        ~Server_Socket();

    private:

        // server data
        int server_socket;
        int server_port;
        bool is_open;

        // other data
        int connections_number;
        ADDRESS_FAMILY family;

    public:

        bool Create_Socket();
        bool Reuse_Address();
        bool Reuse_Port();
        bool Bind_Socket();
        bool Set_Keep_Alive();
        bool Set_Listen_Socket();

        // connection
        bool Server_Open();
        void Server_Close();
        Server_Connection* Connection_Accept() const;

    public:

        void Set_Connections_Number(int number);
        void Set_Address_Family(ADDRESS_FAMILY family);
        bool Is_IPv4() const;
        bool Is_IPv6() const;
        bool Is_Open() const;

};


#endif //SERVER_SOCKET_H
