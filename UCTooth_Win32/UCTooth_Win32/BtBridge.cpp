/**
 * $File: BtBridge.cpp $
 * $Date: 2020-07-30 22:51:11 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright © 2020 by Shen, Jen-Chieh $
 */
#include "./BtBridge.h"

// TUTORIAL: https://www.winsocketdotnetworkprogramming.com/winsock2programming/winsock2advancedotherprotocol4p.html

UCTOOTH_C_BEG
UCTOOTH_NS_BEG

SOCKET btSocket = -1;

#define BUF_LEN 512
char* recvbuf = nullptr;

int Connect(BTH_ADDR btAddr)
{
    WSADATA wsd;

    if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
    {
        printf("[ERROR] Unable to load Winsock! Error code is %d\n", WSAGetLastError());
        return 1;
    }

    SOCKADDR_BTH sockAddr = { 0 };

    int error = 0;

    btSocket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.addressFamily = AF_BTH;
    sockAddr.serviceClassId = RFCOMM_PROTOCOL_UUID;
    sockAddr.port = BT_PORT_ANY;
    sockAddr.btAddr = btAddr;

    error = connect(btSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr));
    if (error == SOCKET_ERROR)
    {
        printf("[ERROR] Network exception, when connect: %d\n", error);
        return error;
    }

    return 0;
}

void Close()
{
    closesocket(btSocket);
    WSACleanup();
}

int Send(char msg[])
{
    int error = 0;
    error = send(btSocket, msg, strlen(msg), 0);

    if (error == SOCKET_ERROR)
    {
        printf("[ERROR] Network exception, when send: %d\n", error);
        return error;
    }

    return error;
}

void Recv(char msg[])
{
    int error = recv(btSocket, msg, BUF_LEN, 0);

    if (error > 0)
        printf(" %d Bytes received from sender\n", error);
    else if (error == 0)
        printf("Connection was closed by peer!\n");
    else
        printf("recv() failed with error code %d\n", WSAGetLastError());
}

UCTOOTH_NS_END
UCTOOTH_C_END
