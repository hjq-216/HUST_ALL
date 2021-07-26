//
//  main.c
//  6改错
//
//  Created by 黄俊淇 on 2018/12/8.
//  Copyright © 2018 黄俊淇. All rights reserved.
//

#include <stdio.h>
int main(void)
{
    float n,*p=&n;/*指针初始化*/
    scanf("%f",&n);
    printf("%f\n",*p);
    return 0;
}
