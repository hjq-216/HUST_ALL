//
//  main.c
//  数据结构实验二
//
//  Created by 黄俊淇的Mac on 2019/10/28.
//  Copyright © 2019 黄俊淇的Mac. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct Node{
    ElemType data;
    struct Node *next;
}Node,*Lnode;
/*-----page 19 on textbook ---------*/
status InitList(Lnode *L);
status DestroyList(Lnode *L);
status ClearList(Lnode *L);
status ListEmpty(Lnode *L);
status ListLength(Lnode *L);
status GetElem(Lnode *L,int i,ElemType *e);
status LocateElem(Lnode *L,ElemType e); //简化过
status PriorElem(Lnode *L,ElemType cur_e,ElemType *pre_e);
status NextElem(Lnode *L,ElemType cur_e,ElemType *next_e);
status ListInsert(Lnode *L,int i,ElemType e);
status ListDelete(Lnode *L,int i,ElemType *e);
status ListTrabverse(Lnode *L);  //简化过
status Writefile(Lnode *L);
status Readfile(Lnode *L);
status Changelist(int *N);
status compare(int i,ElemType e);
/*--------------------------------------------*/
int main(void){
    Lnode List[100];//多表存储于一个结构数组
    int N;
    printf("请输入0～99以确定将对哪个链表进行处理\n");
    scanf("%d",&N);//N为顺序表编号
    int op=1,i;
    ElemType e,cur_e,pre_e,next_e;
    while(op){
        system("cls");    printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("          1. InitList       8. PriorElem\n");
        printf("          2. DestroyList    9. NextElem\n");
        printf("          3. ClearList      10. ListInsert \n");
        printf("          4. ListEmpty      11. ListDelete\n");
        printf("          5. ListLength     12. ListTrabverse\n");
        printf("          6. GetElem        13. Writefile\n");
        printf("          7.LocateElem      14. Readfile\n");
        printf("          15.Changelist      0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~12]:");
        scanf("%d",&op);
        switch(op){
            case 1:
                if(InitList(&List[N])==OK) printf("线性表创建成功！\n");
                else printf("线性表创建失败！\n");
                getchar();getchar();
                break;
            case 2:
                if(DestroyList(&List[N])==OK) printf("销毁成功");
                else printf("不存在可执行线性表");
                getchar();getchar();
                break;
            case 3:
                if(ClearList(&List[N])==OK) printf("清空成功");
                else  if(ClearList(&List[N])==ERROR) printf("不存在可执行线性表");
                getchar();getchar();
                break;
            case 4:
                if(ListEmpty(&List[N])==TRUE) printf("该表为空表");
                else if(ListEmpty(&List[N])==FALSE) printf("该表不是空表");
                else printf("不存在可执行线性表");
                getchar();getchar();
                break;
            case 5:
                if(ListLength(&List[N])==-1) printf("不存在可执行线性表");
                else printf("该表长为%d",ListLength(&List[N]));
                getchar();getchar();
                break;
            case 6:
                printf("请输入要获取元素的位置\n");
                scanf("%d",&i);
                if(GetElem(&List[N],i,&e)==OVERFLOW) printf("输入不合法\n");
                if(GetElem(&List[N],i,&e)==-1) printf("输入不合法\n");
                else
                    printf("第%d个数据元素的值为%d",i,e);
                getchar();getchar();
                break;
            case 7:
                printf("请输入要查找的值\n");
                scanf("%d",&e);
                if(LocateElem(&List[N],e)==0) printf("不存在需要查找的元素\n");
                else if(LocateElem(&List[N],e)==-1)printf("不存在可执行线性表");
                else if(LocateElem(&List[N],e)) printf("您要查找的元素是第%d元素\n",LocateElem(&List[N],e));
                getchar();getchar();
                break;
            case 8:
                printf("请输入cur_e\n");
                scanf("%d",&cur_e);
                if(PriorElem(&List[N],cur_e,&pre_e)==1) printf("找到cur_e的前驱为%d\n",pre_e);
                else printf("未找到cur_e的前驱\n");
                getchar();getchar();
                break;
            case 9:
                printf("请输入cur_e\n");
                scanf("%d",&cur_e);
                if(NextElem(&List[N],cur_e,&next_e)==1) printf("找到cur_e的后继为%d\n",next_e);
                else printf("未找到cur_e的后继\n");
                getchar();getchar();
                break;
            case 10:
                printf("请输入要插入的位置\n");
                scanf("%d",&i);
                printf("请输入要插入的元素\n");
                scanf("%d",&e);
                if(ListInsert(&List[N],i,e)==OK) {
                    printf("插入成功\n");
                    break;}
                else if(ListInsert(&List[N],i,e)==ERROR) printf("输入不合法\n");
                else if(ListInsert(&List[N],i,e)==-1)  printf("不存在该线性表\n");
                else printf("分配空间不足\n");
                getchar();getchar();
                break;
            case 11:
                printf("请输入要删除元素的位置\n");
                scanf("%d",&i);
                if(ListDelete(&List[N],i,&e)==OK) printf("删除成功，删除的元素为%d\n",e);
                else printf("输入不合法\n");
                getchar();getchar();
                break;
            case 12:
                if(!ListTrabverse(&List[N])) printf("线性表是空表！\n");
                getchar();getchar();
                break;
            case 0:
                break;
            case 13:
                if(Writefile(&List[N])==OK) printf("写入成功\n");
                else printf("写入失败\n");
                getchar();getchar();
                break;
            case 14:
                if(Readfile(&List[N])==OK) printf("读取成功\n");
                else printf("读取失败\n");
                getchar();getchar();
                break;
            case 15:
                if(Changelist(&N)==OK) printf("切换成功，此时链表编号为%d\n",N);
                else printf("输入不合法\n");
                break;
        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n");
}//end of main()
/*--------page 23 on textbook --------------------*/
status InitList(Lnode *L){//创建链表
    Lnode s;
    s=(Node *)malloc(sizeof(Node));
    s->data = 0;
    s->next = NULL;
    *L=s;
    return OK;
}
status DestroyList(Lnode *L){//销毁链表
    Lnode Lp;
    if((*L)==NULL) return ERROR;
    while((*L)!= NULL)
    {
        Lp = *L;
        (*L) = (*L)->next;
        free(Lp);
    }
    return OK;
}
status ClearList(Lnode *L){//清空链表
    Lnode Lp=NULL, Lq=NULL;
    if ((*L)==NULL) return ERROR;
    Lp =(*L)->next;
    while (Lp!= NULL)
    {
        Lq = Lp;
        Lp = Lp->next;
        free(Lq);
    }
    (*L)->data = 0;
    (*L)->next=NULL;
    return OK;
}
status ListEmpty(Lnode *L){//判断是否为空表
    if ((*L)==NULL) return -1;
    if((*L)->data==0)
        return TRUE;
    else return FALSE;
}
status ListLength(Lnode *L){//求表长
    if((*L)==NULL) return -1;
    if((*L)->data==0)
        return ERROR;
    else return (*L)->data;
}
status GetElem(Lnode *L,int i,ElemType *e){//获取元素
    if (i<1 || i>(*L)->data) return -2;
    if((*L)==NULL) return -1;
    Lnode Lp;
    Lp = *L;
    int k;
    for (k = 0; k < i; k++)
    {
        Lp = Lp->next;
    }
    *e = Lp->data;
    return OK;
}
status LocateElem(Lnode *L,ElemType e){//通过compare函数定位元素的位置
    Lnode Lp;
    if ((*L)==NULL) return -1;
    int k=(*L)->data;
    int i;
    Lp=(*L)->next;
    for(i=1;i<=k;i++){
        if(compare(Lp->data,e)==OK) return i;
        Lp=Lp->next;
    }
    return ERROR;
}
status PriorElem(Lnode *L,ElemType cur_e,ElemType *pre_e){//查找前驱
    if((*L)->data==0||(*L)->data==1) return 0;
    Lnode Lp,Lq;
    Lp=(*L)->next->next;
    Lq=(*L)->next;
    while(Lp!=NULL){
        if(Lp->data==cur_e){
            *pre_e=Lq->data;
            return OK;
        }
        Lp=Lp->next;
        Lq=Lq->next;
    }
    return ERROR;
}
status NextElem(Lnode *L,ElemType cur_e,ElemType *next_e){//查找后继
    if((*L)->data==0||(*L)->data==1) return 0;
    Lnode Lp,Lq;
    Lp=(*L)->next;
    Lq=(*L)->next->next;
    while(Lq!=NULL){
        if(Lp->data==cur_e){
            *next_e=Lq->data;
            return OK;
        }
        Lp=Lp->next;
        Lq=Lq->next;
    }
    return ERROR;
}
status ListInsert(Lnode *L,int i,ElemType e){//将元素插入到指定位置
    if((*L)==NULL) return -1;
    if (i<1 ||i>(*L)->data + 1) return ERROR;
    Lnode p = *L,q = NULL,newNode;
    newNode = (Lnode)malloc(2*sizeof(Lnode));
    newNode->data= e;
    int k=0;
    while (k<i)
    {
        q = p;
        p = p->next;
        k++;
    }
    q->next = newNode;
    newNode->next = p;
    (*L)->data+=1;
    return OK;
}
status ListDelete(Lnode *L,int i,ElemType *e){//删除链表中元素，并返回该值
    if (i<1 || i>(*L)->data) return ERROR;
    Lnode p = *L, q;
    int k = 0;
    while (p!=NULL&&k<i-1)
    {
        p = p->next;
        k++;
    }
    q = p->next;
    p->next = q->next;
    *e=q->data;
    free(q);
    (*L)->data-=1;
    return OK;
}
status ListTrabverse(Lnode *L){//将链表元素输出
    Lnode p;
    if((*L)->data==0) return ERROR;
    p=(*L)->next;
    printf("\n-----------all elements -----------------------\n");
    while(p!=NULL){
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n-----------end --------------------------------\n");
    return OK;
}
status Writefile(Lnode *L){//将链表中的元素写入到文件
    Lnode p;
    p=(*L)->next;
    FILE  *fp;char filename[30];
    printf("input file name: ");
    scanf("%s",filename);
    //写文件的方法
    if ((fp=fopen(filename,"wb"))==NULL)
    {
        printf("File open error\n ");
        return ERROR;
    }
    while(p!=NULL){
        fprintf(fp,"%d ",p->data);
        p=p->next;
    }//fwrite针对二进制
    //这里是1次性写入，对于其它物理结构，可通过遍历，逐个访问数据元素
    //并写入到文件中。也可以先写入表长，再写入全部元素，这样读入会更方便
    fclose(fp);
    return OK;
}
status Readfile(Lnode *L){//将文件中中的元素写入链表
    ClearList(L);
    if((*L)==NULL) return -1;
    (*L)->data = 0;
    Lnode p = *L;
    FILE  *fp;char filename[30];
    printf("input file name: ");
    scanf("%s",filename);
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        printf("File open error\n ");
        return ERROR;
    }
    while (!feof(fp))
    {
        p->next = (Lnode)malloc(sizeof(Lnode));
        p=p->next;
        fscanf(fp,"%d",&(p->data));
        (*L)->data++;
    }
    p->next = NULL;
    fclose(fp);
    return OK;
}
status Changelist(int *N){//切换链表
    int k;
    printf("请输入要操作的链表编号：");
    scanf("%d",&k);
    if(k<0||k>99) return ERROR;
    *N=k;
    return OK;
}
status compare(int i,ElemType e){//比较函数
    if(i==e) return OK;
    else return ERROR;
}
