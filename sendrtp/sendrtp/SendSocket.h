#pragma once
#include <winsock2.h>
#include <stdio.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
#define MAX_IMAGE_SIZE 1920 * 1080 
#define DATA_ADDR 4;

class CSendSocket
{
public:
    WSADATA wsaData;
    SOCKET sockClient;  //�ͻ���Socket
    SOCKADDR_IN addrServer;  //����˵�ַ

    int width;
    int height;

    CSendSocket();
    ~CSendSocket();
    int Connect2Server();
    int Send2Server(char* pData, int size);
    int GetSize(int w, int h);
};

