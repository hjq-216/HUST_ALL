//
//  main.c
//  n!改错
//
//  Created by 黄俊淇 on 2018/11/13.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//

#include <stdio.h>
long sum_fac(int n);/*声明函数*/
int main(void)
{
    int k;
    for(k=1;k<6;k++)
        printf("k=%d\tthe sum is %ld\n",k,sum_fac(k));
    return 0;
}/*花括号*/
long sum_fac(int n)
{
    long s=0;
    int i;
    long fac=1;/*赋值*/
    for(i=1;i<=n;i++)
    {            /*花括号*/
        fac*=i;
        s+=fac;
    }
    return s;
}
