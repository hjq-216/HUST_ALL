//
//  main.c
//  6命令行排序
//
//  Created by 黄俊淇 on 2018/12/8.
//  Copyright © 2018 黄俊淇. All rights reserved.
//

#include <stdio.h>
#include<string.h>
void up_bubble_sort(int a[],int n);
void down_bubble_sort(int a[],int n);
int main(int argc,char *argv[])
{
   void (*p)(int a[],int n);
    int a[100];
    int n,i;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    if(argc>1&&(strcmp(argv[1],"-d")==0))
            p=down_bubble_sort;
    else
                p=up_bubble_sort;
    p(a,n);
    for(i=0;i<n;i++)
        printf("%d ",a[i]);
    return 0;
}
    
void up_bubble_sort(int a[],int n)
{
    int i,j,t;
    for(i=0;i<n-1;i++)
        for(j=0;j<n-i-1;j++)
            if(a[j]>a[j+1])
            {t=a[j];a[j]=a[j+1];a[j+1]=t;}
}

void down_bubble_sort(int a[],int n)
{
    int i,j,t;
    for(i=0;i<n-1;i++)
        for(j=0;j<n-i-1;j++)
            if(a[j]<a[j+1])
            {t=a[j];a[j]=a[j+1];a[j+1]=t;}
}
