//
//  binarttest.cpp
//  OpenCvTest
//
//  Created by 肖家凯 on 28/03/2017.
//  Copyright © 2017 肖家凯. All rights reserved.
//

#include <stdio.h>
//图像的二值化
//By MoreWindows (http://blog.csdn.net/MoreWindows)
#include <opencv2/opencv.hpp>
using namespace std;

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

IplImage *g_pGrayImage = NULL;
IplImage *g_pBinaryImage = NULL;


int main( int argc, char** argv )
{
    const char *pstrWindowsSrcTitle = "原图(http://blog.csdn.net/MoreWindows)";
    // 从文件中加载原图
    IplImage *pSrcImage = cvLoadImage("/Users/XiaoJiaKai/Desktop/grayTest/nykeyboard.jpg", CV_LOAD_IMAGE_UNCHANGED);
    
    // 转为灰度图
    g_pGrayImage =  cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);
    cvCvtColor(pSrcImage, g_pGrayImage, CV_BGR2GRAY);
    
    // 创建二值图
    g_pBinaryImage = cvCreateImage(cvGetSize(g_pGrayImage), IPL_DEPTH_8U, 1);
    
    // 显示原图
    cvNamedWindow(pstrWindowsSrcTitle, CV_WINDOW_AUTOSIZE);
    cvShowImage(pstrWindowsSrcTitle, pSrcImage);
    // 创建二值图窗口
    cvNamedWindow("test", CV_WINDOW_AUTOSIZE);
    // 转为二值图
    cvThreshold(g_pGrayImage, g_pBinaryImage, 190, 255, CV_THRESH_BINARY);
    // 显示二值图
     ("test", g_pBinaryImage);
    cvWaitKey(0);
    
    cvDestroyWindow(pstrWindowsSrcTitle);
    cvDestroyWindow("test");
    cvReleaseImage(&pSrcImage);
    cvReleaseImage(&g_pGrayImage);
    cvReleaseImage(&g_pBinaryImage);
}
