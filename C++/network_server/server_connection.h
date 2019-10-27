#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include <string>
using namespace std;


class Server_Connection
{

    public:

        explicit Server_Connection(int connection);

    private:

        int server_connection;
        int read_timeout_ms;
        bool is_connected;

    public:

        void Disconnect();

    public:

        void Write(string data);
        string Read();

        void Write(char* data, size_t size);
        void Read(char* buffer, size_t size);

    public:

        bool Is_Connected();
        void Set_Read_Timeout(int timeout_ms);

};


#endif //SERVER_CONNECTION_H
