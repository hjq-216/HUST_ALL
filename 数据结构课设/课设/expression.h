//
//  expression.h
//  课设
//
//  Created by 黄俊淇的Mac on 2020/2/14.
//  Copyright © 2020 黄俊淇的Mac. All rights reserved.
//

#ifndef expression_h
#define expression_h
#include "预定义常量.h"
#include "栈.h"
char MYprecede(char *lastc,char *token_text){
    char precede[10][10]=
    {       //              +  -    *   /   %  （   ）  =   >和< ==和!=
        /* + */            {'=','>','<','<','<','<','>','?','>','>'},
        /* - */            {'>','=','<','<','<','<','>','?','>','>'},
        /* * */            {'>','>','=','>','>','<','>','?','>','>'},
        /* / */            {'>','>','>','=','>','<','>','?','>','>'},
        /* % */            {'>','>','<','<','=','<','>','?','>','>'},
        /* ( */            {'<','<','<','<','<','<','=','?','<','>'},
        /* ) */            {'>','>','>','>','>','>','?','?','>','>'},
        /* = */            {'<','<','<','<','<','<','?','<','<','<'},
        /* >和< */         {'<','<','<','<','<','<','>','?','>','<'},
        /*!=和==*/         {'<','<','<','<','<','<','<','<','<','<'}
    };
    int i=0,j=0;
    if(strcmp(lastc,"+")==0) i=0;
    if(strcmp(lastc,"-")==0) i=1;
    if(strcmp(lastc,"*")==0) i=2;
    if(strcmp(lastc,"/")==0) i=3;
    if(strcmp(lastc,"%")==0) i=4;
    if(strcmp(lastc,"(")==0) i=5;
    if(strcmp(lastc,")")==0) i=6;
    if(strcmp(lastc,"=")==0) i=7;
    if((strcmp(lastc,">")==0)||(strcmp(lastc,">")==0)) i=8;
    if((strcmp(lastc,"!=")==0)||(strcmp(lastc,"==")==0)) i=9;
        
    if(strcmp(token_text,"+")==0) j=0;
    if(strcmp(token_text,"-")==0) j=1;
    if(strcmp(token_text,"*")==0) j=2;
    if(strcmp(token_text,"/")==0) j=3;
    if(strcmp(token_text,"%")==0) j=4;
    if(strcmp(token_text,"(")==0) j=5;
    if(strcmp(token_text,")")==0) j=6;
    if(strcmp(token_text,"=")==0) j=7;
    if(strcmp(token_text,"!=")==0) j=8;
    if((strcmp(token_text,">")==0)||(strcmp(token_text,">")==0)) i=8;
    if((strcmp(token_text,"!=")==0)||(strcmp(token_text,"==")==0)) i=9;
    return precede[i][j];
}
ASTTree MYexp(FILE *fp){
    int w;
    char token_text0[100];
    char lastc[100];
    ASTTree root = NULL,p=NULL;
    //stack *op = NULL;
    //myinitstack(op);
    (root)=(ASTTree)malloc(sizeof(ASTnode));
    (root)->lchild=NULL;
    (root)->rchild=NULL;
    (root)->midchild=NULL;
    
    w=gettoken(fp);
    //printf("aaa%s",token_text);
    //if(w!=INT_CONST||w!=IDENT) return NULL;
    strcpy(token_text0,token_text);
    
    w=gettoken(fp);
    if(w==BIG) strcpy((root)->data,">");
    if(w==SMALL) strcpy(root->data,"<");
    if(w==EM) strcpy(root->data,"!=");
    if(w==EQ) strcpy(root->data,"==");
    if(w==ASSIGN) strcpy(root->data,"=");
    if(w==PLUS) strcpy(root->data,"+");
    if(w==MINUS) strcpy(root->data,"-");
    if(w==MULTIPLY) strcpy(root->data,"*");
    if(w==DIVIDE) strcpy(root->data,"/");
    if(w==PLUSPLUS) strcpy(root->data,"++");
    if(w==MINUSMINUS) strcpy(root->data,"--");
    if(w==SEMI||w==RP){
        strcpy(root->data,token_text0);
        return root;
    }
    (root)->lchild=(ASTTree)malloc(sizeof(ASTnode));
    (root)->lchild->lchild=NULL;
    (root)->lchild->rchild=NULL;
    (root)->lchild->midchild=NULL;
    strcpy((root)->lchild->data,token_text0);
    strcpy(lastc,token_text);
    //if(w==MULTIPLY) printf("hjq");
    w=gettoken(fp);
    if(w==RP) { return root;}
    strcpy(token_text0,token_text);//
    w=gettoken(fp);
    //if(w==MULTIPLY) printf("11%s",token_text);
    if(w==SEMI||w==RP){
        (root)->rchild=(ASTTree)malloc(sizeof(ASTnode));
        (root)->rchild->lchild=NULL;
        (root)->rchild->rchild=NULL;
        (root)->rchild->midchild=NULL;
        strcpy((root)->rchild->data,token_text0);}
    else if(w>=EQ&&w<=SMALL){
            //printf("%c",MYprecede(lastc,token_text));
        
            if(MYprecede(lastc,token_text)=='<'){
                p=(ASTTree)malloc(sizeof(ASTnode));
                p->lchild=NULL;
                p->midchild=NULL;
                p->rchild=NULL;
                if(w==PLUS) strcpy(p->data,"+");
                if(w==MINUS) strcpy(p->data,"-");
                if(w==MULTIPLY) strcpy(p->data,"*");
                if(w==DIVIDE) strcpy(p->data,"/");
                if(w==BIG) strcpy((p)->data,">");
                if(w==SMALL) strcpy(p->data,"<");
                if(w==EM) strcpy(p->data,"!=");
                if(w==EQ) strcpy(p->data,"==");
                if(w==ASSIGN) strcpy(p->data,"=");
                p->lchild=(ASTTree)malloc(sizeof(ASTnode));
                p->lchild->lchild=NULL;
                p->lchild->midchild=NULL;
                p->lchild->rchild=NULL;
                p->rchild=(ASTTree)malloc(sizeof(ASTnode));
                p->rchild->lchild=NULL;
                p->rchild->midchild=NULL;
                p->rchild->rchild=NULL;
                strcpy(p->lchild->data,token_text0);
                w=gettoken(fp);
                strcpy(p->rchild->data,token_text);
                root->rchild=p;
                w=gettoken(fp);
                if(w==SEMI||w==RP) return root;
            }
            else if(MYprecede(lastc,token_text)=='>'){
                (root)->rchild=(ASTTree)malloc(sizeof(ASTnode));
                (root)->rchild->lchild=NULL;
                (root)->rchild->rchild=NULL;
                (root)->rchild->midchild=NULL;
                strcpy((root)->rchild->data,token_text0);
                p=(ASTTree)malloc(sizeof(ASTnode));
                p->lchild=NULL;
                p->midchild=NULL;
                p->rchild=NULL;
                if(w==PLUS) strcpy(p->data,"+");
                if(w==MINUS) strcpy(p->data,"-");
                if(w==MULTIPLY) strcpy(p->data,"*");
                if(w==DIVIDE) strcpy(p->data,"/");
                if(w==BIG) strcpy((p)->data,">");
                if(w==SMALL) strcpy(p->data,"<");
                if(w==EM) strcpy(p->data,"!=");
                if(w==EQ) strcpy(p->data,"==");
                if(w==ASSIGN) strcpy(p->data,"=");
                p->lchild=(ASTTree)malloc(sizeof(ASTnode));
                p->lchild->lchild=NULL;
                p->lchild->midchild=NULL;
                p->lchild->rchild=NULL;
                p->rchild=(ASTTree)malloc(sizeof(ASTnode));
                p->rchild->lchild=NULL;
                p->rchild->midchild=NULL;
                p->rchild->rchild=NULL;
                p->lchild=root;
                w=gettoken(fp);
                strcpy(p->rchild->data,token_text);
                root=p;
                w=gettoken(fp);
                if(w==SEMI||w==RP) return root;
            }
            else if(MYprecede(lastc,token_text)=='='){
                p=(ASTTree)malloc(sizeof(ASTnode));
                p->lchild=NULL;
                p->midchild=NULL;
                p->rchild=NULL;
                if(w==PLUS) strcpy(p->data,"+");
                if(w==MINUS) strcpy(p->data,"-");
                if(w==MULTIPLY) strcpy(p->data,"*");
                if(w==DIVIDE) strcpy(p->data,"/");
                if(w==BIG) strcpy((p)->data,">");
                if(w==SMALL) strcpy(p->data,"<");
                if(w==EM) strcpy(p->data,"!=");
                if(w==EQ) strcpy(p->data,"==");
                if(w==ASSIGN) strcpy(p->data,"=");
                p->lchild=(ASTTree)malloc(sizeof(ASTnode));
                p->lchild->lchild=NULL;
                p->lchild->midchild=NULL;
                p->lchild->rchild=NULL;
                p->rchild=(ASTTree)malloc(sizeof(ASTnode));
                p->rchild->lchild=NULL;
                p->rchild->midchild=NULL;
                p->rchild->rchild=NULL;
                strcpy(p->lchild->data,token_text0);
                w=gettoken(fp);
                strcpy(p->rchild->data,token_text);
                root->rchild=p;
                w=gettoken(fp);
                if(w==SEMI||w==RP) return root;
            }
        
    }
    return root;
}

#endif /* expression_h */
