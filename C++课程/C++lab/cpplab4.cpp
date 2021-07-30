#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
class STACK {
	int  *const  elems;	//�����ڴ����ڴ��ջ��Ԫ��
	const  int   max;	//ջ�ܴ�ŵ����Ԫ�ظ���
	int   pos;			//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
public:
	STACK(int m);		//��ʼ��ջ�����m��Ԫ��
	STACK(const STACK&s); 			//��ջs������ʼ��ջ
	virtual int  size() const;			//����ջ�����Ԫ�ظ���max
	virtual operator int() const;			//����ջ��ʵ��Ԫ�ظ���pos
	virtual int operator[ ] (int x) const;	//ȡ�±�x����ջԪ��
	virtual STACK& operator<<(int e); 	//��e��ջ,������ջ
	virtual STACK& operator>>(int &e);	//��ջ��e,������ջ
	virtual STACK& operator=(const STACK&s); //��s��ջ,�����ر���ֵ��ջ
	virtual void print() const;			//��ӡջ
	virtual ~STACK();					//����ջ
};

class QUEUE :public STACK {
	STACK  s2;
public:
	QUEUE(int m); //ÿ��ջ���m��Ԫ�أ�Ҫ��ʵ�ֵĶ����������2m��Ԫ��
	QUEUE(const QUEUE&s); 			//�ö���s������ʼ������
	virtual operator int() const;			//���ض��е�ʵ��Ԫ�ظ���
	virtual int full() const;		       //���ض����Ƿ�������������1�����򷵻�0
	virtual int operator[ ](int x)const;   //ȡ�±�Ϊx��Ԫ�أ���1��Ԫ���±�Ϊ0
	virtual QUEUE& operator<<(int e);  //��e�����,�����ض���
	virtual QUEUE& operator>>(int &e);	//�����е�e,�����ض���
	virtual QUEUE& operator=(const QUEUE&s); //��s������,�����ر���ֵ�Ķ���
	virtual void print() const;			//��ӡ����
	virtual ~QUEUE();					//���ٶ���
};
using namespace std;
int isPrime(int num); //�������������Ƿ�������
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
		int M, F;    //��Ů���ӳ�ʼ����
		int index_M, index_F; //ĳһ��ʿ�ĳ�ʼλ�ã�ĳһŮʿ�ĳ�ʼλ��
		cout << "������ʿ���е�������";
		cin >> M;
		while (!isPrime(M))
		{
			cout << "����������������";
			cin >> M;
		}
		cout << "����Ůʿ���е����������ܵ�����ʿ���е�������:";
		cin >> F;
		while (!isPrime(F) && F != M)
		{
			cout << "����������������";
			cin >> F;
		}
		cout << "������ʿ�ĳ�ʼλ��:";
		cin >> index_M;
		while (index_M > M)
		{
			cout << "���������룺";
			cin >> index_M;
		}
		cout << "������Ůʿ�ĳ�ʼλ��:";
		cin >> index_F;
		while (index_F > F)
		{
			cout << "���������룺";
			cin >> index_F;
		}
		QUEUE *mQueue = new QUEUE(M);
		QUEUE *fQueue = new QUEUE(F);
		for (int i = 1; i <= M; i++)
		{
			if (i != index_M)
				*mQueue << 1;
			else
				*mQueue << 0; //��ǵ�Mλ��ʿ
		}

		for (int i = 1; i <= F; i++)
		{
			if (i != index_F)
				*fQueue << 1;
			else
				*fQueue << 0; //��ǵ�FλŮʿ
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
		cout << "�ڵ�[" << count << "]֧����ʱ�����Թ���";
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
STACK::STACK(int m)		//��ʼ��ջ�����m��Ԫ��
	:elems(new int[m]), max(m), pos(0)
{

}
STACK::STACK(const STACK&s) 			//��ջs������ʼ��ջ
	: elems(new int[s.max]), max(s.max), pos(s.pos)
{
	int i;
	for (i = 0; i < pos; i++)
	{
		elems[i] = s.elems[i];
	}
}
int STACK::size() const			//����ջ�����Ԫ�ظ���max
{
	return max;
}
STACK::operator int() const			//����ջ��ʵ��Ԫ�ظ���pos
{
	return pos;
}
int STACK::operator[ ] (int x) const	//ȡ�±�x����ջԪ��
{
	return elems[x];
}
STACK& STACK::operator<<(int e) 	//��e��ջ,������ջ
{
	if (pos < max)
	{
		elems[pos] = e;
		pos++;
	}
	return *this;
}
STACK& STACK::operator>>(int &e)	//��ջ��e,������ջ
{
	if (pos > 0)
	{
		e = elems[pos - 1];
		pos--;
	}
	return *this;
}
STACK& STACK::operator=(const STACK&s) //��s��ջ,�����ر���ֵ��ջ
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
void STACK::print() const			//��ӡջ
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
STACK::~STACK()					//����ջ
{
	if (elems)
	{
		delete[] elems;
		*(int **)(&elems) = 0;
	}
}

QUEUE::QUEUE(int m) //ÿ��ջ���m��Ԫ�أ�Ҫ��ʵ�ֵĶ����������2m��Ԫ��
	:STACK(m), s2(m)
{

}
QUEUE::QUEUE(const QUEUE&s) 			//�ö���s������ʼ������
	: STACK(s.STACK::size()), s2(s.s2.size())
{
	*this = s;
}
QUEUE::operator int() const			//���ض��е�ʵ��Ԫ�ظ���
{
	return s2 + STACK::operator int();
}
int QUEUE::full() const		       //���ض����Ƿ�������������1�����򷵻�0
{
	if ((STACK::size() == STACK::operator int()) && s2)
		//ջs1��ʱ,��ջs2�л���Ԫ��ʱ��Ϊ������
		return 1;
	else
		return 0;
}
int QUEUE::operator[ ](int x)const   //ȡ�±�Ϊx��Ԫ�أ���1��Ԫ���±�Ϊ0
{
	int pos = STACK::operator int() + s2; //�����е�ʵ��Ԫ�صĸ���
	if (pos == 0 || x > pos - 1) // ������û��Ԫ�أ������±곬��Ԫ������
	{
		printf("E  ");
		exit(1);
	}
	//��ջs2��Ϊ��ʱ˵������һ����Ԫ����s2��,�ҵ�ǰ���еĶ�����s2��
	//ջs2Ϊ��ʱ˵��������Ԫ�ض���ջs1��
	if (x >= s2)
		return STACK::operator[](x - s2);
	else
		return s2[s2 - x - 1];
}
QUEUE& QUEUE::operator<<(int e)  //��e�����,�����ض���
{
	int k;
	if (full())
	{
		printf("E  ");
		return *this;
	}
	//���s1û����,��ô����ջs1
	if (STACK::operator int() < STACK::size())
	{
		STACK::operator<<(e);
		return *this;
	}
	else
	{
		//���s1���ˣ���ô��s1�е�Ԫ�س�ջ��s2��
		while (STACK::operator int() != 0)
		{
			STACK::operator>>(k);
			s2 << k;
		}
		STACK::operator<<(e);
	}
	return *this;
}
QUEUE& QUEUE::operator>>(int &e)	//�����е�e,�����ض���
{
	//�����������Ԫ�أ�����г����в���
	if (STACK::operator int() != 0 || s2 != 0)
	{
		if (s2 != 0)
		{
			//ջs2��Ϊ��ʱ��������s2��
			s2 >> e;
			return *this;
		}
		else
		{
			//����Ԫ��ȫ��s1��,���Ƚ�ջs1�е�Ԫ�س�ջ��s2�У��ٽ��г����в���
			//���ֶ����Ƚ��г���ԭ��
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
QUEUE& QUEUE::operator=(const QUEUE&s) //��s������,�����ر���ֵ�Ķ���
{
	if (s.s2.operator int() != 0)   //����s.s2����Ԫ��,���Ƚ��丳ֵ����ǰ���е�ջs2
		s2 = s.s2;
	if (s.STACK::operator int() != 0)
		STACK::operator=(s);
	return *this;
}
void QUEUE::print() const			//��ӡ����
{
	int i;
	if (STACK::operator int() == 0 && s2 == 0)
	{
		printf("E  ");
		fputs("E  ", fout);
	}
	if (s2 != 0)
	{
		//ջs2��Ϊ��ʱ,����Ԫ����ջs2��
		for (i = s2 - 1; i >= 0; i--)
		{
			printf("%d  ", s2[i]);
			fprintf(fout, "%d  ", s2[i]);
		}
	}
	//��ӡջs1�е�Ԫ��
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
QUEUE::~QUEUE()					//���ٶ���
{

}