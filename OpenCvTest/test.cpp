//
//  test.cpp
//  OpenCvTest
//
//  Created by 肖家凯 on 20/02/2017.
//  Copyright © 2017 肖家凯. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;
int main()
{
    int a[4];
    int *ptr=a;
    cout <<"size of =" <<sizeof(ptr)<<endl;
    cout <<ptr<<"\n"<<endl;
    ptr++;
    cout <<ptr<<"\n"<<endl;
    ptr++;
    cout <<ptr<<"\n"<<endl;
    cout <<*ptr;
}
