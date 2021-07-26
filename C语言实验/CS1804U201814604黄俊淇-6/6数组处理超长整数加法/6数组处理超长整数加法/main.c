//
//  main.c
//  6数组处理超长整数加法
//
//  Created by 黄俊淇 on 2018/12/9.
//  Copyright © 2018 黄俊淇. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>
#define N 20
#define M 10
int main()
{
    int x[M+N+1],y[M+N+1],z[M+N+2];
    int i,carry=0,flag=0;
  
    for(i=0;i<=19;i++)
    {
        x[i]=getchar();
        x[i]-='0';
    }
   
    x[20]=getchar();
    for(i=21;i<=30;i++)
    {
        x[i]=getchar();
        x[i]-='0';
    }
    
    getchar();
    for(i=0;i<=19;i++)
    {
        y[i]=getchar();
        y[i]-='0';
    }
    y[20]=getchar();
    for(i=21;i<=30;i++)
    {
        y[i]=getchar();
        y[i]-='0';
    }
 
    for(i=31;i>=22;i--)
    {
        z[i]=x[i-1]+y[i-1]+carry;
        if(z[i]>=10)
            carry=1;
        else
            carry=0;
        z[i]%=10;
        z[i]+='0';
    }
    for(i=20;i>=1;i--)
    {
        z[i]=x[i-1]+y[i-1]+carry;
        if(z[i]>=10)
            carry=1;
        else
            carry=0;
        z[i]%=10;
        z[i]+='0';
    }
    z[0]=carry+'0';
    z[21]='.';
    for(i=0;i<=31;i++)
    {
        if(flag==0&&z[i]!='0') flag=1;
        if(flag==1) putchar(z[i]);
    }
    putchar('\n');
    return 0;
}
