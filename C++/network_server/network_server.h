#ifndef NETWORK_SERVER_H
#define NETWORK_SERVER_H

#include "abstract_medium.h"
#include <vector>


class Network_Server : public Abstract_Medium
{

    public:

        Network_Server(int port=1100);
        ~Network_Server();

    private:

        // server data
        int server_socket;
        int server_port;

        // client connections
        //vector<int> connections;
        int server_connect;
        int connections_number;
        int read_timeout_ms;

    public:

        // connection
        bool Connection_Open();
        void Connection_Close();
        void Connection_Accept();
        void Disconnect();

    public:

        // read and write
        void Write(string data);
        string Read();

        void Write(char* data, size_t size);
        void Read(char* buffer, size_t size);

        void Set_Connections_Number(int number);
        void Set_Read_Timeout(int timeout_ms);

};


#endif //NETWORK_SERVER_H
