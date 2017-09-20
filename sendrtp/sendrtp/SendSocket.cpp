/****************************************************************************
filename:           SendSocket.cpp
Author:             linshufei
Date:               2017/9/19
Discription:

*****************************************************************************/

#include "SendSocket.h"


CSendSocket::CSendSocket()
{
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    //�½��ͻ���socket
    sockClient = socket(AF_INET, SOCK_STREAM, 0);
    //����Ҫ���ӵķ���˵�ַ
    addrServer.sin_addr.S_un.S_addr = inet_addr("192.168.179.128");
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(8000);
}


CSendSocket::~CSendSocket()
{
    closesocket(sockClient);
    WSACleanup();

}

int CSendSocket::Connect2Server()
{
    int ret =connect(sockClient, (SOCKADDR*)& addrServer, sizeof(SOCKADDR));
    std::cout << ret << std::endl;
    return 0;
}

int CSendSocket::Send2Server(char* pData ,int size)
{
    //write header
    char* pictureBuf;
    pictureBuf = new char[MAX_IMAGE_SIZE];

    SImageHeader imageHeader;
    imageHeader.width = width;
    imageHeader.height = height;
    imageHeader.dataSize = size;
    imageHeader.dataOffset = sizeof(imageHeader);
    
    memcpy(pictureBuf, &imageHeader, sizeof(imageHeader));
    memcpy(pictureBuf + sizeof(imageHeader), pData, size);

    //send picture
    send(sockClient, pictureBuf, size + sizeof(imageHeader), 0);

    delete pictureBuf;
    return 0;
}

int CSendSocket::GetSize(int w, int h)
{
    width = w;
    height = h;
    return 0;
}