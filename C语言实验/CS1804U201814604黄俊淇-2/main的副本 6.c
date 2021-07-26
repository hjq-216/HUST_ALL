//
//  main.c
//  正整数逆转
//
//  Created by 黄俊淇 on 2018/11/3.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//

#include <stdio.h>
int main(void)
{
    int x;
    scanf("%d", &x);
    do
       printf("%d",x%10);
    while((x/=10)!=0);
    printf("\n");
    return 0;
}
