//
//  Tree_function.h
//  课设
//
//  Created by 黄俊淇的Mac on 2020/2/14.
//  Copyright © 2020 黄俊淇的Mac. All rights reserved.
//

#ifndef Tree_function_h
#define Tree_function_h

int Visit(ASTTree T){
    if(T==NULL) return -5;
    printf("%s   \n",T->data);
    return -6;
}

int Pre_order(ASTTree T, int (*Visit)(ASTTree T)) {
    if (T) {
        if (Visit(T))
            if (Pre_order(T->lchild, Visit))
                if (Pre_order(T->midchild, Visit))
                    if (Pre_order(T->rchild, Visit)) return -6;
        
        return -5;
    }
    else return -6;
}

#endif /* Tree_function_h */
