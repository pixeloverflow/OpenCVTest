//
//  captchaTest.cpp
//  OpenCvTest
//
//  Created by 肖家凯 on 22/04/2017.
//  Copyright © 2017 肖家凯. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
using namespace std;
using namespace cv;
#define M 5
#define N 4
int a[M][N] = {0,1,0,1,0,1,1,0,1,1,0,0,1,0,1,0,1,0,1,0};
int b[M] = {};
void genLine(int n)
{
    if (n == M)
    {
        for (int i = 0; i < M; i++)
        {
            cout<<b[i]<<' ';
        }
        cout<<endl;
    }
    if (n==0)
    {
        for (int j = 0; j < N; j++)
        {
            if (a[0][j] == 1)
            {
                b[0] = j;
                genLine(n+1);
            }
        }
    }
    if (n > 0)
    {

        int p = b[n-1];
        if (b[n-1] > 0 && a[n][b[n-1]-1] == 1){
            b[n] = b[n-1]-1;
            genLine(n+1);
        }
        b[n-1] = p;
        if (a[n][b[n-1]] == 1){
            b[n] = b[n-1];
            genLine(n+1);
        }
        b[n-1] = p;
        if (b[n-1] < N && a[n][b[n-1]+1] == 1){
            b[n] = b[n-1]+1;
            genLine(n+1);
        }
    }
}

int main (int argc,char** args) 
{
    CvSeq* contour = NULL;
    double minarea = 100.0;
    double tmparea = 0.0;
        CvMemStorage* storage = cvCreateMemStorage(0);
    
    IplImage* img = cvLoadImage("/Users/XiaoJiaKai/Desktop/test123.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    IplImage* img_src = cvCreateImage(cvGetSize(img), 8, 1);
        IplImage* img_Clone=cvCloneImage(img_src);
        //访问二值图像每个点的值
        uchar *pp;
        //显示原始图像
        cvNamedWindow("img_src",CV_WINDOW_AUTOSIZE);
        cvShowImage("img_src", img_src);
        
        IplImage* img_dst = cvCreateImage(cvGetSize(img_src),IPL_DEPTH_8U,1);
        
        //------------搜索二值图中的轮廓，并从轮廓树中删除面积小于某个阈值minarea的轮廓-------------//
        CvScalar color = cvScalar(255,0,0);//CV_RGB(128,0,0);
        CvContourScanner scanner = NULL;
        scanner = cvStartFindContours(img_src,storage,sizeof(CvContour),CV_RETR_CCOMP,CV_CHAIN_APPROX_NONE,cvPoint(20,30));
        //开始遍历轮廓树
        CvRect rect;
        while (contour==cvFindNextContour(scanner))
        {
            tmparea = fabs(cvContourArea(contour));
            rect = cvBoundingRect(contour,0);
            if (tmparea < minarea/*||tmparea>4900*/)
            {
                
                //当连通域的中心点为黑色时，而且面积较小则用白色进行填充
                pp=(uchar*)(img_Clone->imageData + img_Clone->widthStep*(rect.y+rect.height/2)+rect.x+rect.width/2);
                if (pp[0]==255)
                {
                    for(int y = rect.y;y<rect.y+rect.height;y++)
                    {
                        for(int x =rect.x;x<rect.x+rect.width;x++)
                        {
                            pp=(uchar*)(img_Clone->imageData + img_Clone->widthStep*y+x);
                            
                            if (pp[0]==255)
                            {
                                pp[0]=0;
                            }
                        }   
                    }   
                }   
                
            }   
        }   
        cvSaveImage("/Users/XiaoJiaKai/Desktop/test124.jpg",img_Clone);
    return 0;
}
