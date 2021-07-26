//
//  file1.c
//  prj5
//
//  Created by 黄俊淇 on 2018/11/13.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//


#include "file.h"
int x,y;
char ch;
int main(void)
{
    x=10;
    y=20;
    ch=getchar( );
    printf("in file1 x=%d,y=%d,ch is %c\n",x,y,ch);
    func1( );
    return 0;
}
