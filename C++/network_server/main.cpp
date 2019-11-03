#include <iostream>
#include <algorithm>
#include "network_server/network_server.h"

void Remove_Char(string& data, char to_remove)
{
    data.erase(
        remove(
            data.begin(),
            data.end(),
            to_remove
        ),
        data.end()
    );
}

int main()
{
    // open connection
    Network_Server server(1100);
    server.Set_Address_Family(Server_Socket::IP_V6);
    server.Server_Open();
    if (not server.Is_Open())
        return 0;

    server.Set_Read_Timeout(1000);
    bool working = true;

    while (working)
    {
        if (server.Waiting_Completed())
            server.Connection_Accept(true);

        server.Waiting_For_Accept(0);
        Connections_List connections =
            server.Connections();

        for (auto connection : connections)
        {
            // information for user
            cout << connection->Client_Address() << "\t";

            // write data
            cout << "write: " << "Hello";
            connection->Write("Hello\n");
            cout << "\t";

            // read data
            string data = connection->Read();
            Remove_Char(data, '\n');

            cout << "read: ";
            cout << data << endl;

            // analise data
            if (data == "x")
                working = false;
        }
    }

    server.Server_Close();
    return 0;
}