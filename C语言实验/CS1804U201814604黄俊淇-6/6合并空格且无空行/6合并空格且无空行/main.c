//
//  main.c
//  6合并空格且无空行
//
//  Created by 黄俊淇 on 2018/12/8.
//  Copyright © 2018 黄俊淇. All rights reserved.
//

#include <stdio.h>
void fun(char *p[],char a[][80],int n);
int main()
{
    int n;
    int i,j;
    scanf("%d",&n);
    while(n!=0)
    {
        char *p[n];
        char a[n][80];
        getchar();
    for(i=0;i<n;i++)
        p[i]=a[i];
    for(i=0;i<n;i++)
    {  fgets(a[i],80,stdin);
        for(j=0;a[i][j]!='\0';j++)
            if(a[i][j]=='\n')
                a[i][j]='\0';
    }
    fun(p,a,n);
        printf("\n");
        scanf("%d",&n);
    }
    return 0;
}

void fun(char *p[],char a[][80],int n)
{
    int i,j,k;
    for(i=0;i<n;i++)
    {
        for(j=0;a[i][j]!='\0';j++)
        {
            if(a[i][j]==' '||a[i][j]=='\t')
                while(a[i][j+1]==' '||a[i][j+1]=='\t')
                { for(k=j+1;a[i][k]!='\0';k++)
                    a[i][k]=a[i][k+1];}
        }
    }
   
    for(i=0;i<n;i++)
    {
        if(a[i][0]=='\0')
                continue;
        else
                printf("%s\n",p[i]);
    }
}
