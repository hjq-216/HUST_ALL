//
//  main.c
//  6
//
//  Created by 黄俊淇 on 2018/10/16.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//

#include <stdio.h>

int main()
{
    int i,n,s=1;
    scanf("%d\n",&n);
    i=1;
    while(i<=n){
    s=s*i;
        i++;}
    printf("%d\n",s);
    return 0;
}

