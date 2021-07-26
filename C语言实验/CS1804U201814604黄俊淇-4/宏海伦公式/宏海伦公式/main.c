//
//  main.c
//  宏海伦公式
//
//  Created by 黄俊淇 on 2018/11/20.
//  Copyright © 2018年 黄俊淇. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#define S(a,b,c) (a+b+c)/2
#define AREA(a,b,c,s) sqrt(s*(s-a)*(s-b)*(s-c))
int main( )
{
    int a,b,c;
    double s,area;
    ;
    while((scanf("%d%d%d",&a,&b,&c)!=EOF))
    {
    s=S(a,b,c);
        printf("%.0lf ",s);
    area=AREA(a,b,c,s);
        printf("%.6lf\n",area);
        
    }
    return 0;
    
}
