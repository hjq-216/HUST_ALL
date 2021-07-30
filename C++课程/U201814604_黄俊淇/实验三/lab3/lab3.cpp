#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include<iostream>
#include<cstring>
#include "QUEUE.h"
extern const char* TestSTACK(int& s);
class STACK : public QUEUE {
    QUEUE q;
public:
    STACK(int m);                    		//初始化栈：最多存放2m-2个元素
    STACK(const STACK& s);         		//用栈s深拷贝初始化栈
    STACK(STACK&& s)noexcept;     		//用栈s移动拷贝初始化栈
    int  size()const noexcept;		  		//返回栈的容量即2m
    operator int() const noexcept;	   		//返回栈的实际元素个数
    STACK& operator<<(int e); 	     		//将e入栈，并返回当前栈
    STACK& operator>>(int& e);     		//出栈到e，并返回当前栈
    STACK& operator=(const STACK& s);	//深拷贝赋值并返回被赋值栈
    STACK& operator=(STACK&& s)noexcept;//移动赋值并返回被赋值栈
    char* print(char* b)const noexcept;	//从栈底到栈顶打印栈元素 
    ~STACK()noexcept;	              	//销毁栈
};
int main() {
    using namespace std;
    char t[2018];
    int x;
    STACK a(10);
    a << 1;
    a << 2;
    a.print(t);
    cout << t << endl;
    STACK b(a);
    a >> x;
    cout << x << endl;
    b.print(t);
    cout << t << endl;
    a.print(t);
    cout << t << endl;
    a = b;
    a.print(t);
    cout << t << endl;
    a >> x;
    a >> x;
    cout << x << endl;
    a = move(b);
    a.print(t);
    cout << t << endl;
    //STACK c (move(b));
    //c.print(t);
    //cout << t << endl;
    int nmark = 0;
    const char* strResult = TestSTACK(nmark);
    cout << "学号：U201814604" << endl;
    cout << "姓名：黄俊淇" << endl;
    cout << "实验三测试：" << strResult << ',' << nmark << endl;
    return 0;
}
STACK::STACK(int m) :QUEUE(m), q(m) {
    
}
STACK::STACK(const STACK& s) : QUEUE(s), q(s.q) {

}
STACK::STACK(STACK&& s)noexcept : QUEUE(std::move(s)), q(std::move(s.q)) {

}
int STACK::size()const noexcept {
    return 2*q.size();
}
STACK::operator int()const noexcept {
    int q1 = QUEUE::operator int();
    int q2 = q.operator int();
    return q1 + q2;
}
STACK& STACK::operator<<(int e) {
    int q1 = QUEUE::operator int();
    int q2 = q.operator int();
    int temp;
    if((q1+q2)==(2*q.size()-2)) throw("STACK is full!");
    if (q1 == (q.size() - 1) && q2 < (q.size()- 1)) {
        this->QUEUE::operator>>(temp);
        q.operator<<(temp);
        this->QUEUE::operator<<(e);
    }
    else if (q1 < (q.size() - 1) && q2 == (q.size() - 1)) {
        this->QUEUE::operator<<(e);
    }
    else if (q1 == 0&&q2!=0) {
        q.operator<<(e);
    }
    else if(q2==0&&q1!=0) {
        this->QUEUE::operator<<(e);
    }
    else {
        this->QUEUE::operator<<(e);
    }
    return *this;
}
STACK& STACK::operator>>(int &e) {
    int q1 = QUEUE::operator int();
    int q2 = q.operator int();
    int num;
    if (q1 == 0 && q2 == 0) throw("STACK is empty!");
    int temp;
    if (q1 == 0 && q2 != 0) {
        while (q2 > 1) {
             q.operator>>(temp);
             this->QUEUE::operator<<(temp);
             --q2;
        }
        q.operator>>(e);
        
    }
    else if (q2 == 0 && q1 != 0) {
        while (q1 > 1) {
            this->QUEUE::operator>>(temp);
            q.operator<<(temp);
            --q1;
        }
        this->QUEUE::operator>>(e);
        
    }
    
    else {
        while (q1 > 1) {
            this->QUEUE::operator>>(temp);
            this->QUEUE::operator<<(temp);
            q1--;
    }
        this->QUEUE::operator>>(e);
    }
    return *this;
}
STACK& STACK::operator=(const STACK& s) {
    if (this == &s) return *this;
    //if (q.size() != 0) q.~QUEUE();
    //if (this->QUEUE::size() != 0) this->QUEUE::~QUEUE();
    this->QUEUE::operator=(s);
    q.operator=(s.q);
    return *this;
}
STACK& STACK::operator=(STACK&& s)noexcept {
    if (this == &s) return *this;
    this->QUEUE::operator=(std::move(s));
    q.operator=(std::move(s.q));
    return *this;
}
char* STACK::print(char* b)const noexcept {
    int q1 = this->QUEUE::operator int();
    int q2 = q.operator int();
    if (q1 == 0 && q2 == 0) throw("STACK is empty!");
    //std::string s;
    
    int i = 0;
    int j=0;
    if (q1 != 0 && q2 != 0) {
        q.print(b);
        int m = 2 * q2;
        b[m - 1] = ',';
        this->QUEUE::print(&b[m]);
        b[2*m-1] = '\0';
    }
    else if (q1 == 0 && q2 != 0) {
        q.print(b);
    }
    else if (q1 != 0&&q2==0 ) {
        this->QUEUE::print(b);
        //if (q2 != 0) q.print(b + 6);
    }
    /*std::string temp[10];
    while (s[i] != '\0') {
        if (s[i] == ',') {
            i++;
            j++;
            continue;
        }
        temp[j] += s[i];
    }*/
    //std::cout << b;
    return b;
}
STACK::~STACK()noexcept{
   // if(q.size()!=0) q.~QUEUE();
    //if(this) this->QUEUE::~QUEUE();
}
