#include <iostream>
#include <unistd.h>
#include "network_client.h"


int main()
{
    // open connection
    Network_Client client("127.0.0.1", 1100);
    client.Connection_Open();
    if (not client.Is_Open())
        return 0;

    // information for user
    cout << "Start transmission: " << endl;

    // write and read data
    for (int k = 0; k < 10; ++k)
    {
        string data = "Hello";

        cout << "write: " << data << "\t";
        client.Write(data);

        cout << "read: ";
        cout << client.Read();
        cout << endl;

        sleep(1);
    }

    return 0;
}