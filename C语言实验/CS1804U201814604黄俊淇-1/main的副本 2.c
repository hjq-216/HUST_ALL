//
//  main.c
//  1程序设计2
//
//  Created by 黄俊淇 on 2019/1/10.
//  Copyright © 2019 黄俊淇. All rights reserved.
//

#include<stdio.h>
int main()
{
    unsigned short x,m,n,mask;
    scanf("%hd %hd %hd",&x,&m,&n);
    mask=(~((~0)<<n))<<m;
    printf("\n");
    x=(x&mask)<<(16-m-n);
    printf("%d",x);
    return 0;getchar();getchar();
}
