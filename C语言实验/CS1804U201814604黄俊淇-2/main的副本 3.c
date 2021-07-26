//
//  main.c
//  if收税
//
//  Created by 黄俊淇 on 2018/11/3.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//

#include <stdio.h>
int main()
{
    double x;
    scanf("%lf",&x);
    if(x<1000)
        printf("0");
    else if(x>=1000&&x<2000)
        printf("%lf",x*0.05);
    else if(x>=2000&&x<3000)
        printf("%lf",0.1*x);
    else if(x>=3000&&x<4000)
        printf("%lf",0.15*x);
    else if(x>=4000&&x<5000)
        printf("%lf",0.2*x);
    else 
        printf("%lf",0.25*x);
    return 0;
}
