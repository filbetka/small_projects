#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include "../tools/server_connection.h"


class Server_Socket
{

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

    public:

        // connection
        bool Server_Open();
        void Server_Close();
        Server_Connection* Connection_Accept() const;

    public:

        void Set_Connections_Number(int number);
        bool Is_Open() const;

};


#endif //SERVER_SOCKET_H
