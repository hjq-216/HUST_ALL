//
//  variable.h
//  课设
//
//  Created by 黄俊淇的Mac on 2020/2/14.
//  Copyright © 2020 黄俊淇的Mac. All rights reserved.
//

#ifndef variable_h
#define variable_h
ASTTree pre(FILE *fp){
    int w;
    ASTTree root=NULL;
    root=(ASTTree)malloc(sizeof(ASTnode));
    root->lchild=(ASTTree)malloc(sizeof(ASTnode));
    root->lchild->lchild=NULL;
    root->lchild->midchild=NULL;
    root->lchild->rchild=NULL;
    root->midchild=(ASTTree)malloc(sizeof(ASTnode));
    root->midchild->lchild=NULL;
    root->midchild->midchild=NULL;
    root->midchild->rchild=NULL;
    root->rchild=(ASTTree)malloc(sizeof(ASTnode));
    root->rchild->lchild=NULL;
    root->rchild->midchild=NULL;
    root->rchild->rchild=NULL;
    strcpy(root->data,"编译预处理");
    w=gettoken(fp);
    if(w!=EXP) return NULL;
    strcpy(root->lchild->data,"#");
    w=gettoken(fp);
    if(w!=INCLUDE) return NULL;
    strcpy(root->midchild->data,"include");
    w=gettoken(fp);
    if(w!=SMALL) return NULL;
    w=gettoken(fp);
    if(w!=hfile) return NULL;
    strcpy(root->rchild->data,token_text);
    w=gettoken(fp);
    if(w!=BIG) return NULL;
    w=gettoken(fp);
    return root;
}
ASTTree ExtVarDef(FILE *fp){//外部变量
    char token_text0[100];
    int w;
    ASTTree root=NULL,p=NULL,q=NULL;

    root=(ASTTree)malloc(sizeof(ASTnode));
    root->midchild=NULL;
    strcpy((root)->data,"外部变量类型：");
    
    w=gettoken(fp);
    strcpy(token_text0,token_text);
    (root)->lchild=(ASTnode*)malloc(sizeof(ASTnode));
    strcpy((root)->lchild->data,token_text0);
    root->lchild->lchild=NULL;
    root->lchild->rchild=NULL;
    root->lchild->midchild=NULL;
    
    (p)=(ASTnode*)malloc(sizeof(ASTnode));
    p->lchild=NULL;
    p->rchild=NULL;
    p->midchild=NULL;
    (root)->rchild=p;
    strcpy((p)->data,"外部变量名：");
    
    w=gettoken(fp);
    
    strcpy(token_text0,token_text);
    (p)->lchild=(ASTnode*)malloc(sizeof(ASTnode));
    strcpy((p)->lchild->data,token_text0);
    p->lchild->lchild=NULL;
    p->lchild->rchild=NULL;
    p->lchild->midchild=NULL;
    
    w=gettoken(fp);
    while(1){
        if(w==SEMI)
        {
            return root;
        }
        else if(w==COMMA){
            w=gettoken(fp);
            if(w!=IDENT)
            {
                //printf("错误");
                return NULL;
            }
            (q)=(ASTnode*)malloc(sizeof(ASTnode));
            q->lchild=NULL;
            q->rchild=NULL;
            q->midchild=NULL;
            strcpy((q)->data,"外部变量名：");
            (p)->rchild=q;
            p=q;
            (p)->lchild=(ASTnode*)malloc(sizeof(ASTnode));
            p->lchild->lchild=NULL;
            p->lchild->rchild=NULL;
            p->lchild->midchild=NULL;
            strcpy((p)->lchild->data,token_text);
            w=gettoken(fp);
        }
        else{
            //printf("错误");
            return NULL;
        }
    }
}
ASTTree ExtVarDef1(FILE *fp){//外部变量
    char token_text0[100];
    int w;
    ASTTree root=NULL,p=NULL,q=NULL;
    
    root=(ASTTree)malloc(sizeof(ASTnode));
    root->midchild=NULL;
    strcpy((root)->data,"局部变量类型：");
    
    
    strcpy(token_text0,token_text);
    (root)->lchild=(ASTnode*)malloc(sizeof(ASTnode));
    strcpy((root)->lchild->data,token_text0);
    root->lchild->lchild=NULL;
    root->lchild->rchild=NULL;
    root->lchild->midchild=NULL;
    
    (p)=(ASTnode*)malloc(sizeof(ASTnode));
    p->lchild=NULL;
    p->rchild=NULL;
    p->midchild=NULL;
    (root)->rchild=p;
    strcpy((p)->data,"局部变量名：");
    
    w=gettoken(fp);
    strcpy(token_text0,token_text);
    (p)->lchild=(ASTnode*)malloc(sizeof(ASTnode));
    strcpy((p)->lchild->data,token_text0);
    p->lchild->lchild=NULL;
    p->lchild->rchild=NULL;
    p->lchild->midchild=NULL;
    
    w=gettoken(fp);
    while(1){
        if(w==SEMI)
        {
            return root;
        }
        else if(w==COMMA){
            w=gettoken(fp);
            if(w!=IDENT)
            {
                //printf("错误");
                return NULL;
            }
            (q)=(ASTnode*)malloc(sizeof(ASTnode));
            q->lchild=NULL;
            q->rchild=NULL;
            q->midchild=NULL;
            strcpy((q)->data,"局部变量名：");
            (p)->rchild=q;
            p=q;
            (p)->lchild=(ASTnode*)malloc(sizeof(ASTnode));
            p->lchild->lchild=NULL;
            p->lchild->rchild=NULL;
            p->lchild->midchild=NULL;
            strcpy((p)->lchild->data,token_text);
            w=gettoken(fp);
        }
        else{
            //printf("错误");
            return NULL;
        }
    }
}

#endif /* variable_h */
