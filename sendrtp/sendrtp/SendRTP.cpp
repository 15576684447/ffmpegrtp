/****************************************************************************
filename:           SendRTP.cpp
Author:             linshufei
Date:               2017/9/13
Discription:

*****************************************************************************/
#include "SendRTP.h"
#include <iostream>

using namespace jrtplib;

#define MAXLEN    (RTP_DEFAULTPACKETSIZE - 100)

SendRTP::SendRTP(void){}
SendRTP::~SendRTP(void){}

void SendRTP::CheckError(int rtperr){
    if (rtperr < 0){
        std::cout << "ERROR: " << RTPGetErrorString(rtperr) << std::endl;
        exit(-1);
    }
}

void SendRTP::SendH264Nalu(uint8_t *h264buf, int bufLen){
    int status;
    uint8_t *pSendBuf;

    pSendBuf = h264buf;
    if (bufLen <= MAXLEN)   //dataSize С����󳤶�
    {
        sess.SetDefaultMark(true);
        status = sess.SendPacket((void *)&pSendBuf[0], bufLen);
        CheckError(status);
        printf("send_packt 0 len = %d\n", bufLen);
    }
    else if (bufLen > MAXLEN)   //dataSize ������󳤶�
    {
        int sendPacket = 0;
        int allPacket = 0;
        int overData = 0;
        int iSendLen;

        allPacket = bufLen / MAXLEN;
        overData = bufLen % MAXLEN;
        sendPacket = 0;
        while ((sendPacket < allPacket) || ((sendPacket == allPacket) && (overData > 0)))
        {
            printf("send_packet = %d \n", sendPacket);
            /* the first packet or the second last packet */
            if ((0 == sendPacket) || (sendPacket < allPacket && 0 != sendPacket))
            {
                sess.SetDefaultMark(false);
                status = sess.SendPacket((void *)&pSendBuf[sendPacket * MAXLEN], MAXLEN);
                CheckError(status);
                sendPacket++;
            }
            /* the last packet */
            else if (((allPacket == sendPacket) && overData>0) || ((sendPacket == (allPacket - 1)) && overData == 0))
            {
                sess.SetDefaultMark(true);

                if (overData > 0)
                {
                    iSendLen = bufLen - sendPacket * MAXLEN;
                }
                else
                {
                    iSendLen = MAXLEN;
                }

                status = sess.SendPacket((void *)&pSendBuf[sendPacket * MAXLEN], iSendLen);
                CheckError(status);
                sendPacket++;
            }
        }
    }
}

void SendRTP::SendJPEG(uint8_t* JPEGBuf, int bufLen)
{
	int status;
	uint8_t *pSendBuf;

	pSendBuf = JPEGBuf;
	if (bufLen <= MAXLEN)   //dataSize С����󳤶�
	{
		sess.SetDefaultMark(true);
		status = sess.SendPacket((void *)&pSendBuf[0], bufLen);
		CheckError(status);
		printf("send_packt 0 len = %d\n", bufLen);
	}
	else if (bufLen > MAXLEN)   //dataSize ������󳤶�
	{
		int sendPacket = 0;
		int allPacket = 0;
		int overData = 0;
		int iSendLen;

		allPacket = bufLen / MAXLEN;
		overData = bufLen % MAXLEN;
		sendPacket = 0;
		while ((sendPacket < allPacket) || ((sendPacket == allPacket) && (overData > 0)))
		{
			printf("send_packet = %d \n", sendPacket);
			/* the first packet or the second last packet */
			if ((0 == sendPacket) || (sendPacket < allPacket && 0 != sendPacket))
			{
				sess.SetDefaultMark(false);
				status = sess.SendPacket((void *)&pSendBuf[sendPacket * MAXLEN], MAXLEN);
				CheckError(status);
				sendPacket++;
			}
			/* the last packet */
			else if (((allPacket == sendPacket) && overData>0) || ((sendPacket == (allPacket - 1)) && overData == 0))
			{
				sess.SetDefaultMark(true);

				if (overData > 0)
				{
					iSendLen = bufLen - sendPacket * MAXLEN;
				}
				else
				{
					iSendLen = MAXLEN;
				}

				status = sess.SendPacket((void *)&pSendBuf[sendPacket * MAXLEN], iSendLen);
				CheckError(status);
				sendPacket++;
			}
		}
	}

}


void SendRTP::init(void)
{
    #ifdef WIN32  
    WSADATA dat;
    WSAStartup(MAKEWORD(2, 2), &dat);
    #endif // WIN32 

    int status;

    //RTPSession sess;
    uint16_t portBase = 6666;  //local portbase
    uint16_t destPort = 6664;
    uint8_t destIP[] = { 127, 0, 0, 1 };   //Ŀ��IP��ַ

    RTPUDPv4TransmissionParams transParams;   //�������
    RTPSessionParams sessParams;  //�Ự����

    // set h264 param
    sessParams.SetUsePredefinedSSRC(true);  //����ʹ��Ԥ�ȶ����SSRC
    sessParams.SetOwnTimestampUnit(1.0 / 90000.0); // ���ò��������1.0/9000.0��ʾһ�����9000��samples��һ��Ҫ���ã�����RTCP Sender ��������
    sessParams.SetAcceptOwnPackets(true);   //�����Լ����͵����ݰ�

    transParams.SetPortbase(portBase);
    status = sess.Create(sessParams, &transParams);
    CheckError(status);

    RTPIPv4Address addr(destIP, destPort);
    status = sess.AddDestination(addr);
    CheckError(status);

    sess.SetDefaultTimestampIncrement(3600);// ����ʱ������Ӽ��
    sess.SetDefaultPayloadType(96);
    sess.SetDefaultMark(true);//��Ҫ�¼���־
}

