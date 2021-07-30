#include<iostream>
#include<cstring>
#include<stdlib.h>
using namespace std;

class STACK{
    int  *const  elems;	//申请内存用于存放栈的元素
    const  int   max;	//栈能存放的最大元素个数
    int   pos;			//栈实际已有元素个数，栈空时pos=0;
public:
STACK(int m);		//初始化栈：最多m个元素
STACK(const STACK&s); 			//用栈s拷贝初始化栈
virtual int  size ( ) const;			//返回栈的最大元素个数max
virtual operator int ( ) const;			//返回栈的实际元素个数pos
virtual int operator[ ] (int x) const;	//取下标x处的栈元素
virtual STACK& operator<<(int e); 	//将e入栈,并返回栈
virtual STACK& operator>>(int &e);	//出栈到e,并返回栈
virtual STACK& operator=(const STACK&s); //赋s给栈,并返回被赋值的栈
virtual void print( ) const;			//打印栈
virtual ~STACK( );					//销毁栈
};
FILE *fout;
int main(int argc, char *argv[])
{
        STACK *p;
        STACK *s;
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
                    p = new STACK(itemp);
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
                    int stackpos = *p;
                    int stackmax = p->size();
                    if (stackpos == stackmax)
                    {
                        printf("E  ");
                        fputs("E  ", fout);
                        exit(1);
                    }
                    *p<<itemp;
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
                        for (j = 0; j < itemp; j++)
                            *p>>e;
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
                        s = new STACK(itemp);
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
                    s = new STACK(*p);
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
        fclose(fout);
        return 0;
}
STACK::STACK(int m)		//初始化栈：最多m个元素
    :elems(new int[m]),max(m),pos(0)
{

}
STACK::STACK(const STACK&s) 			//用栈s拷贝初始化栈
    :elems(new int[s.max]),max(s.max),pos(s.pos)
{
    int i;
    for(i = 0;i<pos;i++)
    {
        elems[i] = s.elems[i];
    }
}
int STACK::size ( ) const			//返回栈的最大元素个数max
{
    return max;
}
STACK::operator int ( ) const			//返回栈的实际元素个数pos
{
    return pos;
}
int STACK::operator[ ] (int x) const	//取下标x处的栈元素
{
    return elems[x];
}
STACK& STACK::operator<<(int e) 	//将e入栈,并返回栈
{
    if(pos < max)
    {
        elems[pos++] = e;
    }
    return *this;
}
STACK& STACK::operator>>(int &e)	//出栈到e,并返回栈
{
    if(pos > 0)
    {
        e = elems[--pos];
    }
    return *this;
}
STACK& STACK::operator=(const STACK&s) //赋s给栈,并返回被赋值的栈
{
    int i;
    if(s.elems){
        delete[] elems;
        pos = s;
        *(int *)(&max) = s.size();
        *(int **)(&elems) = new int[max];
        for(i = 0;i<pos;i++)
            elems[i] = s.elems[i];
    }
    return *this;
}
void STACK::print( ) const			//打印栈
{
    int i;
    if(pos>0)
    {
        for(i = 0;i<pos;i++)
        {
            printf("%d  ",elems[i]);
        }
    }
}
STACK::~STACK( )					//销毁栈
{
    if(elems)
    {
        delete [] elems;
        *(int **)(&elems) = 0;
    }
}