//
//  main.c
//  矩阵
//
//  Created by 黄俊淇 on 2018/11/27.
//  Copyright © 2018 黄俊淇. All rights reserved.
//

#include <stdio.h>
int main()
{
    int a[4][4],b[4][4];
    int i,j;
    for(i=0;i<3;i++)
        for(j=0;j<4;j++)
            scanf("%d",&a[i][j]);
    for(i=0;i<3;i++)
        for(j=0;j<4;j++)
            b[j][i]=a[i][j];
    
    for(i=0;i<3;i++)
    {  for(j=0;j<4;j++)
        
            printf("%5d",a[i][j]);
            printf("\n");
    }
    printf("\n");
        for(j=0;j<4;j++)
        {
            for(i=0;i<3;i++)
                printf("%4d",b[j][i]);
            printf("\n");
        }
}
