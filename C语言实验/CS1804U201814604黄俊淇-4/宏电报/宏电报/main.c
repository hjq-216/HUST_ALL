//
//  main.c
//  宏电报
//
//  Created by 黄俊淇 on 2018/11/20.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//

#include <stdio.h>
#define CHANGE (s%2)
int main()
{
    char s;
    int N,i=1;
    scanf("%d",&N);
    getchar();
  while(i<=N)
{
    s=getchar();
   if( CHANGE==1)
{
    while(s!=EOF)
    {
        if(s<='Z'&&s>='A')
        {  s+=32;
            putchar(s);}
        else if(s<='z'&&s>='a')
        {    s=s-32;
            putchar(s);}
        else
            putchar(s);
        s=getchar();
        if(s=='\n')
        { i++;break;}
    }
    putchar('\n');
}
    
else if( CHANGE==0)
{
    while(s!=EOF)
    {
        putchar(s);
        s=getchar();
        if(s=='\n')
        { i++;break;}
    }
    putchar('\n');
}
}
    return 0;
}
