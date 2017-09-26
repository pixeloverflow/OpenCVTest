//
//  findContoursTest.cpp
//  OpenCvTest
//
//  Created by 肖家凯 on 22/03/2017.
//  Copyright © 2017 肖家凯. All rights reserved.
//

#include <time.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>//OpenCV包含头文件
#include <opencv2/highgui/highgui.hpp>
#include <vector>//容器头文件
using namespace std;
using namespace cv;

static int getContoursByCplus(char* Imgname, double minarea, double whRatio)
{
    cv::Mat src, dst, canny_output;
    /// Load source image and convert it to gray
    src = imread(Imgname, 0);
    
    if (!src.data)
    {
        std::cout << "read data error!" << std::endl;
        return -1;
    }
    blur(src, src, Size(3, 3));
    
    
    //the pram. for findContours,
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    
    /// Detect edges using canny
    Canny(src, canny_output, 80, 255, 3);
    /// Find contours
    findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    //CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE
    
    double maxarea = 0;
    int maxAreaIdx = 0;
    
    for (int i = 0; i<contours.size(); i++)
    {
        
        double tmparea = fabs(contourArea(contours[i]));
        if (tmparea>maxarea)
        {
            maxarea = tmparea;
            maxAreaIdx = i;
            continue;
        }
        
//        if (tmparea < minarea)
//        {
//            //删除面积小于设定值的轮廓
//            contours.erase(contours.begin() + i);
//            std::wcout << "delete a small area" << std::endl;
//            continue;
//        }
        //计算轮廓的直径宽高
//        Rect aRect =boundingRect(contours[i]);
//        if ((aRect.width / aRect.height)<whRatio)
//        {
//            //删除宽高比例小于设定值的轮廓
//            contours.erase(contours.begin() + i);
//            std::wcout << "delete a unnomalRatio area" << std::endl;
//            continue;
//        }
    }
    /// Draw contours,彩色轮廓
    dst= Mat::zeros(canny_output.size(), CV_8UC3);
    for (int i = 0; i< contours.size(); i++)
    {
        //随机颜色
        RNG rng;
        Scalar color = Scalar(255,255,255);
        drawContours(dst, contours, i, color, 0.5, 8, hierarchy, 0, Point());
    }
    // Create Window
    char* source_window = "countors";
    namedWindow(source_window, CV_WINDOW_NORMAL);
    imshow(source_window, dst);
    cv:: waitKey(0);
    
    return 0;
}
static int getContoursByCplus(char* Imgname, double minarea=0, double whRatio=1);
int main()
{
    char* filename = new char[50];
    strcpy(filename, "/Users/XiaoJiaKai/Desktop/11.png");
    getContoursByCplus(filename);
    delete[] filename;
    return 0;
}
