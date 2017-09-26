//
//  CaptchaFloodFillTest.cpp
//  OpenCvTest
//
//  Created by 肖家凯 on 05/05/2017.
//  Copyright © 2017 肖家凯. All rights reserved.
//

#include "CaptchaFloodFillTest.hpp"
for (i = 0; i < nWidth; ++i)
for (j = 0; j < nHeight; ++j)
{
    if ( !getPixel(i,j) )
    {
        //FloodFill each point in connect area using different color
        floodFill(m_Mat,cvPoint(i,j),cvScalar(color));
        color++;
    }
}

int ColorCount[256] = { 0 };
for (i = 0; i < nWidth; ++i)
{
    for (j = 0; j < nHeight; ++j)
    {
        //caculate the area of each area
        if (getPixel(i,j) != 255)
        {
            ColorCount[getPixel(i,j)]++;
        }
    }
}
//get rid of noise point
for (i = 0; i < nWidth; ++i)
{
    for (j = 0; j < nHeight; ++j)
    {
        if (ColorCount[getPixel(i,j)] <= nMin_area)
        {
            setPixel(i,j,WHITE);
        }
    }
}

int k = 1;
int minX,minY,maxX,maxY;
vector<Image> vImage;
while( ColorCount[k] )
{
    if (ColorCount[k] > nMin_area)
    {
        minX = minY = 100;
        maxX = maxY = -1;
        //get the rect of each charactor
        for (i = 0; i < nWidth; ++i)
        {
            for (j = 0; j < nHeight; ++j)
            {
                if(getPixel(i,j) == k)
                {
                    if(i < minX)
                        minX = i;
                        else if(i > maxX)
                            maxX = i;
                            if(j < minY)
                                minY = j;
                                else if(j > maxY)
                                    maxY = j;
                                    }
            }
        }
        //copy to each standard mat
        Mat *ch = new Mat(HEIGHT,WIDTH,CV_8U,WHITE);
        int m,n;
        m = (WIDTH - (maxX-minX))/2;
        n = (HEIGHT - (maxY-minY))/2;
        for (i = minX; i <= maxX; ++i)
        {
            for (j = minY; j <= maxY; ++j)
            {
                if(getPixel(i,j) == k)
                {
                    *(ch->data+ch->step[0]*(n+j-minY)+m+(i-minX)) = BLACK;
                }
            }
