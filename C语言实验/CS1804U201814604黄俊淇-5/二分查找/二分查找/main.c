//
//  main.c
//  二分查找
//
//  Created by 黄俊淇 on 2018/11/27.
//  Copyright © 2018 黄俊淇. All rights reserved.
//

#include <stdio.h>
#include <string.h>
int search(int a[],int together[], int x, int );
void bubble_sort(int score[], int index[], int m);
int main()
{
    int n,x,s;
   
    scanf("%d",&n);
    int score[n];
    char name[n][40];
    int i;
    int together[n];
   
    for (i=0; i<n; i++)
    {
        scanf("%s %d", name[i], &score[i]);
    }
    for (i=0; i<n; i++)
    {
        together[i] = i;
    }
    bubble_sort(score, together, n);
    
    
    for (i=0; i<n; i++)
    {
        printf("%-20s %d\n", name[together[i]], score[together[i]]);
    }
    printf("\n");
    int N;
    scanf("%d",&N);
    for(i=1;i<=N;i++)
    { scanf("%d", &x);
    s = search(score,together,x, n);
    if(s != EOF)
    {      printf("%-20s %d\n", name[together[s]], score[together[s]]);
        }
    else
        printf("Not found!\n");}
    
    return 0;
}

void bubble_sort(int score[], int together[], int m)
{
    int i, j, t;
    for (i=0; i<m-1; i++)
        for (j=0; j<m-1-i; j++)
        {
            if (score[together[j]] < score[together[j+1]])
            {
                t = together[j];
                together[j] = together[j+1];
                together[j+1] = t;
            }
        }
}

int search(int a[],int together[], int x, int p)
{
    int head= 0, back = p -1, mid;
    while (head<= back)
    {
        mid=(head+ back) / 2;
     
        if(x < a[together[mid]])
            head= mid+1;
        else if(x > a[together[mid]])
            back=mid-1;
        else
            return mid;
    }
    return -1;
}
