//
//  main.c
//  4宏max
//
//  Created by 黄俊淇 on 2018/11/20.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//

#include<stdio.h>
#define max(a,b,c) (a>b?a:b)>(b>c?b:c)?(a>b?a:b):(b>c?b:c)
float sum(float x,float y);/*声明函数*/
int main(void)
{
    int a, b, c;
    float d,e;
    printf("Enter three integers:");
    scanf("%d,%d,%d",&a,&b,&c);
    printf("\nthe maximum of them is %d\n",max(a,b,c));
    
    printf("Enter two floating point numbers:");
    scanf("%f,%f",&d,&e);
    printf("\nthe sum of them is  %f\n",sum(d,e));
    return 0;
}
float sum(float x, float y)
{
    return x+y;
}
