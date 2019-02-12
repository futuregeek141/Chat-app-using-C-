#include <iostream>
#include <winsock2.h>
#include <fstream>
#include <cstring>
#pragma comment "C:\Program Files (x86)\CodeBlocks\MinGW\lib\libws2_32.a";
using namespace std;

int main()
{
    char data[100];
    fstream file("Record.txt",ios::out | ios::app | ios::in);
    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN addr;

    WSAStartup(MAKEWORD(2,0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555);

    connect(server, (SOCKADDR *)&addr, sizeof(addr));

    cout << "Connected to server!" << endl;
    char buffer[1024];
    cout << "\nType \"Over\" to end sending message to client: " << endl;
    cout << "\nType \"Exit\" to conclude conversation: " << endl;
    file.seekg(0,ios::beg);
    while(!file.eof())
    {
        file.getline(data,100);
        cout<<data<<endl;
    }
    while(1)
    {
        m:
        cout << "\nClient: ";
        cin.getline(buffer,1024);
        if(!strcmp(buffer,"Over") || !strcmp(buffer,"over"))
        {

        }
        else
            file << "Client: " << buffer << endl << endl;
        if(!strcmp(buffer,"Exit") || !strcmp(buffer,"exit"))
            {
                send(server, buffer, sizeof(buffer), 0);
                closesocket(server);
                cout<<"\n\nClient disconnected:" << endl << endl;
                break;
            }
        send(server, buffer, sizeof(buffer), 0);
        if(!strcmp(buffer,"Over") || !strcmp(buffer,"over"))
            {
                memset(buffer, 0, sizeof(buffer));
                goto l;
            }
        while(1)
            {
                memset(buffer, 0, sizeof(buffer));
                cout << "\nClient: ";
                cin.getline(buffer,1024);
                if(!strcmp(buffer,"Over") || !strcmp(buffer,"over"))
                {

                }
                else
                    file << "Client: " << buffer << endl << endl;
                if(!strcmp(buffer,"Exit") || !strcmp(buffer,"exit"))
                {
                    closesocket(server);
                    cout<<"\n\nClient disconnected:" << endl << endl;
                    break;
                }
                send(server, buffer, sizeof(buffer), 0);
                if(strcmp(buffer,"Over")==0 || strcmp(buffer,"over")==0)
                    break;
            }
        if(!strcmp(buffer,"Exit") || !strcmp(buffer,"exit"))
        {
            send(server, buffer, sizeof(buffer), 0);
            break;
        }
        l:
        memset(buffer, 0, sizeof(buffer));
        recv(server, buffer, sizeof(buffer), 0);
        if(!strcmp(buffer,"Over") || !strcmp(buffer,"over"))
        {

        }
        else
            file << "Server: " << buffer << endl << endl;
        if(!strcmp(buffer,"Over") || !strcmp(buffer,"over"))
            {
                memset(buffer, 0, sizeof(buffer));
                goto m;
            }
        while(strcmp(buffer,"Over")!=0 || strcmp(buffer,"over")!=0)
        {
            cout << "\nServer :" << buffer << endl;
            memset(buffer, 0, sizeof(buffer));
            recv(server, buffer, sizeof(buffer), 0);
            if(!strcmp(buffer,"Over") || !strcmp(buffer,"over"))
            {

            }
            else
                file << "Server: " << buffer << endl << endl;
            if(!strcmp(buffer,"Over")!=0 || !strcmp(buffer,"over"))
                break;
        }
    }
    closesocket(server);
    WSACleanup();
    cout << "Socket closed." << endl << endl;
    file.close();
    return 0;
}
