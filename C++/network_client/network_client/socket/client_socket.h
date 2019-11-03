#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <string>
using namespace std;


class Client_Socket
{

    public:

        Client_Socket(string address, int port);
        ~Client_Socket();

    private:

        string client_address;
        int client_port;
        int client_socket;
        int address_family;
        bool is_connected;

    private:

        bool Create_Socket();
        bool Set_Timeout();
        bool Connect_IPv4();
        bool Connect_IPv6();

    public:

        // connection
        bool Connection_Open();
        void Connection_Close();

    public:

        bool Is_Connected() const;
        bool Is_IPv4() const;
        bool Is_IPv6() const;
        int Connection() const;

};


#endif //CLIENT_SOCKET_H
