//
//  词法分析.h
//  课设
//
//  Created by 黄俊淇的Mac on 2020/2/14.
//  Copyright © 2020 黄俊淇的Mac. All rights reserved.
//
#include"预定义常量.h"
#ifndef _____h
#define _____h

int gettoken(FILE *fp){
    memset(token_text,0, sizeof(token_text));
    char c;
    int i,j=0;
    int count=0;
    c=fgetc(fp);
    while(1){
        if(c==' ') c=fgetc(fp);
        else break;
    }
    if((c>='A'&&c<='Z')||(c>='a'&&c<='z')||(c=='_')){
        do{
            token_text[j++]=c;
            c=fgetc(fp);
            if(c=='.')
            {
                token_text[j++]=c;
                c=fgetc(fp);
                if(c=='h')
                {token_text[j++]=c; return hfile;}
                else return ERROR_TOKEN;
            }
        }while((c>='A'&&c<='Z')||(c>='a'&&c<='z')||(c>='0'&&c<='9'));
        ungetc(c,fp);
      for(i=0;i<11;i++){
            if(strcmp(keywords[i],token_text)==0)
                return i;
        }
        return IDENT;
    }
    if(c>='0'&&c<='9'){
        do{
            token_text[j++]=c;
            c=fgetc(fp);
            if(c=='x')
            {token_text[j++]=c;
                c=fgetc(fp);
                if(c<='0'||c>='9') return ERROR_TOKEN;
            }
            else if(c>='a'&&c<='z') return ERROR_TOKEN;
        }while((c>='0'&&c<='9'));
        ungetc(c,fp);
        return INT_CONST;
    }
    switch (c) {
        case '=':c=fgetc(fp);
            if(c=='=') return EQ;
            ungetc(c,fp);
            return ASSIGN;
        case '+':c=fgetc(fp);
            if(c=='+') return PLUSPLUS;
            ungetc(c,fp);
            return PLUS;
        case '-':c=fgetc(fp);
            if(c=='-') return MINUSMINUS;
            ungetc(c,fp);
            return MINUS;
        case '*':
            return MULTIPLY;
        case '/':
            return DIVIDE;
        case ';':
            return SEMI;
        case ',':
            return COMMA;
        case '%':
            return MOD;
        case '&':c=fgetc(fp);
            if(c=='&') return AND;
            ungetc(c,fp);
            return ERROR_TOKEN;
        case '|':c=fgetc(fp);
            if(c=='|') return OR;
            ungetc(c,fp);
            return ERROR_TOKEN;
        case '(':
            return LP;
        case ')':
            return RP;
        case '\n':count++;
            break;
        case '>':return BIG;
        case '<':return SMALL;
        case '{':return LPP;
        case '}':return RPP;
        case '#':return EXP;
        case '!':c=fgetc(fp);
            if(c=='=') return EM;
            else return ERROR_TOKEN;
        default:if(feof(fp)) return EOF;
        else return ERROR_TOKEN;
    }
    return 100;
}
#endif /* _____h */
