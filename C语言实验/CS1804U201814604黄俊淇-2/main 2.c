//
//  main.c
//  合并空格
//
//  Created by 黄俊淇 on 2018/11/5.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//

#include <stdio.h>
int main( )
{
    int c;
    int N,i=1;
    scanf("%d",&N);
    getchar();
    while(((c=getchar())!=EOF)&&(i<=(N-1)))
          {
              if(c=='\n')
                  i++;
              if(c==' ')
              {
                  putchar(c);
                  while((c=getchar())==' ')
                  {
                      continue;
                  }
              }
              putchar(c);
          }
          return 0;
    }
