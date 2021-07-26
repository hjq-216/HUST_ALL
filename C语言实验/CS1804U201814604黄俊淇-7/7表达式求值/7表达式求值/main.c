//
//  main.c
//  7表达式求值
//
//  Created by 黄俊淇 on 2018/12/23.
//  Copyright © 2018 黄俊淇. All rights reserved.
//

#include <stdio.h>
int main()
{
    char u[]="UVWXYZ";
    char v[]="xyz";
    struct T{
        int x;
        char c;
        char *t;
    }a[]={{11,'A',u},{100, 'B',v}},*p=a;
    
    printf("(++p)->x=%d\n",(++p)->x);
    
    p=a;
    p++;
    printf("p->c=%c\n",p->c);
    
    p=a;
    printf("*p++->t=%c ",*p++->t);
    printf("*p->t=%c\n",*p->t);
    
    p=a;
    printf("*(++p)->t=%c\n",*(++p)->t);
    
    p=a;
    printf("*++p->t=%c\n",*++p->t);
    p->t=u;
    
    p=a;
    printf("++*p->t=%c\n",++*p->t);
    
    return 0;
}
