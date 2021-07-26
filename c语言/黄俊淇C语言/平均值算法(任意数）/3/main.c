//
//  main.c
//  3
//
//  Created by 黄俊淇 on 2018/10/12.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//

#include <stdio.h>

int main()
{
    int x,k,average,sum;
    k=0;
    average=sum=0;
    while(scanf("%d",&x)==1)
    {
       sum=sum+x;
        k++;
    
        average=sum/k;}
    printf("average=%d",average);
    return 0;
}
