//
//  function.h
//  课设
//
//  Created by 黄俊淇的Mac on 2020/2/14.
//  Copyright © 2020 黄俊淇的Mac. All rights reserved.
//

#ifndef function_h
#define function_h

ASTTree funcDef(FILE *fp){//函数定义和声明
    ASTTree root=NULL,p=NULL;
    int w;
    w=gettoken(fp);
    (root)=(ASTnode*)malloc(sizeof(ASTnode));
    (root)->lchild=NULL;
    (root)->rchild=NULL;
    (root)->midchild=NULL;
    strcpy((root)->data,"函数");
    
    
    w=gettoken(fp);
    (root)->lchild=(ASTnode*)malloc(sizeof(ASTnode));
    root->lchild->lchild=NULL;
    root->lchild->rchild=NULL;
    root->lchild->midchild=NULL;
    strcpy((root)->lchild->data,token_text);
    
    w=gettoken(fp);
    (root)->midchild=(ASTnode*)malloc(sizeof(ASTnode));
    (root)->midchild->lchild=NULL;
    (root)->midchild->rchild=NULL;
    (root)->midchild->midchild=NULL;
    strcpy((root)->midchild->data,token_text);
    
    w=gettoken(fp);
    //if(w!=LP) return NULL;
   while(w!=RP){
        w=gettoken(fp);
       switch(w){
           case INT:
        (root)->midchild->midchild=(ASTnode*)malloc(sizeof(ASTnode));
        (root)->midchild->midchild->lchild=NULL;
        (root)->midchild->midchild->rchild=NULL;
        (root)->midchild->midchild->midchild=NULL;
        strcpy((root)->midchild->midchild->data,"形参类型");
       
        (root)->midchild->midchild->lchild=(ASTnode*)malloc(sizeof(ASTnode));
        (root)->midchild->midchild->lchild->lchild=NULL;
        (root)->midchild->midchild->lchild->midchild=NULL;
        (root)->midchild->midchild->lchild->rchild=NULL;
        strcpy((root)->midchild->midchild->lchild->data,token_text);
        
        w=gettoken(fp);
        (p)=(ASTnode*)malloc(sizeof(ASTnode));
        p->lchild=NULL;
        p->rchild=NULL;
        p->midchild=NULL;
        strcpy(p->data,"形参名");
        (root)->midchild->midchild->rchild=p;
        (p)->lchild=(ASTnode*)malloc(sizeof(ASTnode));
        strcpy((p)->lchild->data,token_text);
        p->lchild->lchild=NULL;
        p->lchild->rchild=NULL;
        p->lchild->midchild=NULL;
        
        w=gettoken(fp);
        /*while(1){
            if(w==SEMI)
            {
                break;
            }
            else if(w==COMMA){
                w=gettoken(fp);
                if(w!=IDENT)
                {
                    printf("错误");
                    return NULL;
                }
                (q)=(ASTnode*)malloc(sizeof(ASTnode));
                q->lchild=NULL;
                q->rchild=NULL;
                q->midchild=NULL;
                strcpy((q)->data,"形参");
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
                printf("错误");
                return NULL;
            }
        }*/
               
               break;
           case FLOAT:
               (root)->midchild->lchild=(ASTnode*)malloc(sizeof(ASTnode));
               (root)->midchild->lchild->lchild=NULL;
               (root)->midchild->lchild->rchild=NULL;
               (root)->midchild->lchild->midchild=NULL;
               strcpy((root)->midchild->lchild->data,"形参类型");
               
               (root)->midchild->lchild->lchild=(ASTnode*)malloc(sizeof(ASTnode));
               (root)->midchild->lchild->lchild->lchild=NULL;
               (root)->midchild->lchild->lchild->midchild=NULL;
               (root)->midchild->lchild->lchild->rchild=NULL;
               strcpy((root)->midchild->lchild->lchild->data,token_text);
               
               w=gettoken(fp);
               (p)=(ASTnode*)malloc(sizeof(ASTnode));
               p->lchild=NULL;
               p->rchild=NULL;
               p->midchild=NULL;
               strcpy(p->data,"形参名");
               (root)->midchild->lchild->rchild=p;
               (p)->lchild=(ASTnode*)malloc(sizeof(ASTnode));
               strcpy((p)->lchild->data,token_text);
               p->lchild->lchild=NULL;
               p->lchild->rchild=NULL;
               p->lchild->midchild=NULL;
               
               /*w=gettoken(fp);
               while(1){
                   if(w==SEMI)
                   {
                       break;
                   }
                   else if(w==COMMA){
                       w=gettoken(fp);
                       if(w!=IDENT)
                       {
                           printf("错误");
                           return NULL;
                       }
                       (q)=(ASTnode*)malloc(sizeof(ASTnode));
                       q->lchild=NULL;
                       q->rchild=NULL;
                       q->midchild=NULL;
                       strcpy((q)->data,"形参");
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
                       printf("错误");
                       return NULL;
                   }
               }*/
               break;
           case CHAR:
               (root)->midchild->rchild=(ASTnode*)malloc(sizeof(ASTnode));
               (root)->midchild->rchild->lchild=NULL;
               (root)->midchild->rchild->rchild=NULL;
               (root)->midchild->rchild->midchild=NULL;
               strcpy((root)->midchild->rchild->data,"形参类型");
               
               (root)->midchild->rchild->lchild=(ASTnode*)malloc(sizeof(ASTnode));
               (root)->midchild->rchild->lchild->lchild=NULL;
               (root)->midchild->rchild->lchild->midchild=NULL;
               (root)->midchild->rchild->lchild->rchild=NULL;
               strcpy((root)->midchild->rchild->lchild->data,token_text);
               
               w=gettoken(fp);
               (p)=(ASTnode*)malloc(sizeof(ASTnode));
               p->lchild=NULL;
               p->rchild=NULL;
               p->midchild=NULL;
               strcpy(p->data,"形参名");
               (root)->midchild->rchild->rchild=p;
               (p)->lchild=(ASTnode*)malloc(sizeof(ASTnode));
               strcpy((p)->lchild->data,token_text);
               p->lchild->lchild=NULL;
               p->lchild->rchild=NULL;
               p->lchild->midchild=NULL;
               break;
       }
    }
    
    w=gettoken(fp);
    (root)->rchild=(ASTnode*)malloc(sizeof(ASTnode));
    root->rchild->lchild=NULL;
    (root)->rchild->rchild=NULL;
    (root)->rchild->midchild=NULL;
    if(w==SEMI){
        strcpy((root)->rchild->data,"函数声明");
        return root;
    }
    else{
        if(w!=LPP) return NULL;
        else{
            strcpy((root)->rchild->data,"函数体");
            (root)->rchild->lchild=(ASTnode*)malloc(sizeof(ASTnode));
            (root)->rchild->lchild->lchild=NULL;
            (root)->rchild->lchild->midchild=NULL;
            (root)->rchild->lchild->rchild=NULL;
            //if(complex(fp)==NULL) return NULL;
            (root)->rchild->lchild=complex(fp);
        }
    }
    
    return root;
}

#endif /* function_h */
