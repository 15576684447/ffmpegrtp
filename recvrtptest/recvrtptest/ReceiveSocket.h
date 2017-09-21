/****************************************************************************
filename:           ReceiveSocket.h
Author:             linshufei
Date:               2017/9/19
Discription:

*****************************************************************************/

#pragma once
#include <winsock2.h>
#include <stdio.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
#define MAX_IMAGE_SIZE 1920 * 1080 

typedef struct SImageHeader
{
    int width;          //ͼƬ�Ŀ��
    int height;         //ͼƬ�ĸ߶�
    int serverType;     //����ķ�������
    int dataOffset;     //ͼƬ����ͷ��λ��
    int dataSize;       //ͼƬ��С
} SImageHeader;

class CReceiveSocket
{
public:
    CReceiveSocket();
    ~CReceiveSocket();
    WSADATA wsaData;
    SOCKET sockServer;          //������Socket
    SOCKADDR_IN addrServer;     //��������ַ
    SOCKET sockClient;          //�ͻ���Socket
    SOCKADDR_IN addrClient;     //�ͻ��˵�ַ

    char* pData;
    int width;
    int height;
    int imageSize;

    int Listen();
    int AcceptFromClient();
    int ReceiveFromClient(char* recvBuf, int recvBufLen);
    int SetSize(int &w, int &h, int &size);
};


