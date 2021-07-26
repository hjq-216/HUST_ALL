//
//  main.c
//  5跟踪调试
//
//  Created by 黄俊淇 on 2018/11/27.
//  Copyright © 2018 黄俊淇. All rights reserved.
//

#include<stdio.h>
void mystrncat(char s[],char t[], int n);
int main(void)
{
    char a[50]="The adopted symbol is ",b[27]="abcdefghijklmnopqrstuvwxyz";
    mystrncat(a,b,4);
    printf("%s\n",a);
    return 0;
}
void mystrncat(char s[],char t[], int n)
{
    int i = 0, j;
    while(s[i]!='\0')
    {
        i++;
    }
    for(j = 0; j<n && t[j];)
        s[i++] = t[j++];
    s[i] = '\0';
}
