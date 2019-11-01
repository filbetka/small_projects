#ifndef SERVER_LISTENER_H
#define SERVER_LISTENER_H

#include "../socket/server_socket.h"
#include <thread>


class Server_Listener
{

    public:

        explicit Server_Listener(
            Server_Socket& socket);

    private:

        Server_Socket& server_socket;
        Server_Connection* accepted;

        thread listener_thread;
        bool is_running;

    public:

        void Run();
        void Start();
        void Join();
        void Clear();

        Server_Connection* Accepted_Connection() const;
        bool Is_Running() const;
        bool Is_Empty() const;

};


#endif //SERVER_LISTENER_H
