//
//  main.c
//  6复杂声明
//
//  Created by 黄俊淇 on 2018/12/9.
//  Copyright © 2018 黄俊淇. All rights reserved.
//

#include <stdio.h>
#include <string.h>
char *fun1(const char*,const char*);
char *fun2(const char*,const char*);
int main()
{
    char *(*p[2])(const char *,const char *);
    char a[2],b[2];
    int i;
    for(i=0;i<2;i++)
    {
        a[i]=getchar();
    }
    getchar();
    for(i=0;i<2;i++)
    {
        b[i]=getchar();
    }
    p[0]=fun1;
    p[1]=fun2;
    int n;
    printf("input 0 or 1\n");
    scanf("%d",&n);
    printf("%c",*p[n](a,b));
    return 0;
}
char *fun1(const char*a,const char*b)
{
     const char*k;
    k=a;
    return k;
}
char *fun2(const char*a,const char*b)
{
    const char*k;
    k=b;
    return k;
}
