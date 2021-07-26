//
//  main.c
//  1程序设计3
//
//  Created by 黄俊淇 on 2019/1/10.
//  Copyright © 2019 黄俊淇. All rights reserved.
//

#include<stdio.h>
int main()
{
    unsigned long x,a,b,c,d;
    scanf("%ld",&x);
    a=(x&0xff000000)>>24;
    b=(x&0x00ff0000)>>16;
    c=(x&0x0000ff00)>>8;
    d=(x&0x000000ff);
    printf("%d.%d.%d.%d",d,c,b,a);
    return 0;getchar();getchar();
}
