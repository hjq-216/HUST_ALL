//
//  main.c
//  5选做题strnins
//
//  Created by 黄俊淇 on 2018/11/27.
//  Copyright © 2018 黄俊淇. All rights reserved.
//

#include <stdio.h>
void mystrnins(char [],char[],int);
int main()
{
    char s[100],t[100];
    int n;
    scanf("%s",s);
    scanf("%s",t);
    scanf("%d",&n);
    mystrnins(s,t,n);
    printf("%s",s);
}
void mystrnins(char s[],char t[],int n)
{
    int i=0,j=0,a;
    while(s[i++]);
    while(t[j++]);
    for(a=i;a>=n;a--)/*从最后一位开始移安全，从第一位开始移有可能覆盖*/
        s[a+j-1]=s[a];
    i=0;
    while(i<j-1)
    {
        s[i+n]=t[i];
        i++;
    }
}
