//
//  main.c
//  完数
//
//  Created by 黄俊淇 on 2018/10/19.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//

#include<stdio.h>
int IsPerfectNumber (int a)
{
    int i=1,s=0;
    while(i<a)
    {
        if(a%i==0)
            i++;
    }
    a==s? 1:0;
    return ;
}
int main(void)
{
    int k;
    for(k=1;k<=1000;k++)
    {
        if((IsPerfectNumber(k))==1)
            printf("%d\n",k);
    }
    return 0;
    }
