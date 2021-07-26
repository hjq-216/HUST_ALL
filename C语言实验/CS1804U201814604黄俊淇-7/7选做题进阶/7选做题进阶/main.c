//
//  main.c
//  7选做题进阶
//
//  Created by 黄俊淇 on 2018/12/23.
//  Copyright © 2018 黄俊淇. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct score
{
    char name[20];
    int number;
    float English;
    float Physic;
    float Math;
    float Clanguage;
    float average;
    struct score *next;
};
void output(struct score*headp);
void change(struct score *head);
void output2(struct score*head);
void sort(struct score *head);
int main()
{
    struct score * head=NULL,*tail;
    int i;
    
    printf("please input 3 students you want\n");
    
    head=(struct score*)malloc(sizeof(struct score));
    scanf("%s",head->name);
    scanf("%d",&head->number);
    scanf("%f",&head->English);
    scanf("%f",&head->Physic);
    scanf("%f",&head->Math);
    scanf("%f",&head->Clanguage);
    tail=head;
    for(i=1;i<3;i++)
    {
        
        tail->next=(struct score*)malloc(sizeof(struct score));
        tail=tail->next;
        scanf("%s",tail->name);
        scanf("%d",&tail->number);
        scanf("%f",&tail->English);
        scanf("%f",&tail->Physic);
        scanf("%f",&tail->Math);
        scanf("%f",&tail->Clanguage);
    }
    tail->next=NULL;
    change(head);
    
    output(head);
    output2(head);
    sort(head);
    return 0;
}

void output(struct score*head)
{
    struct score *p=head;
    while(p)
    {
        printf("%s\n",p->name);
        printf("%d\n",p->number);
        printf("%f\n",p->English);
        printf("%f\n",p->Physic);
        printf("%f\n",p->Math);
        printf("%f\n",p->Clanguage);
        p=p->next;
    }
}

void change(struct score *head)
{
    int n,i=1;
    struct score *p=head;
    while(i<=3)
    {
        printf("please input a number to choose the data you want to change\n");
        printf("1:name\n");
        printf("2:number\n");
        printf("3:English score\n");
        printf("4:Physic score\n");
        printf("5:Math score\n");
        printf("6:Clanguage score\n");
        printf("7:no change!\n");
        scanf("%d",&n);
        switch(n)
        {
            case 1:scanf("%s",p->name);
                break;
            case 2:scanf("%d",&p->number);
                break;
            case 3:scanf("%f",&p->English);
                break;
            case 4:scanf("%f",&p->Physic);
                break;
            case 5:scanf("%f",&p->Math);
                break;
            case 6:scanf("%f",&p->Clanguage);
                break;
            default:break;
        }
        p=p->next;
        i++;
    }
}

void output2(struct score*head)
{
    struct score*p=head;
    int i=1;
    while(i<=3)
    {
        printf("sum is %f\n",(p->Clanguage+p->English+p->Math+p->Physic));
        printf("average is %f\n",(p->Clanguage+p->English+p->Math+p->Physic)/4);
        p=p->next;
        i++;
    }
}

void sort(struct score *head)
{
    int i,j;
    struct score *p=head,*k[3],*temp=NULL;
    for(i=0;i<3;i++)
    {
        p->average=(p->Clanguage+p->English+p->Math+p->Physic)/4;
        k[i]=p;
        p=p->next;
    }
    
    for(i=0;i<3;i++)
        for(j=0;j<2;j++)
        {
            if((k[j]->average)>(k[j+1]->average))
            {
                
                k[j]->next=k[j+1]->next;
                k[j+1]->next=k[j];
                temp=k[j];
                k[j]=k[j+1];
                k[j+1]=temp;
            }
        }
    output(k[0]);
}
