#ifndef NETWORK_CLIENT_H
#define NETWORK_CLIENT_H

#include "abstract_medium.h"


class Network_Client : public Abstract_Medium
{

    public:

        Network_Client(string address, int port);
        ~Network_Client();

    private:

        string client_address;
        int client_port;
        int client_socket;
        int read_timeout_ms;

    public:

        // connection
        bool Connection_Open() final;
        void Connection_Close() final;

        // read and write
        void Write(string data) final;
        string Read() final;

        void Write(char* data, size_t size) final;
        void Read(char* buffer, size_t size) final;

        void Set_Read_Timeout(int timeout_ms);

};


#endif //NETWORK_CLIENT_H
