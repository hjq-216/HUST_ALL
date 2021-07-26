//
//  main.c
//  哥德巴赫猜想介于两符号常量
//
//  Created by 黄俊淇 on 2018/11/13.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//

#include <stdio.h>
void gotbaha(int BEGIN );
int isprime(int i)
{
    int a;
    if (i==2) return 1;
    for(a=2;a<=i;a++)
        if(i%a==0)
            break;
    if(a>=i)
        return 1;
    else
        return 0;
}

void gotbaha(int BEGIN)
{
    int y;
    for(y=2;y<=BEGIN/2;y++)
    {
        if((isprime(y)==1)&&(isprime(BEGIN-y)==1))
        {
            printf("%d=%d+%d\n",BEGIN,y,BEGIN-y);
            break;
        }
    }
}

int main()
{
    int END;
    int BEGIN;
   
    while((scanf("%d%d",&BEGIN,&END)!=EOF))
    {
        if((BEGIN%2)!=0)
            for(;BEGIN<=(END-1);BEGIN++,BEGIN++)
            gotbaha((BEGIN+1));
        else
            for(;BEGIN<=END;BEGIN++,BEGIN++)
                gotbaha(BEGIN);
         printf("\n");
       
    }
    return 0;
}
