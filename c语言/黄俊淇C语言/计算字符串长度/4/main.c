//
//  main.c
//  4
//
//  Created by 黄俊淇 on 2018/10/14.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//


#include<stdio.h>
int mystrlen(char s[])
{int i;
    for(i=0;s[i]!=0;i++);
      
    return i;
}

int main()
{
    
    printf("%d\n",mystrlen("world"));
    return 0;
}

