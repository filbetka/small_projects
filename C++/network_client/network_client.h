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

    public:

        // connection
        bool Connection_Open() override;
        void Connection_Close() override;

        // read and write
        void Write(string data);
        string Read();

        void Write(char* data, size_t size);
        void Read(char* buffer, size_t size);

};


#endif //NETWORK_CLIENT_H
