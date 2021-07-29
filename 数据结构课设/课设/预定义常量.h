//
//  预定义常量.h
//  课设
//
//  Created by 黄俊淇的Mac on 2020/2/14.
//  Copyright © 2020 黄俊淇的Mac. All rights reserved.
//

#ifndef ______h
#define ______h

char keywords[11][11]={"int","char","float","while","if","else","break","for","return","continue","include"
};
enum token_kind{INT=0,CHAR,FLOAT,WHILE,IF,ELSE,BREAK,FOR,RETURN,CONTINUE,INCLUDE,hfile,ERROR_TOKEN,INT_CONST,EQ,IDENT,PLUS,PLUSPLUS,MINUS,MINUSMINUS,MULTIPLY,DIVIDE,ASSIGN,SEMI,COMMA,MOD,AND,OR,LP,RP,BIG,SMALL,EM,LPP,RPP,EXP};
char token_text[100];

typedef struct ASTnode{
    char data[100];
    struct ASTnode *lchild;
    struct ASTnode *rchild;
    struct ASTnode *midchild;
    
}ASTnode,*ASTTree;
struct GA1{
    char name;
    int h;
};

typedef struct stack{
    int *base;
    int *top;
}stack;


#endif /* ______h */
