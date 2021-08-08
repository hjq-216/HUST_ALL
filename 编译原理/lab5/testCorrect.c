int f1(int m,int n,int l)
{   
    int a=0,b=0;
    int c[3];//增加数组
    char d = 'h';//增加字符型
    c[a] = 5;//增加[]
    a++;//增加自增，自减
    b--;
    a+=5;//增加x=
    return a;
}

int f2()
{
   int sum = 0;
   int i;
   int j = 6;
   for (i = j; i < 6; i++)//增加for
     {sum += i;}
   return sum;
}

int f3()
{
  int x = f2();
  float f = 1.0;
  return x;
}