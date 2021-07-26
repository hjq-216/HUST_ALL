//
//  main.c
//  7字段结构
//
//  Created by 黄俊淇 on 2018/12/23.
//  Copyright © 2018 黄俊淇. All rights reserved.
//

#include <stdio.h>
struct bits{
    unsigned char bit0:1,bit1:1,bit2:1,bit3:1,bit4:1,bit5:1,bit6:1,bit7:1,bit8:1;
}a;
void f0()
{
    printf("the function 0 is called!\n");
}
void f1()
{
    printf("the function 1 is called!\n");
}
void f2()
{
    printf("the function 2 is called!\n");
}
void f3()
{
    printf("the function 3 is called!\n");
}
void f4()
{
    printf("the function 4 is called!\n");
}
void f5()
{
    printf("the function 5 is called!\n");
}
void f6()
{
    printf("the function 6 is called!\n");
}
void f7()
{
    printf("the function 7 is called!\n");
}
union bit{
    unsigned char b;
    struct bits a;
}c;
int main()
{
    void (*p_fun[8])(void);
    scanf("%c",&c.b);
    p_fun[0]=f0;
    p_fun[1]=f1;p_fun[2]=f2;p_fun[3]=f3;p_fun[4]=f4;p_fun[5]=f5;p_fun[6]=f6;p_fun[7]=f7;
    if(c.a.bit0)
        p_fun[0]();
    if(c.a.bit1)
        p_fun[1]();
    if(c.a.bit2)
        p_fun[2]();
    if(c.a.bit3)
        p_fun[3]();
    if(c.a.bit4)
        p_fun[4]();
    if(c.a.bit5)
        p_fun[5]();
    if(c.a.bit6)
        p_fun[6]();
    if(c.a.bit7)
        p_fun[7]();
    return 0;
}
