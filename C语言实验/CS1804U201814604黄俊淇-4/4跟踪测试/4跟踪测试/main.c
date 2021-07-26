//
//  main.c
//  4跟踪测试
//
//  Created by 黄俊淇 on 2018/11/20.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//

#include<stdio.h>
#include <assert.h>/*头文件*/
#define  R
int integer_fraction(float x);
int main(void)
{
    float  r, s;
    int s_integer=0;
    printf ("input a number: ");
    scanf("%f",&r);
#ifdef  R
    s=3.14159*r*r;
    printf("area of round is: %f\n",s);
    s_integer= integer_fraction(s);
   assert((s-s_integer)<=1.0);/*大于号改小于号*/
    printf("the integer fraction of area is %d\n", s_integer);
#endif
    return 0;
}

int integer_fraction(float x)
{
    int i=x;
    return i;
}
