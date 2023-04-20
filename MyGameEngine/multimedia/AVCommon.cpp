#include "AVCommon.h"

void SaveFrame(AVFrame *pFrame, int width, int height, int iFrame)
{
    FILE *pFile;
    char szFilename[32];
    int  y, x;

    // Open file
    sprintf(szFilename, "frame%04d.ppm", iFrame);
    pFile=fopen(szFilename, "wb");
    if(pFile==NULL)
        return;

    // Write header
    fprintf(pFile, "P6\n%d %d\n255\n", width, height);
    // Write pixel data
    for(y=0; y<height; y++)
        for (x = 0; x < width; x++)
        {
            //fwrite(pFrame->data[0] + y*pFrame->linesize[0] + x * 4, 1, 3, pFile);
            fputc(*(pFrame->data[0] + y*pFrame->linesize[0] + x * 4 + 2), pFile);
            fputc(*(pFrame->data[0] + y*pFrame->linesize[0] + x * 4 + 1), pFile);
            fputc(*(pFrame->data[0] + y*pFrame->linesize[0] + x * 4 + 0), pFile);
        }
    // Close file
    fclose(pFile);
}

void SaveFrameYUV420(AVFrame *pFrame, int width, int height, int iFrame)
{
    FILE *pFile;
    char szFilename[32];
    int  y;

    // Open file
    sprintf(szFilename, "frame%04d.yuv", iFrame);
    pFile=fopen(szFilename, "wb");
    if(pFile==NULL)
        return;

    // Write pixel data
    for(y=0; y<height; y++)
    {
        fwrite(pFrame->data[0] + y * pFrame->linesize[0], 1, width, pFile);
    }
    for(y=0; y<height/2; y++)
    {
        fwrite(pFrame->data[1] + y * pFrame->linesize[1], 1, width/2, pFile);
    }
    for(y=0; y<height/2; y++)
    {
        fwrite(pFrame->data[2] + y * pFrame->linesize[2], 1, width/2, pFile);
    }
    // Close file
    fclose(pFile);
}
