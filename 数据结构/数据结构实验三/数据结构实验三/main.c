//
//  main.c
//  数据结构实验三
//
//  Created by 黄俊淇的Mac on 2019/11/17.
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
#define MAXSIZE 100
#define MAXLENG 100
#define QMAXSIZE 100

typedef int status;

typedef struct BiTnode{
    char name;
    struct BiTnode *lchild,*rchild;
    status data;
}BiTnode,*BiTree;//二叉树定义，name是关键字，data存放节点数据
typedef BiTree QElemType;
typedef struct
{
    QElemType *base;
    int front; // 头指针,若队列不空,指向队列头元素
    int rear; //尾指针,若队列不空,指向队列尾元素的下一个位置
}SqQueue;

status PreCreate(BiTree *T) {
    //按先序次序输入二叉树中结点的值（一个字母），'#'字符表示空树，
    //采用递归调用的方式构造二叉树链表表示的二叉树为T
    char ch;
    printf("请输入关键字：\n");
    scanf("%c", &ch);
    getchar();
    if (ch == '#') {
        *T = NULL;
        return ERROR;
    }
    else {
        if (!((*T) = (BiTnode*)malloc(sizeof(BiTnode)))) exit(OVERFLOW);
        (*T)->name = ch;
        printf("请输入结点值：\n");
        scanf("%d",&((*T)->data));
        getchar();
        PreCreate(&(*T)->lchild);
        PreCreate(&(*T)->rchild);
        return OK;
    }
    
}

void CreateBiTree(BiTree *T,int definition){
    if(definition==1)
        PreCreate(T);
}
status DestroyBiTree(BiTree *T) {
    if (*T) {
        if ((*T)->lchild)
            DestroyBiTree(&((*T)->lchild));
        if ((*T)->rchild)
            DestroyBiTree(&((*T)->rchild));
        free(*T);
        *T = NULL;
    }
    return OK;
}//采用递归的方式销毁二叉树，思想和前序遍历二叉树是一致的
status ClearBiTree(BiTree *T) {
    if (*T) {
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
        return OK;
    }
    else return ERROR;
}//清空保留根节点
status BinTreeEmpty(BiTree *T)
{
    if(*T == NULL)//空树是指根为空
        return TRUE;
    else
        return FALSE;
}
status BiTreeDepth(BiTree *T){
    int depthL;              // 左子树深度
    int depthR;              // 右子树深度
    if((*T)==NULL) return ERROR;
    if ((*T)->lchild==NULL&&(*T)->rchild==NULL)
        return 1;
    depthL = BiTreeDepth(&(*T)->lchild);
    depthR = BiTreeDepth(&(*T)->rchild);
    if (depthL > depthR)
        return 1 + depthL;
    else
        return 1 + depthR;
}
BiTree LocateNode(BiTree *T,char e){
    BiTree p,st[100];
    int top=0;
    st[top++]=*T;
    while(top){
        p=st[--top];
        if(p->name==e) return p;
        else{
            if(p->rchild!=NULL)
                st[top++] = p->rchild;
            if(p->lchild!=NULL)
                st[top++] = p->lchild;
        }
    }
    return NULL;
}
status Assign(BiTree *T,char e,int *value){
    BiTree p;
    p=LocateNode(T,e);
    if(p!=NULL){
        p->data=*value;
        return OK;
    }
    else return ERROR;
}
BiTree LeftSibling(BiTree T, char e) {
    //若e无左孩子，返回NULL
    BiTree T1=NULL;
    if (T) {
        if (T->rchild!=NULL&&T->rchild->name == e) return T->lchild;
        T1 = LeftSibling(T->lchild, e);  //递归调用对左子树进行操作
        if (T1 != NULL) return T1;
        T1 = LeftSibling(T->rchild, e);  //递归调用对右子树进行操作
        if (T1 != NULL) return T1;
    }
    return NULL;
}
BiTree RightSibling(BiTree T, char e) {
    //若e无右孩子，返回NULL
    BiTree T1 = NULL;
    if (T) {
        if (T->lchild!=NULL&&T->lchild->name== e) return T->rchild;
        T1 = RightSibling(T->lchild, e);  //递归调用对左子树进行操作
        if (T1 != NULL) return T1;
        T1 = RightSibling(T->rchild, e);  //递归调用对右子树进行操作
        if (T1 != NULL) return T1;
    }
    return NULL;
}
status InsertChild(BiTree *T, char e, int LR, BiTree c) {
    BiTree p = NULL;
    p=LocateNode(T,e);
    if (!(*T)||!p)
        return -1;

    if (LR == 0) {
        c->rchild=p->lchild;
       
        p->lchild = c;
    }//若LR为0，插入c为T中p所指结点的左子树
    else {
        c->rchild = p->rchild;
        p->rchild = c;
    }//若LR为1，插入c为T中p所指结点的右子树
    return OK;
}
BiTree Parent(BiTree T, char e) {
    //若e是T的非根结点，返回它的双亲结点指针
    //否则返回NULL
    BiTree T1;
    if (T) {
        if ((T->lchild!=NULL&&T->lchild->name == e) ||(T->rchild!=NULL&& T->rchild->name == e)) return T;
        T1 = Parent(T->lchild, e);
        if (T1 != NULL) return T1;
        T1 = Parent(T->rchild, e);
        if (T1 != NULL) return T1;
    }
    return NULL;
}
status DeleteNode(BiTree *T,char e){
    BiTree p,q,r;
    p=LocateNode(T,e);
    q=Parent(*T,e);
    if(*T==NULL) return ERROR;
    if(p==NULL) return ERROR;
    if(p->lchild==NULL&&p->rchild==NULL){
        if(q->lchild==p) q->lchild=NULL;
        if(q->rchild==p) q->rchild=NULL;
        free(p);
    }
    if((p->lchild!=NULL&&p->rchild==NULL)){
        if(q->lchild==p) q->lchild=p->lchild;
        
        free(p);
    }
    if(p->lchild==NULL&&p->rchild!=NULL){
        if(q->rchild==p) q->rchild=p->rchild;
        free(p);
    }
    if(p->lchild!=NULL&&p->rchild!=NULL){
        if(q==NULL){
            (*T)->lchild->rchild=(*T)->rchild;
            (*T)=(*T)->lchild;
        }
        else if(q->lchild==p) {
            r=p->lchild;
            while(r->rchild!=NULL)
            {
                r=r->rchild;
            }
            r->rchild=p->rchild;
            q->lchild=p->lchild;
        }
        else if(q->rchild==p) {
            q->rchild=p->lchild;
            q->rchild->rchild=p->rchild;
        }
        free(p);
    }
    return OK;
}
status Visit(BiTree T){
    if(T==NULL) return ERROR;
    printf("结点关键字：%c  ",T->name);
    printf("存放数据为:%d   ",T->data);
    return OK;
}
status Pre_order(BiTree T, status (*Visit)(BiTree T)) {
    if (T) {
        if (Visit(T))
            if (Pre_order(T->lchild, Visit))
                if (Pre_order(T->rchild, Visit)) return OK;
        return ERROR;
    }
    else return OK;
}

status Mid_order(BiTree T, status(*Visit)(BiTree T)) {
    if (T) {
        if (Mid_order(T->lchild, Visit))
            if (Visit(T))
                if (Mid_order(T->rchild, Visit)) return OK;
        return ERROR;
    }
    else return OK;
}

status Post_order(BiTree T, status(*Visit)(BiTree T)) {
    if (T) {
        if (Post_order(T->lchild, Visit))
            if (Post_order(T->rchild, Visit))
                if (Visit(T)) return OK;
        return ERROR;
    }
    else return OK;
}

//遍历二叉树的非递归算法,建立递归工作栈
status Pre_order_b(BiTree T, status(*Visit)(BiTree T)) {
    BiTree st[MAXSIZE];
    BiTree p;
    int top = 0; //置空栈
    if (T) {
        st[top++] = T;
        while (top)
        {
            p = st[--top]; //弹出栈顶指针
            if(!Visit(p)) return ERROR;
            if (p->rchild != NULL) st[top++] = p->rchild; //将右子树的根结点存入栈中
            if (p->lchild != NULL) st[top++] = p->lchild; //将左子树的根结点存入栈中
        }
        
    }
    return OK;
}//先序遍历的另一种算法思想是直接
//在第一次访问根结点时对根结点进行操作

status Mid_order_b(BiTree T, status(*Visit)(BiTree T)) {
    BiTree st[MAXLENG];  //定义指针栈，并假设二叉树的深度不超过10
    int top = 0;         //置空栈,top为栈顶元素上一个单元的地址
    do {
        while (T)    //根指针T表示的为非空二叉树
        {
            if (top == MAXLENG) exit(OVERFLOW);
            st[top++] = T; //根指针进栈
            T = T->lchild; //T移向左子树
        } //循环结束表示以栈顶元素的指向为
        //根结点的二叉树的左子树遍历结束
        if (top) //为非空栈
        {
            T = st[--top];  //弹出根指针
            if(!Visit(T)) return ERROR; //对根结点进行操作
            T = T->rchild;
        }
    } while (top || T); //父结点未访问或者右子树未遍历
    return OK;
}

//用一个堆栈并设置标志来实现后续非递归遍历
status Post_order_b(BiTree T, status(*Visit)(BiTree T)) {
    BiTnode *st[MAXLENG], *pre;
    int flag, top = 0;
    if (T) {
        do {
            while (T) {
                if (top == MAXLENG) exit(OVERFLOW);
                st[top++] = T;
                T = T->lchild;
            }//循环结束时表示以栈顶元素为指向的
            //根节点的二叉树的左子树遍历完毕
            pre = NULL;
            flag = 1;//设置标志位，用于结束内层循环
            while (top&&flag)
            {
                T = st[top - 1]; //访问左子树根结点
                if (T->rchild == pre) {
                    if (!Visit(T)) return ERROR;
                    top--;//弹出已访问的根结点
                    pre = T;
                }
                else
                {
                    T = T->rchild;
                    flag = 0;//用于跳出内层循环
                }
            }
        } while (top);
    }
    return OK;
}
status InitQueue(SqQueue *Q)
{
    Q->base = (QElemType *)malloc(QMAXSIZE*sizeof(QElemType));
    if (!Q->base) /* 存储分配失败 */
        exit(OVERFLOW);
    Q->front = Q->rear = 0;
    return OK;
}

status QueueEmpty(SqQueue Q){ /* 若队列Q为空队列,则返回TRUE,否则返回FALSE */
    if (Q.front == Q.rear) /* 队列空的标志 */
        return TRUE;
    else
        return FALSE;
}

status EnQueue(SqQueue *Q, QElemType e){ /* 插入元素e为Q的新的队尾元素 */
    if ((Q->rear + 1) % QMAXSIZE == Q->front) /* 队列满 */
        return ERROR;
    Q->base[Q->rear] = e;
    Q->rear = (Q->rear + 1) % QMAXSIZE;
    return OK;
}

status DeQueue(SqQueue *Q, QElemType *e)
{ /* 若队列不空,则删除Q的队头元素,用e返回其值,并返回OK;否则返回ERROR */
    if (Q->front == Q->rear) /* 队列空 */
        return ERROR;
    *e = Q->base[Q->front];
    Q->front = (Q->front + 1) % QMAXSIZE;
    return OK;
}

status LevelOrderTraverse(BiTree T, status(*Visit)(BiTree T)){
    //采用二叉链表存储结构，Visit是对数据元素操作的应用函数
    //层序遍历二叉树T算法(利用队列)，对每个数据元素调用函数Visit
    SqQueue Q;
    BiTree P=T;
    InitQueue(&Q);// 初始化队列
    if (T) EnQueue(&Q, T);
    while (Q.front != Q.rear)
    {
        DeQueue(&Q, &P);
        Visit(P);
        printf("\n");
        if (P->lchild) EnQueue(&Q, P->lchild); // 若存在左孩子，左孩子进队列
        if (P->rchild) EnQueue(&Q, P->rchild); // 若存在右孩子，右孩子进队列
    }
    return OK;
}
status Writefile(BiTree T){//将链表中的元素写入到文件
    FILE  *fp;char filename[30];
    printf("input file name: ");
    scanf("%s",filename);
    //写文件的方法
    if ((fp=fopen(filename,"wb"))==NULL)
    {
        printf("File open error\n ");
        return ERROR;
    }
    BiTree st[1000];
    int rear=0,front=0,q;
    st[rear++]=T;
    while(rear!=front)
    {
        q=rear-1;
        fprintf(fp,"%c: ",st[front]->name);
        fprintf(fp,"%d ",st[front++]->data);
        if(st[q]->lchild!=NULL) {
            st[rear]=st[q]->lchild;
            rear++;
        }
        if(st[q]->rchild!=NULL) {
            st[rear]=st[q]->rchild;
            rear++;
        }
    }
//fwrite针对二进制
    //这里是1次性写入，对于其它物理结构，可通过遍历，逐个访问数据元素
    //并写入到文件中。也可以先写入表长，再写入全部元素，这样读入会更方便
    fclose(fp);
    return OK;
}
status Readfile(BiTree *T){
    FILE  *fp;char filename[30];
    printf("input file name: ");
    scanf("%s",filename);
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        printf("File open error\n ");
        return ERROR;
    }
    char name;
    int data;
    while(!feof(fp)){
        name=fscanf(fp,"%c",&name);
        if(name=='#') break;
        else{
            *T=(BiTree)malloc(sizeof(BiTree));
            (*T)->name=name;
            data=fscanf(fp,"%d",&data);
        }
    }
    return OK;
}
status Changetree(int *N){//切换
    int k;
    printf("请输入要操作的二叉树编号：");
    scanf("%d",&k);
    if(k<0||k>99) return ERROR;
    *N=k;
    return OK;
}
int main(void) {
    BiTree T[100];
    BiTree c;
    int op = 1;
    int LR=0,value=0;
    int N;
    char e;
    printf("请输入0～99来确定要进行操作的树\n");
    scanf("%d",&N);
    while (op) {
        system("cls");    printf("\n\n");
        printf("      Menu for Binary Tree on chain structure!\n");
        printf("-------------------------------------------------\n");
        printf("          1. CreateBiTree      12.MidOrder\n");
        printf("          2. DestroyBiTree     13.PostOrder \n");
        printf("          3. ClearBiTree       14.LevelOrder \n");
        printf("          4. BiTreeEmpty       15.Writefile \n");
        printf("          5. BiTreeDepth       16. Readfile\n");
        printf("          6. LocateNode        17. Changetree\n");
        printf("          7. Assign               \n");
        printf("          8. Brother             \n");
        printf("          9. InsertChild             \n");
        printf("          10.DeleteNode                               \n");
        printf("          11.PreOrder                             \n");
        printf("          0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~17]:");
        scanf("%d", &op);
        switch (op) {
            case 1:getchar();
                if (PreCreate(&T[N]) == OK) printf("树初始化成功！\n");
                else printf("创建失败\n");
                getchar(); getchar();
                break;
            case 2:getchar();
                if(T[N]==NULL) printf("不存在可执行二叉树");
                else if (DestroyBiTree(&T[N]) == OK) printf("树销毁成功！\n");
                getchar(); getchar();
                break;
            case 3:    getchar();
                if(T[N]==NULL) printf("不存在可执行二叉树");
                else if(ClearBiTree(&T[N])==OK) printf("清空成功");
                else printf("清空失败");
                getchar(); getchar();
                break;
            case 4:getchar();
                if(T[N]==NULL) printf("不存在可执行二叉树");
                else if(BinTreeEmpty(&T[N])==TRUE) printf("是空树");
                else printf("不是空树");
                getchar(); getchar();
                break;
            case 5:getchar();
                if(BiTreeDepth(&T[N])==ERROR) printf("不存在可执行二叉树");
                else printf("深度为%d",BiTreeDepth(&T[N]));
                getchar(); getchar();
                break;
            case 6:getchar();
                if(T[N]==NULL) printf("不存在可执行二叉树");
                else{
                printf("输入要查找的关键字：");
                scanf("%c",&e);
                if(LocateNode(&T[N],e)==NULL) printf("不存在关键字为%c的节点",e);
                else printf("成功找到该节点,存储的数据为%d",LocateNode(&T[N],e)->data);
                }
                getchar(); getchar();
                break;
            case 7:getchar();
                if(T[N]==NULL) printf("不存在可执行二叉树");
                else{
                printf("请输入要查找的关键字：");
                scanf("%c",&e);
                printf("请输入value的值：");
                scanf("%d",&value);
                if(Assign(&T[N],e,&value)==OK) printf("查找成功");
                else printf("不存在关键字为%c的节点",e);
                }
                getchar(); getchar();
                break;
            case 8:getchar();
                if(T[N]==NULL) printf("不存在可执行二叉树");
                else{
                printf("请输入要查找的关键字：");
                scanf("%c",&e);
                if(LeftSibling(T[N],e)!=NULL) printf("成功找到左兄弟,其关键字为%c\n",Parent(T[N],e)->lchild->name);
                else if(RightSibling(T[N],e)!=NULL) printf("成功找到右兄弟,,其关键字为%c\n",Parent(T[N],e)->rchild->name);
                else printf("该节点无兄弟");
                }
                getchar(); getchar();
                break;
            case 9:getchar();
                if(T[N]==NULL) printf("不存在可执行二叉树");
                else{
                c=(BiTnode*)malloc(sizeof(BiTnode));
                printf("输入节点c的关键字：\n");
                scanf("%c",&(*c).name);
                printf("输入节点要存放的数据：\n");
                scanf("%d",&(*c).data);
                printf("输入要查找的关键字:\n");
                getchar();
                scanf("%c",&e);
                printf("输入LR：\n");
                scanf("%d",&LR);
                c->lchild=NULL;
                c->rchild=NULL;
                if(InsertChild(&T[N],e,LR,c)==OK) printf("已插入该节点");
                else printf("不存在关键字为%c的结点\n",e);
                }
                getchar(); getchar();
                break;
            case 10:getchar();
                if(T[N]==NULL) printf("不存在可执行二叉树");
                else{
                printf("请输入要查找的关键字：");
                scanf("%c",&e);
                if(DeleteNode(&T[N],e)==ERROR) printf("不存在该节点");
                else printf("已删除该节点");
                }
                getchar(); getchar();
                break;
            case 11:getchar();
                if(T[N]==NULL) {
                    printf("不存在可执行二叉树");
                    getchar(); getchar();
                    break;}
                if(Pre_order_b(T[N],Visit)==OK) printf("\n前序遍历成功");
                getchar(); getchar();
                break;
            case 12:getchar();
                if(T[N]==NULL) {
                    printf("不存在可执行二叉树");
                    getchar(); getchar();
                    break;}
                if(Mid_order(T[N],Visit)==OK) printf("\n中序遍历成功");
                getchar(); getchar();
                break;
            case 13:getchar();
                if(T[N]==NULL) {
                    printf("不存在可执行二叉树");
                    getchar(); getchar();
                    break;}
                if(Post_order(T[N],Visit)==OK) printf("\n后序遍历成功");
                getchar(); getchar();
                break;
            case 14:getchar();
                if(T[N]==NULL) printf("不存在可执行二叉树");
                if(LevelOrderTraverse(T[N],Visit)==ERROR) printf("遍历失败");
                else printf("遍历成功");
                getchar(); getchar();
                break;
            case 15:getchar();
                if(Writefile(T[N])==OK) printf("写入成功\n");
                else printf("写入失败\n");
                getchar();getchar();
                break;
            case 16:getchar();
                if(Readfile(&T[N])==OK) printf("写入成功\n");
                else printf("写入失败\n");
                getchar();getchar();
                break;
            case 17:getchar();
                if(Changetree(&N)==OK) printf("切换成功，此时二叉树编号为%d\n",N);
                else printf("输入不合法\n");
                getchar();getchar();
                break;
            case 0:
                break;
        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n");
    return 0;
}//end of main()

