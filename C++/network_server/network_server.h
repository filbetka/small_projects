#ifndef NETWORK_SERVER_H
#define NETWORK_SERVER_H

#include "server_socket.h"
#include "server_connection.h"
#include <vector>


class Network_Server
{

    public:

        explicit Network_Server(int port=1100);

    private:

        // server data
        Server_Socket server_socket;
        Server_Connection* connections;

        // others
        int max_connections;
        int connections_number;
        int read_timeout_ms;

    public:

        // connection
        bool Connection_Open();
        void Connection_Close();

    public:

        void Set_Connections_Number(int number);
        void Set_Read_Timeout(int timeout_ms);

};


#endif //NETWORK_SERVER_H
