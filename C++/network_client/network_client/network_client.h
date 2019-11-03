#ifndef NETWORK_CLIENT_H
#define NETWORK_CLIENT_H

#include "socket/client_socket.h"


class Network_Client
{

    public:

        Network_Client(string address, int port);
        ~Network_Client();

    private:

        Client_Socket client_socket;
        int read_timeout_ms;

    public:

        // connection
        bool Connection_Open();
        void Connection_Close();
        bool Is_Connected() const;

        // read and write
        void Write(const string& data);
        string Read();

        void Write(char* data, size_t size);
        void Read(char* buffer, size_t size);

        void Set_Read_Timeout(int timeout_ms);

};


#endif //NETWORK_CLIENT_H
