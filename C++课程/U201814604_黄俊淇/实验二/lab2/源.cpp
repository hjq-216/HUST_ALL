#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include<iostream>
extern const char* TestQUEUE(int& s);
class QUEUE {
    int* const  elems;	//elems�����ڴ����ڴ�Ŷ��е�Ԫ��
    const  int  max;	//elems��������Ԫ�ظ���Ϊmax
    int   head, tail;	 	//����ͷhead��βtail���ӿ�head=tail;��ʼhead=tail=0
public:
    QUEUE(int m);		//��ʼ�����У��������m��Ԫ��
    QUEUE(const QUEUE& q); 			//��q�����ʼ������
    QUEUE(QUEUE&& q)noexcept;		//��q�ƶ���ʼ������
    virtual operator int() const noexcept;	//���ض��е�ʵ��Ԫ�ظ���
    virtual int size() const noexcept;		//���ض�����������Ԫ�ظ���max
    virtual QUEUE& operator<<(int e);  	//��e�����β���������ص�ǰ����
    virtual QUEUE& operator>>(int& e); 	//�Ӷ��׳�Ԫ�ص�e�������ص�ǰ����
    virtual QUEUE& operator=(const QUEUE& q);//�����ֵ�����ر���ֵ����
    virtual QUEUE& operator=(QUEUE&& q)noexcept;//�ƶ���ֵ�����ر���ֵ����
    virtual char* print(char* s) const noexcept;//��ӡ������s������s
    virtual ~QUEUE();	 					//���ٵ�ǰ����
};
int main() {
    using namespace std;
    int nmark = 0;
    const char* strResult = TestQUEUE(nmark);
    cout << "ѧ�ţ�U201814604" << endl;
    cout << "�������ƿ��" << endl;
    cout << "ʵ������ԣ�" << strResult << ',' << nmark << endl;
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