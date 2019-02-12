#include <iostream>
#include <winsock2.h>
#include <cstring>
#pragma comment "C:\Program Files (x86)\CodeBlocks\MinGW\lib\libws2_32.a";

using namespace std;
int main()
{

    WSADATA WSAData;
    SOCKET server, client;
    SOCKADDR_IN serverAddr, clientAddr;

    WSAStartup(MAKEWORD(2,0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5555);

    bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
    while(1)
    {
        listen(server, 0);

        cout << "Listening for incoming connections..." << endl;
        char buffer[1024];
        int clientAddrSize = sizeof(clientAddr);
        if(client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize))
        {
            cout << "Client connected: \n" << endl;
        }
        cout << "\nType \"over\" to end sending message to client: ";
        while((client) != INVALID_SOCKET)
        {
            memset(buffer, 0, sizeof(buffer));
            m:
            recv(client, buffer, sizeof(buffer), 0);
            if(!strcmp(buffer,"Exit") || !strcmp(buffer,"exit"))
            {
                closesocket(client);
                cout<<"\n\nClient disconnected:" << endl << endl;
                break;
            }
            if(!strcmp(buffer,"Over") || !strcmp(buffer,"over"))
            {
                memset(buffer, 0, sizeof(buffer));
                goto l;
            }
            while(strcmp(buffer,"Over")!=0 || strcmp(buffer,"over")!=0)
            {
                cout << "\nClient: " << buffer << endl;
                memset(buffer, 0, sizeof(buffer));
                recv(client, buffer, sizeof(buffer), 0);
                if(!strcmp(buffer,"Exit") || !strcmp(buffer,"exit"))
                {
                    closesocket(client);
                    cout<<"\n\nClient disconnected:" << endl << endl;
                    break;
                }
                if(!strcmp(buffer,"Over") || !strcmp(buffer,"over"))
                    break;
            }
            l:
            cout << "\nServer: ";
            cin.getline(buffer,1024);
            send(client, buffer, sizeof(buffer), 0);
            if(!strcmp(buffer,"Over") || !strcmp(buffer,"over"))
            {
                memset(buffer, 0, sizeof(buffer));
                goto m;
            }
            while(1)
            {
                memset(buffer, 0, sizeof(buffer));
                cout << "\nServer: ";
                cin.getline(buffer,1024);
                send(client, buffer, sizeof(buffer), 0);
                if(strcmp(buffer,"Over")==0 || strcmp(buffer,"over")==0)
                    break;
            }
        }
    }
    return 0;
}
