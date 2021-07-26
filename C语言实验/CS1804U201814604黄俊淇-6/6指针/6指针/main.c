//
//  main.c
//  6指针
//
//  Created by 黄俊淇 on 2018/12/8.
//  Copyright © 2018 黄俊淇. All rights reserved.
//

#include <stdio.h>
#define N 5
#define M 5
int average1(char name2[][20],float (*a)[M]);
void average2(char name1[][20],float (*a)[M]);
void low1(char name1[][20],float (*a)[M]);
void low2(char name1[][20],float (*a)[M]);
int main()
{
    float a[N][M];
    char name1[M][20];
    char name2[M][20];
    int i,j;
    for(i=0;i<N;i++)
        scanf("%s",name1[i]);
    for(i=0;i<N;i++)
    {
        scanf("%s",name2[i]);
        for(j=0;j<M;j++)
        {
            
            scanf("%f",&*(*(a+i)+j));
        }
    }
    average1(name2,a);
    average2(name1,a);
    low1(name1,a);
    low2(name1,a);
}

int average1(char name2[][20],float (*a)[M])
{
    int i,j;
    float average=0,sum=0;
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            sum+=*(*(a+i)+j);
        }
        average=sum/M;
        sum=0;
        printf("Average score of %s is %.2f\n",name2[i],average);
    }
    
    return average;
}
int sum1[M];
void average2(char name1[][20],float (*a)[M])
{
    int i,j,k;
    float average=0,sum=0;
    for(k=0;k<N;k++)
    {
        sum1[k]=0;
    }
    for(j=0;j<M;j++)
    {
        for(i=0;i<N;i++)
        {
            sum+=*(*(a+i)+j);
        }
        average=sum/N;
        sum=0;
        printf("Average score of %s is %.2f\n",name1[j],average);
     
        for(i=0;i<N;i++)
        {
            if(*(*(a+i)+j)<average)
            sum1[j]++;
        }
        
    }
}
void low1(char name1[][20],float (*a)[M])
{
    int j;
    for(j=0;j<M;j++)
    {
        printf("Number of students lower than avg of %s is %d\n",name1[j],sum1[j]);
    }
}
void low2(char name1[][20],float (*a)[M])
{
    int i,j,low[5],high[5],k;
    for(k=0;k<5;k++)
    {
        low[k]=0;
        high[k]=0;
    }
    for(j=0;j<M;j++)
    {
        for(i=0;i<N;i++)
        {
            if(*(*(a+i)+j)<60)
               low[j]++;
            if(*(*(a+i)+j)>90)
                high[j]++;
            
        }
     
        
    }
    for(k=0;k<N;k++)
    {
        printf("Number of students %s fail is %d\n",name1[k],low[k]);}
    for(k=0;k<N;k++)
    {        printf("Number of students %s perfect is %d\n",name1[k],high[k]);}
    
}
