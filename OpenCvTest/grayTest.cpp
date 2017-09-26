//  grayTest.cpp
//  OpenCvTest
//
//  Created by 肖家凯 on 23/03/2017.
//  Copyright © 2017 肖家凯. All rights reserved.
//  种子连通域算法。需要大量栈空间存储相连的点
//  漫水填充算法
#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
using namespace std;
using namespace cv;
void test(IplImage* img);
Mat imgResize(Mat img);
IplImage* cvimgResize(IplImage* img);
int main(int argc, char** argv)
{
    
    //const char* imagename = "/Users/XiaoJiaKai/Desktop/10.png";
    const char* imagename = "/Users/XiaoJiaKai/sceencap.jpg";
   //const char* imagename = "/JNI_after.png";
    IplImage* img = cvLoadImage(imagename);
     //cvShowImage("原图", img);
    if(!img)
    {
        fprintf(stderr, "Can not load image %s\n", imagename);
        fprintf(stderr, "if you want to load this img, please retry");
        return -1;
    }
    
    if( !img->imageData ) // 检查是否正确载入图像
        return -1;
    test(img);
    
    return 0;
    
}
void test(IplImage* img)
{
    IplImage *g_pBinaryImage = NULL;
    IplImage *g_pGrayImage = NULL;
    // 转为灰度图
    g_pGrayImage =  cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
    cvCvtColor(img, g_pGrayImage, CV_BGR2GRAY);

    // 创建二值图
    g_pBinaryImage = cvCreateImage(cvGetSize(g_pGrayImage), IPL_DEPTH_8U, 1);
    // 转为二值图
    cvThreshold(g_pGrayImage, g_pBinaryImage, 120, 255, CV_THRESH_BINARY);
    //cvShowImage("img_dilate", cvimgResize(g_pBinaryImage));
    //cvWaitKey(-1);
    //漫水填充算法将连通区域变色
    cvFloodFill(g_pGrayImage, cvPoint(0 ,1), CV_RGB(255, 255, 255), cvScalar(20, 20, 20),cvScalar(20, 20, 20));

    IplImage *img_erode = cvCreateImage(cvGetSize(g_pGrayImage), 8, 1);
    IplImage *img_dilate = cvCreateImage(cvGetSize(g_pGrayImage), 8, 1);
    
    cvErode( g_pBinaryImage,img_erode, NULL,1); //腐蚀
    cvDilate( img_erode,img_dilate, 0,2); //膨胀
    
    cvNamedWindow("img_erode");
    cvNamedWindow("img_dilate");
    
    //cvShowImage("img_erode", img_erode);
    cvShowImage("img_dilate",img_dilate);
    
    //cvWaitKey(-1);
    
    
    cvReleaseImage(&img_dilate);
    cvReleaseImage(&img_erode);
    
    cvDestroyAllWindows();

    imshow("hello", imgResize(g_pGrayImage));
     //String savePath = "/Users/XiaoJiaKai/Desktop/11.png";
    //imwrite(savePath, imgResize(imgResize(g_pGrayImage)));
    cvWaitKey();
    cvReleaseImage(&img);
    cvReleaseImage(&g_pBinaryImage);
    cvReleaseImage(&g_pGrayImage);
}


Mat imgResize(Mat img)
{
    Mat resizedImg;
    resize(img,resizedImg,Size(img.cols*0.4, img.rows*0.4),0,0,CV_INTER_LINEAR);
    return resizedImg;
}
IplImage* cvimgResize(IplImage* img)
{
    IplImage* imageresize =0;
    imageresize=cvCreateImage(cvSize(img->width*0.4,img->height*0.4),IPL_DEPTH_8U,1);
    cvResize(img,imageresize,CV_INTER_LINEAR);
    return imageresize;
}
