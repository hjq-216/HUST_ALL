//
//  complex_sentences.h
//  课设
//
//  Created by 黄俊淇的Mac on 2020/2/14.
//  Copyright © 2020 黄俊淇的Mac. All rights reserved.
//

#ifndef complex_sentences_h
#define complex_sentences_h
#include "expression.h"
ASTTree complex(FILE*fp){//复合语句
    int w;
    int wrong=0;
    ASTTree root = NULL;
    ASTTree IF_ELSE=NULL,MYwhile=NULL,MYfor=NULL;
    (root)=(ASTnode*)malloc(sizeof(ASTnode));
    (root)->lchild=NULL;
    (root)->rchild=NULL;
    (root)->midchild=NULL;
    
    (root)->rchild=(ASTnode*)malloc(sizeof(ASTnode));//if-else
    root->rchild->lchild=NULL;
    root->rchild->rchild=NULL;
    root->rchild->midchild=NULL;
    strcpy(root->rchild->data,"if-else语句");
    (root)->rchild->rchild=(ASTnode*)malloc(sizeof(ASTnode));//return
    root->rchild->rchild->lchild=NULL;
    root->rchild->rchild->rchild=NULL;
    root->rchild->rchild->midchild=NULL;
    strcpy(root->rchild->rchild->data,"return语句");
    (root)->rchild->rchild->rchild=(ASTnode*)malloc(sizeof(ASTnode));//while
    root->rchild->rchild->rchild->lchild=NULL;
    root->rchild->rchild->rchild->rchild=NULL;
    root->rchild->rchild->rchild->midchild=NULL;
    strcpy(root->rchild->rchild->rchild->data,"while语句");
    (root)->rchild->rchild->rchild->rchild=(ASTnode*)malloc(sizeof(ASTnode));//for
    root->rchild->rchild->rchild->rchild->lchild=NULL;
    root->rchild->rchild->rchild->rchild->rchild=NULL;
    root->rchild->rchild->rchild->rchild->midchild=NULL;
    strcpy(root->rchild->rchild->rchild->rchild->data,"for语句");
    (root)->rchild->rchild->rchild->rchild->rchild=(ASTnode*)malloc(sizeof(ASTnode));//expression
    root->rchild->rchild->rchild->rchild->rchild->lchild=NULL;
    root->rchild->rchild->rchild->rchild->rchild->rchild=NULL;
    root->rchild->rchild->rchild->rchild->rchild->midchild=NULL;
    strcpy(root->rchild->rchild->rchild->rchild->rchild->data,"表达式");
    
    (IF_ELSE)=(ASTnode*)malloc(sizeof(ASTnode));
    (IF_ELSE)->lchild=NULL;
    (IF_ELSE)->rchild=NULL;
    (IF_ELSE)->midchild=NULL;
    strcpy((IF_ELSE)->data,"if-else");
    MYwhile=(ASTnode*)malloc(sizeof(ASTnode));
    MYwhile->lchild=NULL;
    MYwhile->rchild=NULL;
    MYwhile->midchild=NULL;
    strcpy((MYwhile)->data,"while");
    MYfor=(ASTnode*)malloc(sizeof(ASTnode));
    MYfor->lchild=NULL;
    MYfor->rchild=NULL;
    MYfor->midchild=NULL;
    strcpy((MYfor)->data,"for");
    
    strcpy((root)->data,"复合语句");
    w=gettoken(fp);
    w=gettoken(fp);
    while(w!=RPP){
    if(w>=INT&&w<=FLOAT){
        root->lchild=ExtVarDef1(fp);
    }
    else{
        //w=gettoken(fp);
        //printf("%s",token_text);
        switch(w){
            case IF:
                w=gettoken(fp);
                //printf("%s",token_text);
                if(w!=LP) wrong=1;
                (IF_ELSE)->lchild=MYexp(fp);
                (IF_ELSE)->midchild=MYexp(fp);
                w=gettoken(fp);
                
                w=gettoken(fp);
                if(w!=ELSE) wrong=1;
                (IF_ELSE)->rchild=MYexp(fp);
                (root)->rchild->lchild=IF_ELSE;
                w=gettoken(fp);
                //w=gettoken(fp);
                
                break;
            case RETURN:
                (root)->rchild->rchild->lchild=(ASTnode*)malloc(sizeof(ASTnode));//return
                root->rchild->rchild->lchild->lchild=NULL;
                root->rchild->rchild->lchild->rchild=NULL;
                root->rchild->rchild->lchild->midchild=NULL;
                strcpy(root->rchild->rchild->lchild->data,"return");
                //w=gettoken(fp);
                (root)->rchild->rchild->lchild->lchild=(ASTnode*)malloc(sizeof(ASTnode));//return
                root->rchild->rchild->lchild->lchild->lchild=NULL;
                root->rchild->rchild->lchild->lchild->rchild=NULL;
                root->rchild->rchild->lchild->lchild->midchild=NULL;
                root->rchild->rchild->lchild->lchild=MYexp(fp);
                w=gettoken(fp);
                break;
            case WHILE:
                w=gettoken(fp);
                //printf("%s",token_text);
                if(w!=LP) return NULL;
                MYwhile->lchild=(ASTTree)malloc(sizeof(ASTnode));
                MYwhile->lchild->lchild=NULL;
                MYwhile->lchild->rchild=NULL;
                MYwhile->lchild->midchild=NULL;
                (MYwhile)->lchild=MYexp(fp);
                w=gettoken(fp);
                if(w==SEMI){
                    MYwhile->midchild=(ASTTree)malloc(sizeof(ASTnode));
                    MYwhile->midchild->lchild=NULL;
                    MYwhile->midchild->rchild=NULL;
                    MYwhile->midchild->midchild=NULL;
                    strcpy(MYwhile->midchild->data,"死循环");
                }
                else if(w==LPP){
                    MYwhile->rchild=(ASTTree)malloc(sizeof(ASTnode));
                    MYwhile->rchild->lchild=NULL;
                    MYwhile->rchild->rchild=NULL;
                    MYwhile->rchild->midchild=NULL;
                    strcpy(MYwhile->rchild->data,"循环体");
                    MYwhile->rchild->lchild=complex(fp);
                    
                }
                else{
                    wrong=1;
                }
                (root)->rchild->rchild->rchild->lchild=MYwhile;
                break;
            case FOR:
                w=gettoken(fp);
                //printf("111%s\n",token_text);
                if(w!=LP) return NULL;
                MYfor->lchild=(ASTTree)malloc(sizeof(ASTnode));
                MYfor->lchild->lchild=NULL;
                MYfor->lchild->rchild=NULL;
                MYfor->lchild->midchild=NULL;
                MYfor->lchild->lchild=MYexp(fp);
                MYfor->lchild->midchild=MYexp(fp);
                MYfor->lchild->rchild=MYexp(fp);
                w=gettoken(fp);
                if(w==SEMI){
                    MYfor->midchild=(ASTTree)malloc(sizeof(ASTnode));
                    MYfor->midchild->lchild=NULL;
                    MYfor->midchild->rchild=NULL;
                    MYfor->midchild->midchild=NULL;
                    strcpy(MYfor->midchild->data,"死循环");
                }
                else if(w==LPP){
                    MYfor->rchild=(ASTTree)malloc(sizeof(ASTnode));
                    MYfor->rchild->lchild=NULL;
                    MYfor->rchild->rchild=NULL;
                    MYfor->rchild->midchild=NULL;
                    strcpy(MYfor->rchild->data,"循环体");
                    MYfor->rchild->lchild=complex(fp);
                    
                }
                else{
                    wrong=1;
                }
                (root)->rchild->rchild->rchild->rchild->lchild=MYfor;
                break;
            case EXP:
                root->rchild->rchild->rchild->rchild->rchild->lchild=MYexp(fp);
                break;
            case IDENT:
                root->rchild->rchild->rchild->rchild->rchild->lchild=MYexp(fp);
                break;
                //w=gettoken(fp);
        }
        
    }
        w=gettoken(fp);
        
    }
    if(wrong==1) root=NULL;
    return root;
}

#endif /* complex_sentences_h */
