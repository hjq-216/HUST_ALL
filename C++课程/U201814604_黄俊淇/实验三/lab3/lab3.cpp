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
    STACK(int m);                    		//��ʼ��ջ�������2m-2��Ԫ��
    STACK(const STACK& s);         		//��ջs�����ʼ��ջ
    STACK(STACK&& s)noexcept;     		//��ջs�ƶ�������ʼ��ջ
    int  size()const noexcept;		  		//����ջ��������2m
    operator int() const noexcept;	   		//����ջ��ʵ��Ԫ�ظ���
    STACK& operator<<(int e); 	     		//��e��ջ�������ص�ǰջ
    STACK& operator>>(int& e);     		//��ջ��e�������ص�ǰջ
    STACK& operator=(const STACK& s);	//�����ֵ�����ر���ֵջ
    STACK& operator=(STACK&& s)noexcept;//�ƶ���ֵ�����ر���ֵջ
    char* print(char* b)const noexcept;	//��ջ�׵�ջ����ӡջԪ�� 
    ~STACK()noexcept;	              	//����ջ
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
    cout << "ѧ�ţ�U201814604" << endl;
    cout << "�������ƿ��" << endl;
    cout << "ʵ�������ԣ�" << strResult << ',' << nmark << endl;
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
