//
//  main.c
//  杨辉三角
//
//  Created by 黄俊淇 on 2018/11/4.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//

#include<stdio.h>
int main()
{
    int i,j,a[13][13];/*i是行，j是列*/
    int n,space;
    scanf("%d",&n);
    while(n!=0)
    { for(i=0;i<=n;i++)
        for(j=0;j<=n;j++)
        {
            a[i][0]=1;
            a[i][i]=1;
        }
    
    for(i=2;i<=n;i++)
        for(j=1;j<=i-1;j++)
            a[i][j]=a[i-1][j-1]+a[i-1][j];
    
    for(i=0;i<=(n-1);i++)
    {
        for(space=1;space<=(n-i-1);space++)
        {putchar(' ');putchar(' ');}
        for(j=0;j<=i;j++)
            printf("%4d",a[i][j]);
        printf("\n");
    }
        printf("\n");
        scanf("%d",&n);
    }
    return 0;
}
