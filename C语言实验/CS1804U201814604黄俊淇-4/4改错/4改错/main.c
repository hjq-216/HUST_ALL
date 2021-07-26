//
//  main.c
//  4改错
//
//  Created by 黄俊淇 on 2018/11/20.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//

#include<stdio.h>
#define SUM  (a+b)/*加括号*/
#define DIF  (a-b)
#define SWAP(a,b)  t=a,a=b,b=t/*z缺少中间变量*/
int main(void)
{
    int a,b,t;/*变量a的声明*/
    printf("Input two integers a, b:");
    scanf("%d,%d", &a,&b);/*逗号*/
    printf("\nSUM=%d\n the difference between square of a and square of b is:%d", SUM, SUM*DIF);
    SWAP(a,b);
    printf("\nNow a=%d,b=%d\n",a,b);
    return 0;
}
