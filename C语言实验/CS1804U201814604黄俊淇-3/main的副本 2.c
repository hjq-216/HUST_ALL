//
//  main.c
//  最大公约数
//
//  Created by 黄俊淇 on 2018/11/13.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//
#include <stdio.h>
int maxgongyueshu(int a,int b)
{
    int r;
    r=a%b;
    if(r==0)
    return b;
    else
        printf("%d\n",r);
        return maxgongyueshu(b,r);
}
int main(void)
{
    int a,b;
    scanf("%d%d",&a,&b);
    
    printf("%d\n",maxgongyueshu(a,b));
    
}
