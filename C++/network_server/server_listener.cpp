#include "server_listener.h"

/**
 * @class Server_Listener
 * @details Waiting for new connections
 * in another thread.
 */

Server_Listener::Server_Listener(Server_Socket& socket):
    server_socket(socket)
{
    accepted_connection = -1;
    is_running = false;
}

/**
 * @brief Server_Listener::Thread_Method
 * @details The method is called by Start method
 * in another thread. It waiting for new connection
 * to accept.
 */

void Server_Listener::Thread_Method()
{
    // start running
    is_running = true;

    // processing
    accepted_connection =
        server_socket.Connection_Accept();

    // finished
    is_running = false;
}

/**
 * @brief Server_Listener::Start
 * @details Prepare listener and start new thread.
 */

void Server_Listener::Start()
{
    accepted_connection = -1;
    listener_thread = thread {
        &Server_Listener::Thread_Method,
        this
    };
}

/**
 * @brief Server_Listener::Accepted_Connection
 * @return new accepted connection.
 */

int Server_Listener::Accepted_Connection() const
{
    return accepted_connection;
}

/**
 * @brief Server_Listener::Is_Running
 * @return if thread is running.
 * It means that waiting for new connection.
 */

bool Server_Listener::Is_Running() const
{
    return is_running;
}
