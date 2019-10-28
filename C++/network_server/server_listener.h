#ifndef SERVER_LISTENER_H
#define SERVER_LISTENER_H

#include "server_socket.h"
#include <thread>


class Server_Listener
{

    public:

        explicit Server_Listener(
            Server_Socket& socket);

    private:

        Server_Socket& server_socket;
        int accepted_connection;

        thread listener_thread;
        bool is_running;

    public:

        void Run();
        void Start();
        void Join();

        int Accepted_Connection() const;
        bool Is_Running() const;

};


#endif //SERVER_LISTENER_H
