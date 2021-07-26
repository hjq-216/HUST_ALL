//
//  main.c
//  8实验替换
//
//  Created by 黄俊淇 on 2018/12/25.
//  Copyright © 2018 黄俊淇. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>
int main(int argc, char* argv[])
{
    char ch;
    FILE *fp;
    if(argc!=2){
        printf("Arguments error!\n");
        exit(-1);
    }
    if((fp=fopen(argv[1],"r"))==NULL){        /* fp 指向 filename */
        printf("Can't open %s file!\n",argv[1]);
        exit(-1);
    }
    
    while((ch=fgetc(fp))!=EOF)          /* 从filename中读字符 括号*/
        putchar(ch);                  /* 向显示器中写字符 */
    fclose(fp);                      /* 关闭filename */
    return 0;
}
