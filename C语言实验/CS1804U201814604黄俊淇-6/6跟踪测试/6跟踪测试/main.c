//
//  main.c
//  6跟踪测试
//
//  Created by 黄俊淇 on 2018/12/9.
//  Copyright © 2018 黄俊淇. All rights reserved.
//
#include<stdio.h>
char *mystrcpy(char *,char *);
int main(void)
{
    char a[20],b[60]="there is a boat on the lake.";
    printf("%s\n",mystrcpy(a,b));
    return 0;
    
}
char *mystrcpy(char *s,char *t)/*返回指针*/
{
    char*p;
    p=s;
    while(*s++=*t++)
        ;
    return p;
}
