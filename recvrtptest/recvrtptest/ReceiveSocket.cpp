#include "ReceiveSocket.h"


CReceiveSocket::CReceiveSocket()
{
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    sockServer = socket(AF_INET, SOCK_STREAM, 0);
    addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //INADDR_ANY��ʾ�κ�IP
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(6000); //�󶨶˿�6000
    bind(sockServer, (SOCKADDR*)& addrServer, sizeof(SOCKADDR));

}


CReceiveSocket::~CReceiveSocket()
{
    closesocket(sockClient);
    WSACleanup();

}

int CReceiveSocket::Listen()
{
    listen(sockServer, 1); //1Ϊ�ȴ�������Ŀ
    std::cout << "��������������" << std::endl << "������" << std::endl;
    return 0;
}

int CReceiveSocket::AcceptFromClient()
{
    int len = sizeof(SOCKADDR);
    sockClient = accept(sockServer, (SOCKADDR*)& addrClient, &len);
    return 0;
}

int CReceiveSocket::ReceiveFromClient(char* pData, int size)
{
    recv(sockClient, pData, size, 0);
    return 0;
}

int CReceiveSocket::GetSize(int &w, int &h)
{
    width = w;
    height = h;
    return 0;
}