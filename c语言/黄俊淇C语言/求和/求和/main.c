//
//  main.c
//  求和
//
//  Created by 黄俊淇 on 2018/10/16.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//

#include<stdio.h>
int main()
{
    int i,sum=0;
    i=1;
    while(i<=100)
    {
        sum+=i;
        i++;
    }
    
    printf("%d",sum);
    return 0;
}
