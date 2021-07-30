#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
using namespace std;
struct STACK {
	int  *elems;	//�����ڴ����ڴ��ջ��Ԫ��
	int   max;	//ջ�ܴ�ŵ����Ԫ�ظ���
	int   pos;	//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
};
void initSTACK(STACK *const p, int m);	//��ʼ��pָ���ջ�����m��Ԫ��
void initSTACK(STACK *const p, const STACK&s); //��ջs��ʼ��pָ���ջ
int  size(const STACK *const p);		//����pָ���ջ�����Ԫ�ظ���max
int  howMany(const STACK *const p);	//����pָ���ջ��ʵ��Ԫ�ظ���pos
int  getelem(const STACK *const p, int x);	//ȡ�±�x����ջԪ��
STACK *const push(STACK *const p, int e); 	//��e��ջ��������p
STACK *const pop(STACK *const p, int &e); 	//��ջ��e��������p
STACK *const assign(STACK*const p, const STACK&s); //��s��pָ��ջ,������p
void print(const STACK*const p);			//��ӡpָ���ջ
void destroySTACK(STACK*const p);		//����pָ���ջ
FILE *fout;
int main(int argc, char *argv[])
{
	struct STACK *p = new STACK;
	struct STACK *s = new STACK;
	int i;
	int e;
	int itemp;
	int init = 0;
	if(!(fout = fopen("U201614795.txt","w")))
	{
		printf("Cannot open file strike any key exit!");
		getchar();
	}
	for(i = 1;i < argc;i++)
	{
		if(!strcmp(argv[i],"-S"))
		{
			printf("S  ");
			fputs("S  ", fout);
			if (init == 1)
			{
				printf("E  ");
				fputs("E  ", fout);
				break;
			}
			if (argv[i + 1][0] >= '0' && argv[i + 1][0] <= '9')
			{
				itemp = atoi(argv[++i]);
				initSTACK(p, itemp);
				fprintf(fout, "%d  ", itemp);
				printf("%d  ", itemp);
				init = 1;
			}
			else {
				printf("E  ");
				fputs("E  ", fout);
				break;
			}
		}
		if(!strcmp(argv[i],"-I"))
		{
			printf("I  ");
			fputs("I  ",fout);
			if (init == 0)
			{
				printf("E  ");
				fputs("E  ", fout);
				exit(0);
			}
			i++;

			for (; (i < argc) && (argv[i][0] >= '0') && (argv[i][0] <= '9'); i++)
			{
				itemp = atoi(argv[i]);
				int stackpos = howMany(p);
				int stackmax = size(p);
				if (stackpos == stackmax)
				{
					printf("E  ");
					fputs("E  ", fout);
					exit(1);
				}
				push(p, itemp);
			}
			print(p);
			i--; //������һ��forѭ�����������ٴμ��-I
		}
		if (i < argc)
		{
			if (!strcmp(argv[i], "-O"))
			{
				fputs("O  ", fout);
				printf("O  ");

				if (init == 0)
				{
					printf("E  ");
					fputs("E  ", fout);
					break;
				}
				if (argv[i + 1][0] >= '0' &&argv[i][0] <= '9')
				{
					itemp = atoi(argv[++i]);
					if (itemp > howMany(p))
					{
						printf("E  ");
						fputs("E  ", fout);
						break;
					}
					int j;
					for (j = 0; j < itemp; j++)
						pop(p, e);
					if (howMany(p))
						print(p);
					i--;
				}
				else
				{
					printf("E  ");
					fputs("E  ", fout);
					break;
				}
			}

			if (!strcmp(argv[i], "-A"))
			{
				fputs("A  ", fout);
				printf("A  ");
				if (argv[i + 1][0] >= '0'&&argv[i][0] <= '9')
				{
					itemp = atoi(argv[++i]);
					initSTACK(s, itemp);
					p=assign(s, *p);
					if (howMany(p)) print(p);
				}
				else
				{
					printf("E  ");
					fputs("E  ", fout);
					break;
				}
			}
			if (!strcmp(argv[i], "-C"))
			{
				fputs("C  ", fout);
				printf("C  ");
				initSTACK(s, *p);
				if (howMany(p)) print(p);
			}
			if (!strcmp(argv[i], "-N"))
			{
				fputs("N  ", fout);
				printf("N  ");
				int N = howMany(p);
				fprintf(fout, "%d  ", N);
				printf("%d  ", N);
			}
			if (!strcmp(argv[i], "-G"))
			{
				fputs("G  ", fout);
				printf("G  ");
				if (argv[i + 1][0] >= '0'&&argv[i + 1][0] <= '9')
				{
					itemp = atoi(argv[i + 1]);
					if (howMany(p) <= itemp)
					{
						fputs("E  ", fout);
						printf("E  ");
						break;
					}
					else
					{
						int N = getelem(p, itemp);
						fprintf(fout, "%d  ", N);
						printf("%d  ", N);
					}
				}
			}

		}
	}
	fclose(fout);
	return 0;
}
void initSTACK(STACK *const p, int m)
{
	p->elems = new int[m];
	if (p->elems) {
		p->max = m;
		p->pos = 0;
	}
	else{
		printf("E  ");
		fputs("E  ",fout);
	}
	
}
void initSTACK(STACK *const p, const STACK&s) //p=assign(s, *p);
{
	int i;
	if (s.elems) {
		p->max = s.max;
		p->pos = s.pos;
		p->elems = new int[p->pos];
		for (i = 0; i < p->pos; i++)
		{
			p->elems[i] = s.elems[i];
		}
	}
}
int  size(const STACK *const p)
{
	return p->max;
}
int  howMany(const STACK *const p)	//����pָ���ջ��ʵ��Ԫ�ظ���pos
{
	return p->pos;
}
int  getelem(const STACK *const p, int x)	//ȡ�±�x����ջԪ��
{
	if (x > p->max)
		exit(0);
	else
		return p->elems[x];
}
STACK *const push(STACK *const p, int e) 	//��e��ջ��������p
{
	if (p->pos < p->max) 
	{
		p->elems[p->pos] = e;
		p->pos++;
	}
	return p;
}
STACK *const pop(STACK *const p, int &e) 	//��ջ��e��������p
{
	if (p->pos > 0) 
	{
		e = p->elems[p->pos - 1];
		p->pos--;
	}
	return p;
}
STACK *const assign(STACK*const p, const STACK&s) //��s��pָ��ջ,������p
{
	int i;
	if (s.elems) {
		delete[]p->elems;
		p->pos = s.pos;
		p->max = s.max;
		p->elems = new int[p->max];
		for (i = 0; i < p->pos; i++)
			p->elems[i] = s.elems[i];
	}
	return p;
}
void print(const STACK*const p)			//��ӡpָ���ջ
{
	int i;
	if (p->pos > 0)
	{
		for (i = 0; i <p->pos; i++) {
			printf("%d  ", p->elems[i]);
			fprintf(fout, "%d  ", p->elems[i]);
		}
	}
}
void destroySTACK(STACK*const p)		//����pָ���ջ
{
	if (p->elems)
	{
		delete[]p->elems;
		p->pos = 0;
		p->max = 0;
	}
}