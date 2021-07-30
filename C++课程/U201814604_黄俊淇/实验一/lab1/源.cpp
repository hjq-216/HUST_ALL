#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
extern const char* TestQueue(int& s);
struct Queue {
    int* const elems;	   	//elems�����ڴ����ڴ�Ŷ��е�Ԫ��
    const int   max;	  	//elems��������Ԫ�ظ���max
    int   head, tail;	 	//����ͷhead��βtail���ӿ�head=tail;��ʼhead=tail=0
};
void initQueue(Queue* const p, int m);	//��ʼ��pָ���У��������m��Ԫ��
void initQueue(Queue* const p, const Queue& s); //��s�����ʼ��pָ����
void initQueue(Queue* const p, Queue&& s); //��s�ƶ���ʼ��pָ����
int  number(const Queue* const p);	//����pָ���е�ʵ��Ԫ�ظ���
int  size(const Queue* const p);			//����pָ������������Ԫ�ظ���max
Queue* const enter(Queue* const p, int e);  //��e�����β����������p
Queue* const leave(Queue* const p, int& e); //�Ӷ��׳�Ԫ�ص�e��������p
Queue* const assign(Queue* const p, const Queue& q); //�����s�����в�����p
Queue* const assign(Queue* const p, Queue&& q); //�ƶ���s�����в�����p
char* print(const Queue* const p, char* s);//��ӡpָ������s������s
void destroyQueue(Queue* const p);	 //����pָ��Ķ���
int main() {
    int nmark = 0;
    const char* strResult = TestQueue(nmark);
    cout << "ѧ�ţ�U201814604" << endl;
    cout << "�������ƿ��" << endl;
    cout << "ʵ��һ���ԣ�" << strResult << ',' << nmark << endl;
    return 0;
}
void initQueue(Queue* const p, int m) {
    (int*&)p->elems = new int[m];
    (int&)p->max = m;
    p->head = 0;
    p->tail = 0;
}
void initQueue(Queue* const p, const Queue& s) {
    (int*&)p->elems = new int[s.max];
    (int&)p->max = s.max;
    p->head = s.head;
    p->tail = s.tail;
    int i;
    if (s.head < s.tail) {
        for (i = s.head; i < s.tail; i++) {
            p->elems[i] = s.elems[i];
        }
    }
    else if (s.head > s.tail) {
        int count = 0;
        i = s.head;
        while (count < number(&s)) {
            p->elems[i] = s.elems[i];
            i++;
            count++;
            if (i == s.max) i = 0;
        }
    }

}
void initQueue(Queue* const p, Queue&& s) {
    (int*&)p->elems = s.elems;
    (int*&)s.elems = nullptr;
    (int&)p->max = s.max;
    p->head = s.head;
    p->tail = s.tail;
    s.head = 0;
    s.tail = 0;
    (int&)s.max = 0;
}
int  number(const Queue* const p) {
    if (p->head <= p->tail) return p->tail - p->head;
    else return (p->max - p->head + p->tail);
}
int  size(const Queue* const p) {
    return p->max;
}
Queue* const enter(Queue* const p, int e) {
    if (((p->tail + 1) % p->max) == p->head) throw("Queue is full!");
    p->elems[p->tail] = e;
    p->tail += 1;
    if (p->tail == p->max) p->tail = 0;
    return p;
}
Queue* const leave(Queue* const p, int& e) {
    if (!number(p)) 
        throw("Queue is empty!");
    else {
        e = p->elems[p->head];
        if (p->head == p->max - 1) p->head = 0;
        else p->head += 1;
    }
    return p;
}
Queue* const assign(Queue* const p, const Queue& q) {
    if (p == &q) return p;
    if (p->elems!=0) delete[] p->elems;
    (int*&)p->elems = new int[q.max];
    (int&)p->max = q.max;
    p->head = q.head;
    p->tail = q.tail;
    int i;
    if (q.head < q.tail) {
        for (i = q.head; i <= q.tail; i++) {
            p->elems[i] = q.elems[i];
        }
    }
    else if (q.head > q.tail) {
        int count = 0;
        i = q.head;
        while (count < number(&q)) {
            p->elems[i] = q.elems[i];
            i++;
            count++;
            if (i == q.max) i = 0;
        }
    }
    return p;
}
Queue* const assign(Queue* const p, Queue&& q) {
    if (p == &q) return p;
    if (p->elems != 0) delete[] p->elems;
    (int*&)p->elems = q.elems;
    (int*&)q.elems = nullptr;
    (int&)p->max = q.max;
    (int&)q.max = 0;
    p->head = q.head;
    p->tail = q.tail;
    q.head = 0;
    q.tail = 0;
    return p;
}
char* print(const Queue* const p, char* s) {
    int i;
    int head = p->head;
    int count;
    int j;
    if (p->head == p->tail) { throw("Queue is empty!"); }
    else if (p->head < p->tail) {
        i = 0;
        j = number(p);
        while (j) {
            count = 0;
            _itoa(p->elems[head], &s[i], 10);
            int num = p->elems[head];
            while (num) {
                num /= 10;
                count++;
            }
            i += count;
            if (head != (p->tail - 1)) { s[i] = ','; i++; }
            head += 1;
            j--;
        }
        s[i] = '\0';
    }
    else if (p->head > p->tail) {
        i = 0;
        j = number(p);
        head = p->head;
        while (j) {
            count = 0;
            _itoa(p->elems[head], &s[i], 10);
            int num = p->elems[head];
            while (num) {
                num /= 10;
                count++;
            }
            i+=count;
            if (((head+1)%p->max) != (p->tail)) { s[i] = ','; i++; }
            head++;
            if (head == (p->max))
                head = 0;
            j--;
        }
        s[i] = '\0';
    }

    return s;
}
void destroyQueue(Queue* const p) {
    delete[] p->elems;
    (int*&)p->elems = nullptr;
    p->head = 0;
    p->tail = 0;
    (int&)p->max = 0;
}

