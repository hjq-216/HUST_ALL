//
//  栈.h
//  课设
//
//  Created by 黄俊淇的Mac on 2020/2/15.
//  Copyright © 2020 黄俊淇的Mac. All rights reserved.
//

#ifndef __h
#define __h

void myinitstack(stack *int_sta){
    int_sta->base=(int *)malloc(sizeof(int)*100);
    int_sta->top=int_sta->base;
}
void deletestack(stack  *int_sta){
    free(int_sta->base);
}
void push(stack *int_sta,int i){
    *(int_sta->top++)=i;
}
int pop(stack *int_sta,int *i){
    if(int_sta->top==int_sta->base) return 0;
    else{
        *i=*(--int_sta->top);
        return 1;
    }
}
#endif /* __h */
