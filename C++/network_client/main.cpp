#include <iostream>
#include "network_client.h"


int main()
{
//    // initialize
//    string address;
//    int port;
//
//    // get base data
//    cout << "Type [address port]: ";
//    cin >> address >> port;

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
    }

    return 0;
}