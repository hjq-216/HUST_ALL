//
//  main.c
//  课设
//
//  Created by 黄俊淇的Mac on 2020/2/11.
//  Copyright © 2020 黄俊淇的Mac. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "预定义常量.h"
#include "词法分析.h"
#include "Tree_function.h"
#include "variable.h"
#include "complex_sentences.h"
#include "function.h"
#include "expression.h"
#include "栈.h"

int main() {
    FILE *fp,*fp1;
    char filename[30];
    int num;
    int w;
    ASTTree root,T,T1;
    printf("input file name: ");
    scanf("%s",filename);
    //读文件的方法
    if ((fp=fopen(filename,"rb"))==NULL)
    {
        printf("File open error\n ");
        return -1;
    }
    printf("单词类别        单词值\n");
    while(!feof(fp)){
        num=gettoken(fp);
        switch(num){
            case INT:printf("关键字        %s\n",token_text);
                break;
            case CHAR:printf("关键字        %s\n",token_text);
                break;
            case FLOAT:printf("关键字        %s\n",token_text);
                break;
            case WHILE:printf("关键字        %s\n",token_text);
                break;
            case IF:printf("关键字        %s\n",token_text);
                break;
            case ELSE:printf("关键字        %s\n",token_text);
                break;
            case BREAK:printf("关键字        %s\n",token_text);
                break;
            case FOR:printf("关键字        %s\n",token_text);
                break;
            case RETURN:printf("关键字        %s\n",token_text);
                break;
            case CONTINUE:printf("关键字        %s\n",token_text);
                break;
            case INCLUDE:printf("关键字        %s\n",token_text);
                break;
            case hfile:printf("头文件        %s\n",token_text);
                break;
            case ERROR_TOKEN:printf("错误\n");
                break;
            case IDENT:printf("标识符        %s\n",token_text);
                break;
            case INT_CONST:printf("整型常量       %s\n",token_text);
                break;
            case EQ:printf("赋值号        %s\n",token_text);
                break;
            case PLUS:printf("加号        +\n");
                break;
            case PLUSPLUS:printf("自增       ++\n");
                break;
            case MINUS:printf("减号       -\n");
                break;
            case MINUSMINUS:printf("自减       --\n");
                break;
            case MULTIPLY:printf("乘号         *\n");
                break;
            case DIVIDE:printf("除号         /\n");
                break;
            case SEMI:printf("分号         ;\n");
                break;
            case COMMA:printf("逗号        ,\n");
                break;
            case MOD:printf("求余号        %s\n",token_text);
                break;
            case AND:printf("逻辑与        &&\n");
                break;
            case OR:printf("逻辑或        ||\n");
                break;
            case LP:printf("左括号        (\n");
                break;
            case RP:printf("右括号        )\n");
                break;
            case ASSIGN:printf("赋值号        =\n");
                break;
            case SMALL:printf("比较符       <\n");
                break;
            case BIG:printf("比较符       >\n");
                break;
            case EM:printf("比较符       !=\n");
                break;
            case LPP:printf("左大括号       {\n");
                break;
            case RPP:printf("右大括号       }\n");
                break;
            case EXP:printf("井号         #\n");
                break;
        }
    }
    fclose(fp);
    printf("input file name: ");
    scanf("%s",filename);
    //读文件的方法
    if ((fp=fopen(filename,"rb"))==NULL)
    {
        printf("File open error\n ");
        return -1;
    }
    while(!feof(fp)){
        T1=pre(fp);
        if(T1==NULL) printf("预处理错误");
        root=ExtVarDef(fp);
        T=funcDef(fp);
        
        if(root==NULL) {printf("错误");break;}
        if(T==NULL) {
            printf("错误");
            break;
        }
         Pre_order(T1,Visit);
        Pre_order(root,Visit);
        Pre_order(T,Visit);
        w=gettoken(fp);
    }
    fclose(fp);
    printf("input file name: ");
    scanf("%s",filename);
    if ((fp=fopen(filename,"rb"))==NULL)
    {
        printf("File open error\n ");
        return -1;
    }
    
    printf("input file name: ");
    scanf("%s",filename);
    if ((fp1=fopen(filename,"w"))==NULL)
    {
        printf("File open error\n ");
        return -1;
    }
    while(!feof(fp)){
        num=gettoken(fp);
        fprintf(fp1,"%s\n",token_text);
    }
    fclose(fp);
    fclose(fp1);
    return 0;
}

