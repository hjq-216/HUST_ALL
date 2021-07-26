//
//  main.c
//  5标记法
//
//  Created by 黄俊淇 on 2018/11/27.
//  Copyright © 2018 黄俊淇. All rights reserved.
//

#include<stdio.h>
#define M 10
#define N 3
int main(void)
{
     int a[M], b[M];    /* 数组a存放圈中人的编号，数组b存放出圈人的编号 */
    int i, j, k;
    for(i = 0; i < M-1; i++)    /* 对圈中人按顺序编号1—M */
        a[i] = i + 1;
    a[9]=10;
    for(i = M, j = 0; i > 0; i--)
    {
        /* i表示圈中人个数，初始为M个，剩1个人时结束循环；
         j表示当前报数人的位置    */
        for(k = 1; k <= N; k++)    /* 1至N报数 */
        {
            if(a[++j-1]==0) k--;
            if(j>M-1) j=0;
        }/* 最后一个人报数后第一个接着报，形成一个圈 */
       
        b[M-i] = j?a[j-1]:a[i-1];    /* 将报数为N的人的编号存入数组b */
        if(!j)
            a[i-1]=0;
        else
        a[j-1]=0;
    }
    for(i=0;i<M;i++)
    /* 按次序输出出圈人的编号 */
    {     printf("%3d", b[i]);
        
    }
    return 0;
}
