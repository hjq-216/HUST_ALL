//
//  main.c
//  作业
//
//  Created by 黄俊淇 on 2018/10/18.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//

#include<stdio.h>
int main()
{
    int n,sum,i,N,s;
    s=1;
    i=1;
    sum=0;
    scanf("%d",&N);
    while(s<=N)
    {
        scanf("%d",&n);
        while(i<=n)
    {
        sum=sum+i;
        i++;
    }
        printf("%d\n",sum);
        s++;
    }
    return 0;
}
