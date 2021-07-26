//
//  main.c
//  5
//
//  Created by 黄俊淇 on 2018/10/15.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//

#include <stdio.h>
int main()
{
    int x,k,positive,negtive;
    k=1;
    positive=negtive=0;
    while(scanf("%d",&x)==1)
    {
        if(x>0)
        {
            positive++;
        }
        else
        {
            negtive++;
        }
        k++;
    }
    printf("positive=%d",positive);
    printf("negtive=%d",negtive);
    return 0;
}
