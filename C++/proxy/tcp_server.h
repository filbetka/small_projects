#ifndef PROXY_TCP_SERVER_H
#define PROXY_TCP_SERVER_H

#include <string>


class Tcp_Server
{

    public:

        Tcp_Server();

    private:

        // server data
        int server_socket;
        int server_connect;
        int server_port;

        // status
        bool is_open;

    public:

        bool Open();
        void Close();
        void Accept();
        void Disconnect();

    public:

        // read and write
        void Write(std::string data);
        void Write(char* data, size_t size);
        void Read(char* buffer, size_t size);
        std::string Read();

};

#endif //PROXY_TCP_SERVER_H
