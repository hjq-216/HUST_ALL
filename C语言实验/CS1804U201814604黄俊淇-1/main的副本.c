//
//  main.c
//  1程序设计1
//
//  Created by 黄俊淇 on 2019/1/10.
//  Copyright © 2019 黄俊淇. All rights reserved.
//

#include<stdio.h>
int main()
{
    char c;
    scanf("%c",&c);
    if(c<='Z'&&c>='A')
        printf("%c",c+32);
    else
        printf("%c\n\n",c);
    return 0;getchar();getchar();
}
