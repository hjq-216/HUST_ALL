//
//  main.c
//  n！计算
//
//  Created by 黄俊淇 on 2018/11/13.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//

#include <stdio.h>
float sum_fac(int n);
int main(void)
{
    int k;
    for(k=1;k<6;k++)
        printf("k=%d\tthe sum is %f\n",k,sum_fac(k));
    return 0;
}
float sum_fac(int n)
{
    float s=0;
    int i;
    float fac=1;
    for(i=1;i<=n;i++)
    {
        fac*=i;
        s+=(1/fac);
    }
    return s;
}
