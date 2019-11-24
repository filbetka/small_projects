#include "server_listener.h"

/**
 * @class Server_Listener
 * @details Waiting for new connections
 * in another thread.
 */

Server_Listener::Server_Listener(Server_Socket& socket):
    server_socket(socket), accepted(nullptr)
{
    is_running = false;
}

/**
 * @brief Server_Listener::Run
 * @details The method is called by Start method
 * in another thread. It waiting for new connection
 * to accept.
 */

void Server_Listener::Run()
{
    // start running
    is_running = true;

    // processing
    accepted = server_socket.Connection_Accept();

    // finished
    is_running = false;
}

/**
 * @brief Server_Listener::Start
 * @details Prepare listener and start new thread.
 */

void Server_Listener::Start()
{
    accepted = nullptr;
    listener_thread = thread {
        &Server_Listener::Run,
        this
    };
}

/**
 * @brief Server_Listener::Join
 * @details Join thread to main thread.
 */

void Server_Listener::Join()
{
    if (listener_thread.joinable())
        listener_thread.join();
}

/**
 * @brief Server_Listener::Clear
 * @details Clear data to default.
 */

void Server_Listener::Clear()
{
    accepted = nullptr;
    is_running = false;
}

/**
 * @brief Server_Listener::Is_Empty
 * @return if has not any connection.
 */

bool Server_Listener::Is_Empty() const
{
    return not accepted;
}

/**
 * @brief Server_Listener::Accepted_Connection
 * @return new accepted connection.
 */

auto Server_Listener::Accepted_Connection() const
        -> Server_Connection*
{
    return accepted;
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
