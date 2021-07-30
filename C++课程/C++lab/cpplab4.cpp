#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
class STACK {
	int  *const  elems;	//申请内存用于存放栈的元素
	const  int   max;	//栈能存放的最大元素个数
	int   pos;			//栈实际已有元素个数，栈空时pos=0;
public:
	STACK(int m);		//初始化栈：最多m个元素
	STACK(const STACK&s); 			//用栈s拷贝初始化栈
	virtual int  size() const;			//返回栈的最大元素个数max
	virtual operator int() const;			//返回栈的实际元素个数pos
	virtual int operator[ ] (int x) const;	//取下标x处的栈元素
	virtual STACK& operator<<(int e); 	//将e入栈,并返回栈
	virtual STACK& operator>>(int &e);	//出栈到e,并返回栈
	virtual STACK& operator=(const STACK&s); //赋s给栈,并返回被赋值的栈
	virtual void print() const;			//打印栈
	virtual ~STACK();					//销毁栈
};

class QUEUE :public STACK {
	STACK  s2;
public:
	QUEUE(int m); //每个栈最多m个元素，要求实现的队列最多能入2m个元素
	QUEUE(const QUEUE&s); 			//用队列s拷贝初始化队列
	virtual operator int() const;			//返回队列的实际元素个数
	virtual int full() const;		       //返回队列是否已满，满返回1，否则返回0
	virtual int operator[ ](int x)const;   //取下标为x的元素，第1个元素下标为0
	virtual QUEUE& operator<<(int e);  //将e入队列,并返回队列
	virtual QUEUE& operator>>(int &e);	//出队列到e,并返回队列
	virtual QUEUE& operator=(const QUEUE&s); //赋s给队列,并返回被赋值的队列
	virtual void print() const;			//打印队列
	virtual ~QUEUE();					//销毁队列
};
using namespace std;
int isPrime(int num); //检查输入的数字是否是素数
FILE *fout;
int main(int argc, char *argv[])
{
	if (!(fout = fopen("U201614795.txt", "w")))
	{
		printf("Cannot open file strike any key exit!");
		getchar();
	}
	if (argc != 1)
	{
		QUEUE *p;
		QUEUE *s;
		int i;
		int e;
		int itemp;
		int init = 0;
		
		for (i = 1; i < argc; i++)
		{
			if (!strcmp(argv[i], "-S"))
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
					p = new QUEUE(itemp);
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
			if (!strcmp(argv[i], "-I"))
			{
				printf("I  ");
				fputs("I  ", fout);

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
					if (p->full())
					{
						printf("E  ");
						fputs("E  ", fout);
						exit(1);
					}
					*p << itemp;
				}

				p->print();
				i--; //进入下一轮for循环，否则不能再次检测-I
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
						if (itemp > *p)
						{
							printf("E  ");
							fputs("E  ", fout);
							break;
						}
						int j;
						for (j = 0; j < itemp; j++) {
							*p >> e;
						}
						if (*p)
							p->print();
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
						s = new QUEUE(itemp);
						*s = *p;
						p = s;
						if (*p) p->print();
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
					s = new QUEUE(*p);
					p = s;
					if (*p) p->print();
				}
				if (!strcmp(argv[i], "-N"))
				{
					fputs("N  ", fout);
					printf("N  ");
					int N = *p;
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
						if (*p <= itemp)
						{
							fputs("E  ", fout);
							printf("E  ");
							break;
						}
						else
						{
							int N = (*p)[itemp];
							fprintf(fout, "%d  ", N);
							printf("%d  ", N);
						}
					}
				}

			}
		}
	}
	else
	{
		int M, F;    //男女两队初始人数
		int index_M, index_F; //某一男士的初始位置，某一女士的初始位置
		cout << "输入男士队列的人数：";
		cin >> M;
		while (!isPrime(M))
		{
			cout << "请重新输入人数：";
			cin >> M;
		}
		cout << "输入女士队列的人数（不能等于男士队列的人数）:";
		cin >> F;
		while (!isPrime(F) && F != M)
		{
			cout << "请重新输入人数：";
			cin >> F;
		}
		cout << "输入男士的初始位置:";
		cin >> index_M;
		while (index_M > M)
		{
			cout << "请重新输入：";
			cin >> index_M;
		}
		cout << "请输入女士的初始位置:";
		cin >> index_F;
		while (index_F > F)
		{
			cout << "请重新输入：";
			cin >> index_F;
		}
		QUEUE *mQueue = new QUEUE(M);
		QUEUE *fQueue = new QUEUE(F);
		for (int i = 1; i <= M; i++)
		{
			if (i != index_M)
				*mQueue << 1;
			else
				*mQueue << 0; //标记第M位男士
		}

		for (int i = 1; i <= F; i++)
		{
			if (i != index_F)
				*fQueue << 1;
			else
				*fQueue << 0; //标记第F位女士
		}

		int m_out = 1, f_out = 1;
		int count = 0;
		while (m_out == 1 || f_out == 1)
		{
			*mQueue >> m_out;
			*mQueue << m_out;
			*fQueue >> f_out;
			*fQueue << f_out;
			count++;
		}
		delete mQueue;
		delete fQueue;
		cout << "在第[" << count << "]支舞曲时，可以共舞";
	}
	fclose(fout);
	return 0;
}
int isPrime(int num)
{
	int i;
	int flag = 1;
	for (i = 2; i < num / 2; i++)
	{
		if (num%i == 0)
		{
			flag = 0;
			break;
		}
	}
	return flag;
}
STACK::STACK(int m)		//初始化栈：最多m个元素
	:elems(new int[m]), max(m), pos(0)
{

}
STACK::STACK(const STACK&s) 			//用栈s拷贝初始化栈
	: elems(new int[s.max]), max(s.max), pos(s.pos)
{
	int i;
	for (i = 0; i < pos; i++)
	{
		elems[i] = s.elems[i];
	}
}
int STACK::size() const			//返回栈的最大元素个数max
{
	return max;
}
STACK::operator int() const			//返回栈的实际元素个数pos
{
	return pos;
}
int STACK::operator[ ] (int x) const	//取下标x处的栈元素
{
	return elems[x];
}
STACK& STACK::operator<<(int e) 	//将e入栈,并返回栈
{
	if (pos < max)
	{
		elems[pos] = e;
		pos++;
	}
	return *this;
}
STACK& STACK::operator>>(int &e)	//出栈到e,并返回栈
{
	if (pos > 0)
	{
		e = elems[pos - 1];
		pos--;
	}
	return *this;
}
STACK& STACK::operator=(const STACK&s) //赋s给栈,并返回被赋值的栈
{
	int i;
	if (s.elems) {
		delete[] elems;
		pos = s.pos;
		*(int *)(&max) = s.size();
		*(int **)(&elems) = new int[max];
		for (i = 0; i < pos; i++)
			elems[i] = s.elems[i];
	}
	return *this;
}
void STACK::print() const			//打印栈
{
	int i;
	if (pos > 0)
	{
		for (i = 0; i < pos; i++)
		{
			printf("%d  ", elems[i]);
		}
	}
}
STACK::~STACK()					//销毁栈
{
	if (elems)
	{
		delete[] elems;
		*(int **)(&elems) = 0;
	}
}

QUEUE::QUEUE(int m) //每个栈最多m个元素，要求实现的队列最多能入2m个元素
	:STACK(m), s2(m)
{

}
QUEUE::QUEUE(const QUEUE&s) 			//用队列s拷贝初始化队列
	: STACK(s.STACK::size()), s2(s.s2.size())
{
	*this = s;
}
QUEUE::operator int() const			//返回队列的实际元素个数
{
	return s2 + STACK::operator int();
}
int QUEUE::full() const		       //返回队列是否已满，满返回1，否则返回0
{
	if ((STACK::size() == STACK::operator int()) && s2)
		//栈s1满时,且栈s2中还有元素时，为满队列
		return 1;
	else
		return 0;
}
int QUEUE::operator[ ](int x)const   //取下标为x的元素，第1个元素下标为0
{
	int pos = STACK::operator int() + s2; //队列中的实际元素的个数
	if (pos == 0 || x > pos - 1) // 队列中没有元素，或者下标超过元素数量
	{
		printf("E  ");
		exit(1);
	}
	//当栈s2不为空时说明，有一部分元素在s2中,且当前队列的队首在s2中
	//栈s2为空时说明，队列元素都在栈s1中
	if (x >= s2)
		return STACK::operator[](x - s2);
	else
		return s2[s2 - x - 1];
}
QUEUE& QUEUE::operator<<(int e)  //将e入队列,并返回队列
{
	int k;
	if (full())
	{
		printf("E  ");
		return *this;
	}
	//如果s1没有满,那么进入栈s1
	if (STACK::operator int() < STACK::size())
	{
		STACK::operator<<(e);
		return *this;
	}
	else
	{
		//如果s1满了，那么将s1中的元素出栈到s2中
		while (STACK::operator int() != 0)
		{
			STACK::operator>>(k);
			s2 << k;
		}
		STACK::operator<<(e);
	}
	return *this;
}
QUEUE& QUEUE::operator>>(int &e)	//出队列到e,并返回队列
{
	//如果队列中有元素，则进行出队列操作
	if (STACK::operator int() != 0 || s2 != 0)
	{
		if (s2 != 0)
		{
			//栈s2不为空时，队首在s2中
			s2 >> e;
			return *this;
		}
		else
		{
			//队列元素全在s1中,则先将栈s1中的元素出栈到s2中，再进行出队列操作
			//保持队列先进行出的原则
			int k;
			while (STACK::operator int() != 0)
			{
				STACK::operator>>(k);
				s2 << k;
				// printf("K:%d  ",k);
			}
			s2 >> e;
			return *this;
		}
	}
	else
	{
		printf("E  ");
		fputs("E  ", fout);
	}
	return *this;
}
QUEUE& QUEUE::operator=(const QUEUE&s) //赋s给队列,并返回被赋值的队列
{
	if (s.s2.operator int() != 0)   //队列s.s2中有元素,则先将其赋值给当前队列的栈s2
		s2 = s.s2;
	if (s.STACK::operator int() != 0)
		STACK::operator=(s);
	return *this;
}
void QUEUE::print() const			//打印队列
{
	int i;
	if (STACK::operator int() == 0 && s2 == 0)
	{
		printf("E  ");
		fputs("E  ", fout);
	}
	if (s2 != 0)
	{
		//栈s2不为空时,队首元素在栈s2中
		for (i = s2 - 1; i >= 0; i--)
		{
			printf("%d  ", s2[i]);
			fprintf(fout, "%d  ", s2[i]);
		}
	}
	//打印栈s1中的元素
	if (STACK::operator int() != 0)
	{
		//printf("STACK:%d  ",STACK::operator int());
		for (i = 0; i < STACK::operator int(); i++)
		{
			printf("%d  ", STACK::operator[](i));
			fprintf(fout, "%d  ", STACK::operator[](i));
		}
	}
}
QUEUE::~QUEUE()					//销毁队列
{

}