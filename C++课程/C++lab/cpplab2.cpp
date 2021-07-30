#include <iostream>
#include<cstring>
#include<stdlib.h>
using namespace std;
FILE *fout;
class STACK{
    int  *const  elems;	//申请内存用于存放栈的元素
    const  int   max;	//栈能存放的最大元素个数
    int   pos;			//栈实际已有元素个数，栈空时pos=0;
public:
STACK(int m);		//初始化栈：最多m个元素
STACK(const STACK&s); //用栈s拷贝初始化栈
int  size ( ) const;		//返回栈的最大元素个数max
int  howMany ( ) const;	//返回栈的实际元素个数pos
int  getelem (int x) const;	//取下标x处的栈元素
STACK& push(int e); 	//将e入栈,并返回栈
STACK& pop(int &e); 	//出栈到e,并返回栈
STACK& assign(const STACK&s); //赋s给栈,并返回被赋值的栈
void print( ) const;		//打印栈
~STACK( );				//销毁栈
};

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
                    int stackpos = p->howMany();
                    int stackmax = p->size();
                    if (stackpos == stackmax)
                    {
                        printf("E  ");
                        fputs("E  ", fout);
                        exit(1);
                    }
                    p->push(itemp);
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
                        if (itemp > p->howMany())
                        {
                            printf("E  ");
                            fputs("E  ", fout);
                            break;
                        }
                        int j;
                        for (j = 0; j < itemp; j++)
                            p->pop(e);
                        if (p->howMany())
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
                        s->assign(*p);
                        p = s;
                        if (p->howMany()) p->print();
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
                    if (p->howMany()) p->print();
                }
                if (!strcmp(argv[i], "-N"))
                {
                    fputs("N  ", fout);
                    printf("N  ");
                    int N = p->howMany();
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
                        if (p->howMany() <= itemp)
                        {
                            fputs("E  ", fout);
                            printf("E  ");
                            break;
                        }
                        else
                        {
                            int N = p->getelem(itemp);
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
STACK::STACK(int m)     //初始化栈
    :elems(new int[m]),max(m),pos(0)
{

}
STACK::STACK(const STACK&s)
    :elems(new int[s.max]),max(s.max),pos(s.pos)
{
    int i;
    for(i = 0;i<pos;i++)
    {
        this->elems[i] = s.elems[i];
    }
}
int STACK::size()const
{
    return this->max;
}
int STACK::howMany()const
{
    return this->pos;
}
int STACK::getelem(int x)const
{
    return this->elems[x];
}
STACK& STACK::push(int e)
{
    if(this->pos<this->max)
    {
        this->elems[pos++] = e;
    }
    return *this;
}
STACK& STACK::pop(int &e)
{
    if(this->pos>0)
    {
        e = this->elems[--pos];
    }
    return *this;
}
STACK& STACK::assign(const STACK& s)//赋s给栈,并返回被赋值的栈
{
    int i;
    if(s.elems){
        delete [] this->elems;
        this->pos = s.howMany();
        *(int*)(&(this->max)) = s.size();
        *(int **)(&(this->elems)) = new int[this->max];
        for(i=0;i<pos;i++)
            elems[i] = s.elems[i];
    }
}
void STACK::print()const
{
    int i;
    if(this->pos>0)
    {
        for(i = 0;i<this->pos;i++)
        {
            printf("%d  ",this->elems[i]);
        }
    }
}
STACK::~STACK()
{
    if(elems)
    {
        delete [] elems;
        *(int **)(&(this->elems)) = 0;
    }
}