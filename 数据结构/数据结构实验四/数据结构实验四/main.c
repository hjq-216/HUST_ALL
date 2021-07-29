//
//  main.c
//  数据结构实验四
//
//  Created by 黄俊淇的Mac on 2019/12/4.
//  Copyright © 2019 黄俊淇的Mac. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20
#define OK 1
#define ERROR -1
#define TRUE 1
#define FALSE 0

typedef struct ArcNode{        //VR
    char adjvex;
    struct ArcNode *nextarc;
}ArcNode;
typedef struct VNode{          //V
    char name;
    int data;
    ArcNode *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct{                //G
    AdjList adjlist;
    int vexnum;
    int arcnum;
}ALGraph;

typedef struct QNode
{
    char data;
    struct QNode *next;
}QNode, *QueuePtr;
typedef struct
{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

void CreateALG(ALGraph * G)
{
    char ch;
    int i = 0, count = 0;
    ArcNode * temp;
    
    printf("请输入图的顶点：");
    while ((ch = getchar()) != '#')/* 建立顶点表 */
    {
        G->adjlist[i].name = ch;
        G->adjlist[i].firstarc = NULL;
        i++;
    }
    G->vexnum = i;/* 顶点数 */
    
    for (i = 0; i < G->vexnum; i++)/* 头插法建立顶点的邻接边表 */
    {
        printf("请输入顶点 %c 的邻接顶点：", G->adjlist[i].name);
        while ((ch = getchar()) != '#')/* 按下回车结束邻接点的创建 */
        {
            temp = (ArcNode *)malloc(sizeof(ArcNode));
            temp->adjvex = ch;
            temp->nextarc = G->adjlist[i].firstarc;
            G->adjlist[i].firstarc= temp;
            count++;
        }
    }
    G->arcnum = count / 2;
    // 无向图中每条边连接两个顶点，故：节点总度数 = 边数 * 2
}
void DestroyALG(ALGraph *G){
    ArcNode *p,*q;
    int i;
    for(i=0;i<G->vexnum;i++)
    {
        p=G->adjlist[i].firstarc;
        while(p!=NULL)
        {
            q=p;
            p=p->nextarc;
            free(q);
        }
    }
    (*G).arcnum=0;
    (*G).vexnum=0;
}
int LocateVex(ALGraph G,char u){
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        if(G.adjlist[i].name==u){
            printf("找到该节点，存储数据为%d",G.adjlist[i].data);
            return OK;
        }
    }
    return ERROR;
}
int PutVex(ALGraph *G,int *value,char u){
    int i=0;
    while(i<G->vexnum)
    {
        if(G->adjlist[i].name==u)
            break;
        else i++;
    }
    if(i==G->vexnum) return ERROR;
    else{
        G->adjlist[i].data=*value;
        return OK;
    }
}
int FirstAdjVex(ALGraph G,int u){
    int i;
    ArcNode* p;
    if(u<0||u>=G.vexnum) return ERROR;
    p=G.adjlist[u].firstarc;
    if(p==NULL) return ERROR;
    for(i=0;i<G.vexnum;i++)
    {
        if(G.adjlist[i].name==p->adjvex) return i;
    }
    return ERROR;
}
int NextAdjVex(ALGraph G,int v,int w){
    ArcNode *p;
    if(v<0||v>=G.vexnum) return ERROR;
    p=G.adjlist[v].firstarc;
    while(p!=NULL)
    {
        if(p->adjvex==G.adjlist[w].name)
            break;
        p=p->nextarc;
    }
    if(p==NULL) return ERROR;
    p=p->nextarc;
    if(p==NULL) return ERROR;
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        if(G.adjlist[i].name==p->adjvex) return i;
    }
    return ERROR;
}
void InsertVex(ALGraph *G,char v){
    (*G).adjlist[(*G).vexnum].name=v;
    (*G).adjlist[(*G).vexnum].firstarc=NULL;
    (*G).vexnum++;
}
int DeleteVex(ALGraph *G,char v){
    int i=0;
    int j;
    int k;
    int count=0;
    ArcNode *p,*q;
    while(i<G->vexnum)
    {
        if(G->adjlist[i].name==v)
            break;
        else i++;
    }
    if(i==G->vexnum) return ERROR;
    p=G->adjlist[i].firstarc;
    while(p!=NULL)//free邻接点
    {
        q=p;
        p=p->nextarc;
        free(q);
    }
    for(k=i;k<G->vexnum;k++)
    {
        G->adjlist[k]=G->adjlist[k+1];
    }
    G->vexnum--;
    G->arcnum=G->arcnum-2*count;
    for(j=0;(j<G->vexnum);j++)//free（w,v)
    {
        p=G->adjlist[j].firstarc;
        if(p==NULL) continue;
        if(p->adjvex==v)
        {
            G->adjlist[j].firstarc=p->nextarc;
            free(p);
            continue;
        }
        else{
        q=G->adjlist[j].firstarc;
        while(p->adjvex!=v)
        {
            p=p->nextarc;
            if(p==NULL) break;
        }
            if(p==NULL) continue;
        while(q->nextarc!=p)
        {
            q=q->nextarc;
            if(q==NULL) break;
        }
        q->nextarc=p->nextarc;
        free(p);
        }
        count++;
    }

    return OK;
}
int InsertArc(ALGraph *G,char v,char w){
    ArcNode *p,*q;
    int i,j;
    for(i=0;i<G->vexnum;i++)
    {
        if(G->adjlist[i].name==v) break;
    }
    if(i==G->vexnum) return ERROR;
    p=(ArcNode *)malloc(sizeof(ArcNode));
    p->adjvex=w;
    p->nextarc=G->adjlist[i].firstarc;
    G->adjlist[i].firstarc=p;
    for(i=0;i<G->vexnum;i++)
    {
        if(G->adjlist[i].name==w) break;
    }
    if(i==G->vexnum) return ERROR;
    q=(ArcNode *)malloc(sizeof(ArcNode));
    q->adjvex=v;
    q->nextarc=G->adjlist[i].firstarc;
    G->adjlist[i].firstarc=q;
    (*G).arcnum+=2;
    return OK;
}
int DeleteArc(ALGraph *G,char v,char w){
    ArcNode *p,*q,*r;
    int i,j;
    for(i=0;i<G->vexnum;i++)
    {
        if(G->adjlist[i].name==v) break;
    }
    if(i==G->vexnum) return ERROR;
    for(j=0;j<G->vexnum;j++)
    {
        if(G->adjlist[j].name==w) break;
    }
    if(j==G->vexnum) return ERROR;
    p=G->adjlist[i].firstarc;
    if(p==NULL) return ERROR;
    if(p->adjvex==w){
        free(p);
        G->adjlist[i].firstarc=NULL;
    }
    else{
        while((p->adjvex!=w))
        {
            p=p->nextarc;
            if(p==NULL) break;
        }
        if(p==NULL) return ERROR;
        r=G->adjlist[i].firstarc;
        while(r->nextarc!=p)
        {
            r=r->nextarc;
        }
        r->nextarc=p->nextarc;
        free(p);
    }
    q=G->adjlist[j].firstarc;
    if(q==NULL) return ERROR;
    if(q->adjvex==v){
        free(q);
        G->adjlist[j].firstarc=NULL;
    }
    else{
        while((q->adjvex!=v))
        {
            q=q->nextarc;
            if(q==NULL) break;
        }
        if(q==NULL) return ERROR;
        r=G->adjlist[j].firstarc;
        while(r->nextarc!=q)
        {
            r=r->nextarc;
            if(r==NULL) break;
        }
        r->nextarc=q->nextarc;
        free(q);
    }
    (*G).arcnum-=2;
    return OK;
}
int visited[MAX_VERTEX_NUM];
void DFS(ALGraph G,int v){
    int w;
    visited[v]=TRUE;
    printf("%c\n",G.adjlist[v].name);
    for(w=FirstAdjVex(G,v);w>=0;w=NextAdjVex(G,v,w))
        if(!visited[w]) DFS(G,w);
}
void DFSTraverse(ALGraph G){
    int v;
    for(v=0;v<G.vexnum;v++) visited[v]=0;
    for(v=0;v<G.vexnum;v++)
    {
        if(!visited[v])
            DFS(G,v);
    }
}
int InitQueue(LinkQueue *Q)
{ /* 构造一空的队列Q */
    Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
    if (!Q->front)
        exit(-1);
    Q->front->next = NULL;
    return OK;
}

int QueueEmpty(LinkQueue Q)
{ /* 若Q为空,返回TRUE,不空则返回FALSE */
    if (Q.front == Q.rear)
        return TRUE;
    else
        return FALSE;
}

int EnQueue(LinkQueue *Q, int e)
{ /* 插入元素e为Q的新的队尾元素 */
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    if (!p) /* 存储分配失败 */
        exit(-1);
    p->data = e;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    return OK;
}

int DeQueue(LinkQueue *Q,int *e)
{ /* 若队列不空,删除Q的队头元素,用e返回其值,并返回OK,否则返回ERROR */
    QueuePtr p;
    if (Q->front == Q->rear)
        return ERROR;
    p = Q->front->next;
    *e = p->data;
    Q->front->next = p->next;
    if (Q->rear == p)
        Q->rear = Q->front;
    free(p);
    return OK;
}

void BFSTraverse(ALGraph G, LinkQueue Q)
{
    int v, u;
    int count = 0;
    int w;
    for (v = 0; v < G.vexnum; v++)
    {
        visited[v] = 0;
    }
    for (v = 0; v < G.vexnum; v++)
    {
        if (!visited[v])
        {
            visited[v] = TRUE;
            printf("\t第%d个结点为:%c\n", v + 1, G.adjlist[v].name);
            EnQueue(&Q, v);
            while (!QueueEmpty(Q))
            {
                DeQueue(&Q, &u);
                for (w=FirstAdjVex(G,u);w>=0;w=NextAdjVex(G,u,w)) {
                    if (visited[w] != 1) {
                        visited[w] = TRUE;
                        printf("\t第%d个结点为:%c\n", ++count, G.adjlist[w].name);
                        EnQueue(&Q, w);
                    }
                }
            }
        }
    }
}
int ChangeG(int *N){//切换
    int k;
    printf("请输入要操作的图编号：");
    scanf("%d",&k);
    if(k<0||k>99) return ERROR;
    *N=k;
    return OK;
}
int Writefile(ALGraph *G){//将链表中的元素写入到文件
    FILE  *fp;char filename[30];
    printf("input file name: ");
    scanf("%s",filename);
    //写文件的方法
    if ((fp=fopen(filename,"wb"))==NULL)
    {
        printf("File open error\n ");
        return ERROR;
    }
    int i;
    char c;
    int k;
    for(i=0;i<G->vexnum;i++)
    {
        c=G->adjlist[i].name;
        k=G->adjlist[i].data;
        fprintf(fp,"%c: ",c);
        fprintf(fp,"%d ",k);
    }
    fclose(fp);
    return OK;
}
int Readfile(ALGraph *G){
    FILE  *fp;char filename[30];
    printf("input file name: ");
    scanf("%s",filename);
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        printf("File open error\n ");
        return ERROR;
    }
    char ch;
    int i = 0, count = 0;
    ArcNode * temp;
    while(!feof(fp)){
        fscanf(fp,"%c",&ch);
        while ((ch ) != '#')/* 建立顶点表 */
        {
            
            G->adjlist[i].name = ch;
            G->adjlist[i].firstarc = NULL;
            fscanf(fp,"%c",&ch);
            i++;
        }
        G->vexnum = i;/* 顶点数 */
        
        for (i = 0; i < G->vexnum; i++)/* 头插法建立顶点的邻接边表 */
        {
            fscanf(fp,"%c",&ch);
            while (ch  != '#')/* 按下回车结束邻接点的创建 */
            {
                temp = (ArcNode *)malloc(sizeof(ArcNode));
                temp->adjvex = ch;
                temp->nextarc = G->adjlist[i].firstarc;
                G->adjlist[i].firstarc= temp;
                count++;
                fscanf(fp,"%c",&ch);
            }
        }
        G->arcnum = count / 2;
        // 无向图中每条边连接两个顶点，故：节点总度数 = 边数 * 2
    }
    fclose(fp);
    return OK;
}
int main(void) {
    int op = 1;
    int N;
    ALGraph G[100];
    printf("请输入0～99来确定要进行操作的图\n");
    scanf("%d",&N);
    char u,c;
    int n;
    int value = 0;
    int v,w;
    LinkQueue Q;

    while (op) {
        system("cls");    printf("\n\n");
        printf("      Menu for Binary Tree on chain structure!\n");
        printf("-------------------------------------------------\n");
        printf("          1. CreateALG       8. DeleteVex\n");
        printf("          2. DestroyGraph    9. InsertArc \n");
        printf("          3. LocateVex       10.DeleteArc \n");
        printf("          4. PutVex          11.DFSTraverse\n");
        printf("          5. FirstAdjVex     12.BFSTraverse\n");
        printf("          6. NextAdjVex      13.ChangeG\n");
        printf("          7. InsertVex       14.Writefile       \n");
        printf("          15.Readfile        0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~17]:");
        scanf("%d", &op);
        switch (op) {
            case 1:getchar();
                CreateALG(&G[N]);
                printf("图创建成功！");
                getchar(); getchar();
                break;
            case 2:getchar();
                if(G[N].vexnum==0) {printf("不存在可操作图！"); break;}
                else{
                    DestroyALG(&G[N]);
                    printf("销毁成功");
                }
                getchar(); getchar();
                break;
            case 3:    getchar();
                if(G[N].vexnum==0) {printf("不存在可操作图！"); break;}
                printf("请输入关键字");
                scanf("%c",&u);
                if(LocateVex(G[N],u)==OK) printf("定位成功");
                else printf("不存在关键字为%c的结点",u);
                getchar(); getchar();
                break;
            case 4:getchar();
                if(G[N].vexnum==0) {printf("不存在可操作图！"); break;}
                printf("请输入要赋予的值\n");
                scanf("%d",&value);
                getchar();
                printf("请输入关键字\n");
                scanf("%c",&u);
                if(PutVex(&G[N],&value,u)==OK) printf("赋值成功！");
                else printf("赋值失败！");
                getchar(); getchar();
                break;
            case 5:getchar();
                if(G[N].vexnum==0) {printf("不存在可操作图！"); break;}
                printf("请输入要查找的结点位序：\n");
                scanf("%d",&n);
                if(FirstAdjVex(G[N],n)!=-1) printf("查找成功，第一邻接点的位序为%d",FirstAdjVex(G[N],n));
                else printf("查找失败");
                getchar(); getchar();
                break;
            case 6:getchar();
                if(G[N].vexnum==0) {printf("不存在可操作图！"); break;}
                printf("请输入结点位序：\n");
                scanf("%d",&v);
                getchar();
                printf("请输入上一邻接点位序：\n");
                scanf("%d",&w);
                if(NextAdjVex(G[N],v,w)!=-1) printf("下一邻接点位序为%d",NextAdjVex(G[N],v,w));
                else printf("查找失败");
                getchar(); getchar();
                break;
            case 7:getchar();
                if(G[N].vexnum==0) {printf("不存在可操作图！"); break;}
                printf("请输入结点关键字:\n");
                scanf("%c",&u);
                InsertVex(&G[N],u);
                printf("插入成功");
                getchar(); getchar();
                break;
            case 8:getchar();
                if(G[N].vexnum==0) {printf("不存在可操作图！"); break;}
                printf("请输入关键字：\n");
                scanf("%c",&u);
                if(DeleteVex(&G[N],u)==OK) printf("删除成功");
                else printf("删除失败");
                getchar(); getchar();
                break;
            case 9:getchar();
                if(G[N].vexnum==0) {printf("不存在可操作图！"); break;}
                printf("请输入其中一个结点关键字：\n");
                scanf("%c",&u);
                getchar();
                printf("请输入另一个结点关键字：\n");
                scanf("%c",&c);
                if(InsertArc(&G[N],u,c)==OK) printf("插入成功");
                else printf("插入失败");
                getchar(); getchar();
                break;
            case 10:getchar();
                if(G[N].vexnum==0) {printf("不存在可操作图！"); break;}
                printf("请输入其中一个结点关键字：\n");
                scanf("%c",&u);
                getchar();
                printf("请输入另一个结点关键字：\n");
                scanf("%c",&c);
                if(DeleteArc(&G[N],u,c)==OK) printf("删除成功");
                else printf("删除失败");
                getchar(); getchar();
                break;
            case 11:getchar();
                if(G[N].vexnum==0) {printf("不存在可操作图！"); break;}
                DFSTraverse(G[N]);
                getchar(); getchar();
                break;
            case 12:getchar();
                if(G[N].vexnum==0) {printf("不存在可操作图！"); break;}
                InitQueue(&Q);
                BFSTraverse(G[N],Q);
                getchar(); getchar();
                break;
            case 13:getchar();
                if(ChangeG(&N)==OK) printf("切换成功，此时图编号为%d\n",N);
                else printf("切换失败");
                getchar(); getchar();
                break;
            case 14:getchar();
                if(G[N].vexnum==0) {printf("不存在可操作图！"); break;}
                if(Writefile(&G[N])==OK) printf("写入成功");
                else printf("写入失败");
                getchar(); getchar();
                break;
            case 15:getchar();
                if(Readfile(&G[N])==OK) printf("读取成功");
                else printf("读取失败");
                getchar();getchar();
                break;
            case 0:
                break;
        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n");
    return 0;
}//end of main()

