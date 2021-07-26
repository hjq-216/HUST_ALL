//
//  main.c
//  等差数列
//
//  Created by 黄俊淇 on 2018/11/13.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//

#include <stdio.h>
#define max 2147483647
#include<math.h>
void canshu(int a,int d,int k);
int k=1;
int main()
{
     int a,d;
    printf("please input 2 numbers:\n");
    scanf("%d %d",&a,&d);
    canshu(a,d,k);
}
    
void canshu(int a,int d,int k)
{
         int t=0;
        for(;k<=100;k++)
    {
        if((a+(k-1)*d)>(a+k*d))/*整数上溢判断条件*/
            break;
        t=a+(k-1)*d;
        printf("%d\t",t);
        if(!(k%5))
            printf("\n");
    }
}

