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
        string server_address;

        int read_timeout_ms;
        bool is_connected;

    public:

        bool Validate() const;
        void Disconnect();

    public:

        void Write(const string& data);
        string Read();

        void Write(char* data, size_t size);
        void Read(char* buffer, size_t size);

    public:

        bool Is_Connected();
        string Client_Address();

        void Set_Read_Timeout(int timeout_ms);
        void Set_Client_Address(string address);

};


#endif //SERVER_CONNECTION_H
