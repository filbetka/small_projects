#ifndef NETWORK_SERVER_H
#define NETWORK_SERVER_H

#include "server_socket.h"
#include "server_connection.h"
#include "server_listener.h"
#include <vector>
using Connections_List =
    vector<Server_Connection>;


class Network_Server
{

    public:

        explicit Network_Server(int port=1100);

    private:

        // server data
        Server_Socket server_socket;
        Connections_List connections;

        // accept listener
        Server_Listener listener;

        // others
        int max_connections;
        int read_timeout_ms;

    public:

        // server
        bool Server_Open();
        void Server_Close();
        bool Is_Open() const;

        // management
        void Connection_Accept(bool async);
        void Wait_For_Accept(int ms);
        Server_Connection Connection(int number);

    public:

        void Set_Connections_Number(int number);
        void Set_Read_Timeout(int timeout_ms);

};


#endif //NETWORK_SERVER_H
