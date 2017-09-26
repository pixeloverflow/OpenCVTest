<<<<<<< HEAD
//
//  main.cpp
//  OpenCvTest
//
//  Created by 肖家凯 on 15/02/2017.
//  Copyright © 2017 肖家凯. All rights reserved.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
=======
#include "opencv2/core/core.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/legacy/legacy.hpp"
#include "opencv2/legacy/compat.hpp"
#include "opencv2/core/types_c.h"
#include <iostream>
#include <vector>
#include <stdio.h>


using namespace cv;
using namespace std;
static void flannFindPairs( const Mat& m_object,
               const Mat& m_image, vector<int>& ptpairs )
{
    
    
    // find nearest neighbors using FLANN
    cv::Mat m_indices(m_object.rows, 2, CV_32S);
    cv::Mat m_dists(m_object.rows, 2, CV_32F);
    cv::flann::Index flann_index(m_image, cv::flann::KDTreeIndexParams(4));  // using 4 randomized kdtrees
    flann_index.knnSearch(m_object, m_indices, m_dists, 2, cv::flann::SearchParams(64) ); // maximum number of leafs checked
    
    int* indices_ptr = m_indices.ptr<int>(0);
    float* dists_ptr = m_dists.ptr<float>(0);
    for (int i=0;i<m_indices.rows;++i) {
        if (dists_ptr[2*i]<0.6*dists_ptr[2*i+1]) {
            ptpairs.push_back(i);
            ptpairs.push_back(indices_ptr[2*i]);
        }
    }
    cout<<ptpairs.size()/2<<endl;
}

//基于Opencv的SIFT代码，使用FLANN匹配
int main(int argc, char* argv[])
{

    if (argc == NULL){
        printf("agrv[1]=%s\n", argv[1]);
        return 1;
    }
    //Load Image
    String imgUrl = "/Users/XiaoJiaKai/Downloads/testpics/1486969895394_9693c891_c96cee5b_opencv.jpg";
    //String imgUrl = argv[1];
    String baseimg = imgUrl;
    String baseimg_sub = baseimg.substr(0,baseimg.find("."));
    const char * baseimg_char = baseimg.c_str();
    String targetImg = baseimg_sub+"-target.jpg";
    const char * targetImg_char = targetImg.c_str();
    const char * targetImg_char = targetImg.c_str();
    Mat c_object =  imread(targetImg);
    Mat c_image = imread(baseimg);
    Mat object = imread(targetImg, CV_LOAD_IMAGE_GRAYSCALE);
    Mat image = imread(baseimg, CV_LOAD_IMAGE_GRAYSCALE);
    if( !object.data || !image.data )
    { std::cout<< " --(!) Error reading images " << std::endl; return -1; }
    
    
    //sift feature detect
    SiftFeatureDetector detector;
    std::vector<KeyPoint> kp1, kp2;
    
    detector.detect( object, kp1 );
    detector.detect( image, kp2 );
    SiftDescriptorExtractor extractor;
    Mat des1(kp1.size(),128,CV_32F);
    Mat des2(kp2.size(),128,CV_32F);//descriptor
    
    extractor.compute(object,kp1,des1);
    extractor.compute(image,kp2,des2);
    
    Mat res1,res2;
    int drawmode = DrawMatchesFlags::DRAW_RICH_KEYPOINTS;
    drawKeypoints(c_object,kp1,res1,Scalar::all(-1),drawmode);//在内存中画出特征点
    drawKeypoints(c_image,kp2,res2,Scalar::all(-1),drawmode);
    cout<<"size of description of Img1: "<<kp1.size()<<endl;
    cout<<"size of description of Img2: "<<kp2.size()<<endl;
    
    
    CvFont font;
    double hScale=1;
    double 3=1;
    int lineWidth=2;
    cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, hScale,vScale,0,lineWidth);
    IplImage ipl_img1(res1);
    IplImage ipl_img2(res2);
    IplImage* transimg1 = cvCloneImage(&ipl_img1);
    IplImage* transimg2 = cvCloneImage(&ipl_img2);
    
    
    
    
    char str1[20],str2[20];
    sprintf(str1,"%d",kp1.size());
    sprintf(str2,"%lu",kp2.size());
    
    
    const char* str = str1;
    cvPutText(transimg1,str1,cvPoint(280,230),&font,CV_RGB(255,0,0));//在图片中输出字符
    
    str = str2;
    cvPutText(transimg2,str2,cvPoint(280,230),&font,CV_RGB(255,0,0));//在图片中输出字符
    
    //imshow("Description 1",res1);
    cvShowImage("descriptor1",transimg1);
    cvShowImage("descriptor2",transimg2);
    
    /////////////////////////////////////////////////////////
    
    static CvScalar colors[] =
    {
        {{0,0,255}},
        {{0,128,255}},
        {{0,255,255}},
        {{0,255,0}},
        {{255,128,0}},
        {{255,255,0}},
        {{255,0,0}},
        {{255,0,255}},
        {{255,255,255}}
    };
    
    const char* object_filename = argc == 3 ? argv[1] : targetImg_char;
    const char* scene_filename = argc == 3 ? argv[2] : baseimg_char;
    
    
    
    IplImage* object_t = cvLoadImage( object_filename, CV_LOAD_IMAGE_GRAYSCALE );
    IplImage* image_t = cvLoadImage( scene_filename, CV_LOAD_IMAGE_GRAYSCALE );
    
    vector<int> ptpairs;
    flannFindPairs( des1, des2, ptpairs );
    
    cout<<ptpairs.size()/2<<endl;
    IplImage* correspond = cvCreateImage( cvSize(image_t->width, object_t->height+image_t->height), 8, 1 );
    cvSetImageROI( correspond, cvRect( 0, 0, object_t->width, object_t->height ) );
    cvCopy( object_t, correspond );
    cvSetImageROI( correspond, cvRect( 0, object_t->height, correspond->width, correspond->height ) );
    cvCopy( image_t, correspond );
    cvResetImageROI( correspond );
    
    
    
    
    
    cout<< (int)ptpairs.size()/2<< endl;
    for(int i = 0; i < (int)ptpairs.size(); i += 2 )
    {
        KeyPoint r1 = kp1.at(ptpairs[i]);
        KeyPoint r2 = kp2.at(ptpairs[i+1]);
        
        
        cvLine( correspond, cvPointFrom32f(r1.pt),
               cvPoint(cvRound(r2.pt.x), cvRound(r2.pt.y+object_t->height)), colors[8] );
        cout<< "GOOD MATCH ["<< i/2 << "] : object [" <<ptpairs[i] <<" ] ,image ["<<ptpairs[i+1]<<"] \n" ;
    }
    
    //cvShowImage( "Object Correspond", correspond );
    Mat show =correspond;
    Mat img2;
    resize(show,img2,Size(show.cols*0.7,show.rows*0.7),0,0,CV_INTER_LINEAR);
    imshow("test", img2);
    String FileName = imgUrl.substr(37,baseimg.find("."));
    cout << "saved name:"<<FileName;
    String SavePath = "/Users/XiaoJiaKai/Desktop/matched/"+FileName;
    cout << "saved path:"<<SavePath;
    //imwrite(SavePath, img2);
    cvWaitKey();
    return 0;
}

>>>>>>> 18d1119... Commit
