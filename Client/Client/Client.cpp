
#include "stdafx.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>


using namespace std;

void CleanupWSADLL();

int main()
{
    cout << "\n\nTHIS IS A CLIENT!!!\n\n\n";

    //
    // Step 1. Set up WSA DLL
    //

    SOCKET clientSocket;
    int port = 55555;
    WSADATA wsaData;
    int wsaError;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaError = WSAStartup(wVersionRequested, &wsaData);
    if (wsaError != 0)
    {
        cout << "The Winsock dll not found :(\n";
        return 0;
    }
    else
    {
        cout << "The Winsock dll found :)\n";
        cout << "Status: " << wsaData.szSystemStatus << "\n\n";
    }


    //
    // Step 2. Set up a socket
    //

    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET)
    {
        cout << "Error creating socket: " << WSAGetLastError() << "\n";
        CleanupWSADLL();
        return 0;
    }


    //
    // Step 3. Connect to server
    //

    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr); // OR &service.sin_addr.S_un.S_addr
    // Loopback address. https://www.geeksforgeeks.org/what-is-a-loopback-address/
    clientService.sin_port = htons(port);
    
    if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR)
    {
        cout << "Connection failed: " << WSAGetLastError() <<"\n";
        CleanupWSADLL();
        return 0;
    }
    else
    {
        cout << "Client connection: OK\n";
        cout << "Ready to send and receive data.\n\n";
    }
    system("pause");







    CleanupWSADLL();

    return 0;
}



void CleanupWSADLL()
{
    // Shut down WSA DLL
    int cleanupError = WSACleanup();
    cout << "\n\n\n\n\n\nCleanup result: " << cleanupError << "\n\n";
}