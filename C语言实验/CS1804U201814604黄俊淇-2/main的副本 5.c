//
//  main.c
//  n!求和计算量最小
//
//  Created by 黄俊淇 on 2018/11/13.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//

#include <stdio.h>
long sum_fac(int n);
static long fac=1;
int main(void)
{
    int k;
    for(k=1;k<6;k++)
        printf("k=%d\tthe sum is %ld\n",k,sum_fac(k));
    return 0;
}

long sum_fac(int n)
{
    static long s=0;
    
    fac*=n;
    
        
    s+=fac;
    
    return s;
}
