//
//  main.c
//  6程序16进制
//
//  Created by 黄俊淇 on 2018/12/8.
//  Copyright © 2018 黄俊淇. All rights reserved.
//

#include <stdio.h>
int main()
{
    long n,N,k;
    k=1;
    scanf("%ld",&N);
    while(k<=N)
    {  scanf("%ld",&n);
    char *p=(char*)&n;
    char a[4][2];
    int i,j;
    for(i=0;i<4;i++)
    {
        a[i][1]=(*p>>4)&0x0f;
        a[i][0]=(*p)&0x0f;
        p++;
    }
    for(i=3;i>=0;i--)
    {
        for(j=1;j>=0;j--)
        {
            if((a[i][j]>=0)&&(a[i][j]<=9))
                a[i][j]+='0';
            if((a[i][j]>=10)&&(a[i][j]<=15))
                a[i][j]=a[i][j]-10+'a';
  
        }
       
    }
        for(i=3;i>=1;i--)
        {
            for(j=1;j>=0;j--)
            {
                printf("%c ",a[i][j]);
                
            }
            
        }
        printf("%c ",a[0][1]);
        printf("%c",a[0][0]);
        printf("\n");
        k++;
    }
    return 0;
}
