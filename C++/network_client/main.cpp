#include <iostream>
#include "network_client/network_client.h"


int main()
{
    // open connection
    Network_Client client("127.0.0.1", 1100);
    client.Set_Read_Timeout(3000);
    client.Connection_Open();
    if (not client.Is_Connected())
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