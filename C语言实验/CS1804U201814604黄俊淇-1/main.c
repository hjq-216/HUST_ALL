//
//  main.c
//  1修改替换
//
//  Created by 黄俊淇 on 2019/1/10.
//  Copyright © 2019 黄俊淇. All rights reserved.
//

#include<stdio.h>
int main( )
{
    int a, b;
    printf("Input two integers:");
    scanf("%d %d",&a,&b);
    a=a-b;
    b=a+b;
    a=b-a;
    printf("\na=%d,b=%d",a,b);
    return 0;getchar();getchar();
}
