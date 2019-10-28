#include <iostream>
#include "network_server.h"


int main()
{
    // open connection
    Network_Server server(1100);
    server.Server_Open();
    if (not server.Is_Open())
        return 0;

    server.Set_Read_Timeout(3000);
    server.Connection_Accept(false);

    Server_Connection connection =
        server.Connection(0);

    // information for user
    cout << "Start transmission: " << endl;

    // write and read data
    for (int k = 0; k < 10; ++k)
    {
        cout << "read: ";
        cout << connection.Read();
        cout << "\t";

        string data = "Hello";

        cout << "write: " << data;
        connection.Write(data);
        cout << endl;
    }

    connection.Disconnect();
    server.Server_Close();
    return 0;
}