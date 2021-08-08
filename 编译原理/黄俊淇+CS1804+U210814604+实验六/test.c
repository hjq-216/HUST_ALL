int a,b,c;
float m,n;
int check(int a)
{
    if(a == 1 || a == 2)
        return 1;
}
int main(){
    int m,n,i;
    m = read();
    i = 1;
    while (i <= m)
    {
        n = check(i);
        write(n);
        i = i + 1;
    }
    i++;
    return 1;
    
}