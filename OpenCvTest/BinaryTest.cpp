//
//  BinaryTest.cpp
//  OpenCvTest
//
//  Created by 肖家凯 on 21/03/2017.
//  Copyright © 2017 肖家凯. All rights reserved.
//

#include <time.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>//OpenCV包含头文件
#include <opencv2/highgui/highgui.hpp>
#include <vector>//容器头文件
using namespace std;
using namespace cv;

int valuearray[200000000] = { 0 };//记录连通域数值对应关系

class colorobj
{
public:
    int value;
    Scalar mycolor;
};

vector<colorobj> setcolor;//收集需要上色的灰度对象

bool equal255or0(int &value)//判断元素是否等于255或者0
{
    if (value == 255 || value == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void setvalue(int &value, int &minimun)//设置配对值
{
    if (value != 0)
    {
        if (valuearray[value] > minimun && valuearray[value]!=255)
        {
            int savemidvalue = valuearray[value];
            while (true)//将映射表调整
            {
                if (valuearray[savemidvalue] > minimun)
                {
                    int mid = valuearray[savemidvalue];
                    valuearray[savemidvalue] = minimun;
                    savemidvalue = mid;
                }
                else
                {
                    break;
                }

            }
            valuearray[value] = minimun;
        }
        value = minimun;
    }
}

void compare(int &value, int &minimun)//比较大小
{
    if (value != 0 && value!=255)
    {
        if (minimun >= value)
        {
            minimun = value;
        }
    }
}

Scalar GetRandomColor()//彩色显示
{
    uchar r = 255 * (rand() / (1.0 + RAND_MAX));
    uchar g = 255 * (rand() / (1.0 + RAND_MAX));
    uchar b = 255 * (rand() / (1.0 + RAND_MAX));
    return cv::Scalar(b, g, r);
}

int main()
{
    long time = clock();//记录计算时间
    Mat Image = cv::imread("/Users/XiaoJiaKai/Desktop/test.jpg", 0);//读入图像，并将图像灰度化
    threshold(Image, Image, 50, 255, CV_THRESH_BINARY_INV);//二值化图像
    imshow("a", Image);
    
    int contourmark = 1; //连通域标志
    
    Mat IntImage;//图片对象，用以将图像的像素变量从uchar转为int，以防止后面标志位大于255程序无法工作的情况
    Image.convertTo(IntImage, CV_32SC1);//将图像像素变量转为int
    
    //遍历图像，搜索连通域
    for (int Y = 1; Y < IntImage.rows - 1; Y++)//遍历图像,Y为行，X为列
        for (int X = 1; X < IntImage.cols - 1; X++)
        {
            if (IntImage.at<int>(Y, X) != 0)//记住这里是先行后列
            {
                //如果不属于任何一个连通域
                if (IntImage.at<int>(Y, X) == 255 && //本元素
                    equal255or0(IntImage.at<int>(Y - 1, X)) && //上方元素
                    equal255or0(IntImage.at<int>(Y + 1, X)) && //下方元素
                    equal255or0(IntImage.at<int>(Y, X - 1)) && //左方元素
                    equal255or0(IntImage.at<int>(Y, X + 1)))//右方元素
                {
                    valuearray[contourmark] = contourmark;
                    IntImage.at<int>(Y, X) = contourmark;
                    if (IntImage.at<int>(Y - 1, X) == 255)
                    {
                        IntImage.at<int>(Y - 1, X) = contourmark;
                    }
                    if (IntImage.at<int>(Y + 1, X) == 255)
                    {
                        IntImage.at<int>(Y + 1, X) = contourmark;
                    }
                    if (IntImage.at<int>(Y, X - 1) == 25
                    {
                        IntImage.at<int>(Y, X - 1) = contourmark;
                    }
                    if (IntImage.at<int>(Y, X + 1) == 255)
                    {
                        IntImage.at<int>(Y, X + 1) = contourmark;
                    }
                    contourmark++;
                    if (contourmark==255)//防止冲突
                    {
                        valuearray[contourmark] = 255;
                        contourmark = 256;
                    }
                }
                //已经属于某一个连通域
                else
                {
                    int getminimum = 200000000;
                    //取得上下左右最小的标志位
                    compare(IntImage.at<int>(Y, X), getminimum);
                    compare(IntImage.at<int>(Y - 1, X), getminimum);
                    compare(IntImage.at<int>(Y + 1, X), getminimum);
                    compare(IntImage.at<int>(Y, X - 1), getminimum);
                    compare(IntImage.at<int>(Y, X + 1), getminimum);
                    //将最小的标志位赋值给目标
                    setvalue(IntImage.at<int>(Y, X), getminimum);
                    setvalue(IntImage.at<int>(Y - 1, X), getminimum);
                    setvalue(IntImage.at<int>(Y + 1, X), getminimum);
                    setvalue(IntImage.at<int>(Y, X - 1), getminimum);
                    setvalue(IntImage.at<int>(Y, X + 1), getminimum);
                }
            }
        }
    
    for (size_t i = 1; i <= contourmark; i++)//将同一个连通域的对象映射表调整好，做完这一步映射表制作完成
    {
        valuearray[i] = valuearray[valuearray[i]];
    }
    
    for (int Y = 1; Y < IntImage.rows; Y++)//根据映射表对图像像素进行重新赋值
        for (int X = 1; X < IntImage.cols; X++)
        {
            if (IntImage.at<int>(Y, X) != 0)
            {
                IntImage.at<int>(Y, X) = valuearray[IntImage.at<int>(Y, X)];
            }
        }
    for (int j = 1; j < contourmark; j++)//获得需要上色的对象值
    {
        if (j==255)//跳过无意义值
        {
            continue;
        }
        bool dopush = true;
        for (int i = 0; i < setcolor.size(); i++)
        {
            if (setcolor[i].value == valuearray[j])
            {
                dopush = false;
                break;
            }
        }
        if (dopush == true)
        {
            colorobj mycolorobj;
            mycolorobj.value = valuearray[j];
            mycolorobj.mycolor = GetRandomColor();
            setcolor.push_back(mycolorobj);
        }
    }
    
    //彩色显示
    Mat colorLabelImg;
    colorLabelImg.create(IntImage.rows, IntImage.cols, CV_8UC3);
    colorLabelImg = Scalar::all(255);//初始化，将待显示图片的背景设置为白色
    
    for (int Y = 0; Y < IntImage.rows; Y++)//颜色填充
        for (int X = 0; X < IntImage.cols; X++)
        {
            if (IntImage.at<int>(Y, X) != 0)
            {
                for (int i = 0; i < setcolor.size(); i++)
                {
                    if (IntImage.at<int>(Y, X) == setcolor[i].value)
                    {
                        colorLabelImg.at<Vec3b>(Y, X)[0] = setcolor[i].mycolor[0];
                        colorLabelImg.at<Vec3b>(Y, X)[1] = setcolor[i].mycolor[1];
                        colorLabelImg.at<Vec3b>(Y, X)[2] = setcolor[i].mycolor[2];
                        break;
                    }
                }
            }
        }
    printf("标志位值%d\n", contourmark);
    printf("花费时间%lums\n", clock() - time);
    imwrite("a.bmp", colorLabelImg);
    imshow("colorLabelImg", colorLabelImg);
    waitKey(0);
}
