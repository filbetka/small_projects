#include <iostream>
#include "network_client.h"


int main()
{
    Network_Client client("127.0.0.1", 1100);
    //client;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}