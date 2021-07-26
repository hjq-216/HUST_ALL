//
//  main.c
//  switch收税
//
//  Created by 黄俊淇 on 2018/11/3.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//

#include <stdio.h>
int main()
{
    int y;
    double x;
    scanf("%lf",&x);
    y=(int)(x/1000);
    switch(y)
    {
        case 0:
            printf("0");
            break;
        case 1:
            printf("%lf",0.05*x);
            break;
        case 2:
            printf("%lf",0.1*x);
            break;
        case 3:
            printf("%lf",0.15*x);
            break;
        case 4:
            printf("%lf",0.2*x);
            break;
        default:
            printf("%lf",0.25*x);
    }
    return 0;
}
