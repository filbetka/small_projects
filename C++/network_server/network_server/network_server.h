#ifndef NETWORK_SERVER_H
#define NETWORK_SERVER_H

#include "socket/server_socket.h"
#include "tools/server_connection.h"
#include "listener/server_listener.h"
#include <vector>
using Connections_List =
    vector<Server_Connection*>;


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
        void Waiting_For_Accept(int ms);
        bool Accept_Listener_Finished();

        Connections_List Connections();
        Server_Connection* Connection(
            const string& ip) const;

    public:

        void Set_Connections_Number(int number);
        void Set_Read_Timeout(int timeout_ms);
        void Set_Address_Family(
            Server_Socket::ADDRESS_FAMILY family);

};


#endif //NETWORK_SERVER_H
