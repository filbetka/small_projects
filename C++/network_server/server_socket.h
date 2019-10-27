#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include <string>
using namespace std;


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
        bool Connection_Open();
        void Connection_Close();
        int Connection_Accept();

    public:

        void Set_Connections_Number(int number);
        bool Is_Open();

};


#endif //SERVER_SOCKET_H
