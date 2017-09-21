/****************************************************************************
filename:           JPEGEncoder.cpp
Author:             linshufei
Date:               2017/9/15
Discription:

*****************************************************************************/
#pragma once
#include "JPEGEncoder.h"
#include <iostream>

CJPEGEncoder::CJPEGEncoder(int width, int height)
{
    //ע�������
    avcodec_register_all();

    //Ѱ�ұ�����
    pCodec = avcodec_find_encoder(AV_CODEC_ID_MJPEG);
    if (pCodec == NULL)
    {
        printf("Fail to get encoder !\n");
    }

    //Param that must set
    pCodecCtx = avcodec_alloc_context3(pCodec);
    if (pCodecCtx == NULL)
    {
        printf("Fail to get decoder context !\n");
    }

    //ͼ��ɫ�ʿռ�ĸ�ʽ������ʲô����ɫ�ʿռ�������һ�����ء�
    pCodecCtx->pix_fmt = AV_PIX_FMT_YUVJ444P;

    //�������������������
    pCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;

    //��������Ƶ֡��С��������Ϊ��λ��
    pCodecCtx->width = width;
    pCodecCtx->height = height;

    //֡�ʵĻ�����λ��time_base.numΪʱ���߷��ӣ�time_base.denΪʱ���߷�ĸ��֡��=����/��ĸ��
    pCodecCtx->time_base.num = 1;
    pCodecCtx->time_base.den = 25;

    //Output some information
    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0){
        printf("Could not open codec.");
    }

    //init picture
    pPicture = av_frame_alloc();  //Allocate an AVFrame and set it to a default value
    int size = avpicture_get_size(pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height);
    pictureBuf = (uint8_t *)av_malloc(size);
    if (!pictureBuf)
    {
        std::cout << "av_malloc picture_buf failed!" << std::endl;
    }
    avpicture_fill((AVPicture *)pPicture, pictureBuf, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height);

    //new packet
    av_new_packet(&packet,size);

}

CJPEGEncoder::~CJPEGEncoder()
{
    //���ٺ���
    av_free(pCodec);
    av_free(pCodecCtx);
    av_free(pPicture);
    av_free(pictureBuf);
    av_free_packet(&packet);
}

int CJPEGEncoder::Encode(unsigned char* data)
{
    //Write Header д�ļ�ͷ
    int ySize = pCodecCtx->width * pCodecCtx->height;
    memcpy(pictureBuf, data, ySize * 3 / 2);
    pPicture->data[0] = pictureBuf;                    // Y
    pPicture->data[1] = pictureBuf + ySize;            // U
    pPicture->data[2] = pictureBuf + ySize * 5 / 4;    // V

    //Encode
    int gotPicture;
    int ret = avcodec_encode_video2(pCodecCtx, &packet, pPicture, &gotPicture);

    if (ret < 0){
        printf("Encode Error.\n");
        return -1;
    }

    if (gotPicture == 1)
    {
           printf("Encode Successful.\n");
    }

    return 0;

}