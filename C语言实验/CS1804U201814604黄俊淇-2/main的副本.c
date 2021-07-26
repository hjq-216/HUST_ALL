//
//  main.c
//  for改成while
//
//  Created by 黄俊淇 on 2018/11/3.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//


#include <stdio.h>
int main()
{
    int i,n,s=1;
    i=1;
    printf("please enter n:\n");
    scanf("%d",&n);
    while(i<=n)
    {
        s=s*i;
        i++;
    }
    printf("%d!=%d",n,s);
    return 0;
}
