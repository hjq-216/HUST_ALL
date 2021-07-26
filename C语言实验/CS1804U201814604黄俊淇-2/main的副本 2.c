//
//  main.c
//  for改为do while
//
//  Created by 黄俊淇 on 2018/11/3.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//

#include <stdio.h>
int main()
{
    int i,n,s=1;
    
    printf("please enter n:\n");
    scanf("%d",&n);
    i=1;
    do
    {
        s=s*i;
        i++;
    }
    while(i<=n);
    printf("%d!=%d",n,s);
    return 0;
}
