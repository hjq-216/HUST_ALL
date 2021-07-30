#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include<iostream>
extern const char* TestQUEUE(int& s);
class QUEUE {
    int* const  elems;	//elems申请内存用于存放队列的元素
    const  int  max;	//elems申请的最大元素个数为max
    int   head, tail;	 	//队列头head和尾tail，队空head=tail;初始head=tail=0
public:
    QUEUE(int m);		//初始化队列：最多申请m个元素
    QUEUE(const QUEUE& q); 			//用q深拷贝初始化队列
    QUEUE(QUEUE&& q)noexcept;		//用q移动初始化队列
    virtual operator int() const noexcept;	//返回队列的实际元素个数
    virtual int size() const noexcept;		//返回队列申请的最大元素个数max
    virtual QUEUE& operator<<(int e);  	//将e入队列尾部，并返回当前队列
    virtual QUEUE& operator>>(int& e); 	//从队首出元素到e，并返回当前队列
    virtual QUEUE& operator=(const QUEUE& q);//深拷贝赋值并返回被赋值队列
    virtual QUEUE& operator=(QUEUE&& q)noexcept;//移动赋值并返回被赋值队列
    virtual char* print(char* s) const noexcept;//打印队列至s并返回s
    virtual ~QUEUE();	 					//销毁当前队列
};
int main() {
    using namespace std;
    int nmark = 0;
    const char* strResult = TestQUEUE(nmark);
    cout << "学号：U201814604" << endl;
    cout << "姓名：黄俊淇" << endl;
    cout << "实验二测试：" << strResult << ',' << nmark << endl;
    return 0;
}
QUEUE::QUEUE(int m) :elems(new int [m]),max(m){
    head = 0;
    tail = 0;
}
QUEUE::QUEUE(const QUEUE& q):elems(new int [q.max]),max(q.max) {
    for (int i = 0; i < q.max; i++) {
        {
            elems[i] = q.elems[i];
        }
    head = q.head;
    tail = q.tail;
    }
}
QUEUE::QUEUE(QUEUE&& q)noexcept :elems(q.elems),max(q.max){
    (int*&)q.elems = nullptr;
    head = q.head;
    tail = q.tail;
    q.head = 0;
    q.tail = 0;
    (int&)q.max = 0;
}
QUEUE::operator int() const noexcept {
    if (head <= tail) return tail - head;
    else return max - head + tail;
}
int QUEUE::size()const noexcept {
    return max;
}
QUEUE& QUEUE::operator<<(int e) {
    if (((this->tail + 1) % this->max) == this->head) throw("QUEUE is full!");
    this->elems[this->tail] = e;
    this->tail += 1;
    if (this->tail == this->max) this->tail = 0;
    return *this;
}
QUEUE& QUEUE::operator>>(int& e) {
    if (head==tail)
        throw("QUEUE is empty!");
    else {
        e = this->elems[this->head];
        if (this->head == this->max - 1) this->head = 0;
        else this->head += 1;
    }
    return *this;
}
QUEUE& QUEUE::operator=(const QUEUE& q) {
    if (this == &q)  return *this;;
    if (this->elems != 0) delete[] this->elems;
    (int*&)this->elems = new int[q.max];
    (int&)this->max = q.max;
    this->head = q.head;
    this->tail = q.tail;
    int i;
    if (q.head < q.tail) {
        for (i = q.head; i <= q.tail; i++) {
            this->elems[i] = q.elems[i];
        }
    }
    else if (q.head > q.tail) {
        int count = 0;
        i = q.head;
        while (count < q.size()) {
            this->elems[i] = q.elems[i];
            i++;
            count++;
            if (i == q.max) i = 0;
        }
    }
    return *this;
}
QUEUE& QUEUE::operator=(QUEUE&& q)noexcept {
    if (this== &q)  return *this;;
    if (this->elems != 0) delete[] this->elems;
    (int*&)this->elems = q.elems;
    (int*&)q.elems = nullptr;
    (int&)this->max = q.max;
    (int&)q.max = 0;
    this->head = q.head;
    this->tail = q.tail;
    q.head = 0;
    q.tail = 0;
    return *this;
}
char* QUEUE::print(char* s) const noexcept {
    int i;
    int head = this->head;
    int count;
    int j;
    if (this->head == this->tail) { throw("QUEUE is empty!"); }
    else if (this->head < this->tail) {
        i = 0;
        j = this->operator int();
        while (j) {
            count = 0;
            _itoa(this->elems[head], &s[i], 10);
            int num = this->elems[head];
            while (num) {
                num /= 10;
                count++;
            }
            i += count;
            if (head != (this->tail - 1)) { s[i] = ','; i++; }
            head += 1;
            j--;
        }
        s[i] = '\0';
    }
    else if (this->head > this->tail) {
        i = 0;
        j = this->operator int();
        head = this->head;
        while (j) {
            count = 0;
            _itoa(this->elems[head], &s[i], 10);
            int num = this->elems[head];
            while (num) {
                num /= 10;
                count++;
            }
            i += count;
            if (((head + 1) % this->max) != (this->tail)) { s[i] = ','; i++; }
            head++;
            if (head == (this->max))
                head = 0;
            j--;
        }
        s[i] = '\0';
    }

    return s;
}
QUEUE::~QUEUE() {
    if (elems != nullptr) {
        delete[] elems;
        (int*&)elems = nullptr;
        (int&)max = 0;
        head = 0;
        tail = 0;
    }
}