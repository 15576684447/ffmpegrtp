/****************************************************************************
filename:           ReceiveSocket.cpp
Author:             linshufei
Date:               2017/9/19
Discription:

*****************************************************************************/

#include "ReceiveSocket.h"

CReceiveSocket::CReceiveSocket()
{
    pData = new char[MAX_IMAGE_SIZE];
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    sockServer = socket(AF_INET, SOCK_STREAM, 0);
    addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //INADDR_ANY��ʾ�κ�IP
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(6000); //�󶨶˿�6000
    bind(sockServer, (SOCKADDR*)& addrServer, sizeof(SOCKADDR));
}

CReceiveSocket::~CReceiveSocket()
{
    if (pData == NULL)
    {
        delete[] pData;
        pData = NULL;
    }

    closesocket(sockClient);
    WSACleanup();
}

//����
int CReceiveSocket::Listen()
{
    listen(sockServer, 1); //1Ϊ�ȴ�������Ŀ
    std::cout << "��������������" << std::endl << "������" << std::endl;
    return 0;
}

//���������̣�ֱ���пͻ�����������Ϊֹ
int CReceiveSocket::AcceptFromClient()
{
    int len = sizeof(SOCKADDR);
    sockClient = accept(sockServer, (SOCKADDR*)& addrClient, &len);
    return 0;
}

//���տͻ�������
int CReceiveSocket::ReceiveFromClient(char* recvBuf, int recvBufLen)
{
    int pos = 0;
    SImageHeader header;

    int len = recv(sockClient, (char *)&header, sizeof(SImageHeader), 0);
    while (1)
    {
        len = recv(sockClient, &recvBuf[pos], 1024, 0);
        pos += len;
        std::cout << "pos:" << pos << "/"<< header.dataSize <<std::endl;
        if (pos >= header.dataSize)
        {
            break;
        }
    }

    std::cout << "length:" << len << std::endl;
    memcpy(pData, recvBuf, header.dataSize);
    SetSize(header.width, header.height, header.dataSize);
    return 0;
}

int CReceiveSocket::SetSize(int &w, int &h ,int &size)
{
    width = w;
    height = h;
    imageSize = size;
    return 0;
}