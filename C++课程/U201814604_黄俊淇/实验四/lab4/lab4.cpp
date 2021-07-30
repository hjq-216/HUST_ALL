#define _CRT_SECURE_NO_WARNINGS 
#include <iomanip> 
#include <exception>
#include <typeinfo>
#include <string.h>
#include<iostream>
extern const char* TestMAT(int& s);	//����ʵ����

using namespace std;
template <typename T>
class MAT {
	T* const e;							//ָ���������;���Ԫ�ص�ָ��
	const int r, c;							//�������r����c��С
public:
	MAT(int r, int c);						//������
	MAT(const MAT& a);				//�������
	MAT(MAT&& a)noexcept;			//�ƶ�����
	virtual ~MAT()noexcept;
	virtual T* const operator[ ](int r);//ȡ����r�еĵ�һ��Ԫ�ص�ַ��rԽ�����쳣
	virtual MAT operator+(const MAT& a)const;	//����ӷ������ܼ����쳣
	virtual MAT operator-(const MAT& a)const;	//������������ܼ����쳣
	virtual MAT operator*(const MAT& a)const;	//����˷������ܳ����쳣
	virtual MAT operator~()const;					//����ת��
	virtual MAT& operator=(const MAT& a);		//�����ֵ����
	virtual MAT& operator=(MAT&& a)noexcept;	//�ƶ���ֵ����
	virtual MAT& operator+=(const MAT& a);		//��+=������
	virtual MAT& operator-=(const MAT& a);		//��-=������
	virtual MAT& operator*=(const MAT& a);		//��*=������
//print�����s������s�����ÿո���������ûس�����
	virtual char* print(char* s)const noexcept;
};
template MAT<int>;
template MAT<long long>;
int main(int argc, char* argv[]) 					//����չmain()������������
{
	
	/*MAT<int>   a(1, 2), b(2, 2), c(1, 2);
	char t[2048];
	a[0][0] = 1;			//���Ƶس�ʼ�����������Ԫ��
	a[0][1] = 2; 			//�ȼ��ڡ�*(a.operator[ ](0)+1)=2;�����ȼ��ڡ�*(a[0]+1)=2;��
	a.print(t);			//��ʼ�����������þ���
	b[0][0] = 3; 	b[0][1] = 4;		//����T* const operator[ ](int r)��ʼ������Ԫ��
	b[1][0] = 5; 	b[1][1] = 6;
	b.print(t);
	c = a * b;						//���Ծ���˷�����
	c.print(t);
	(a + c).print(t);					//���Ծ���ӷ�����
	c = c - a;						//���Ծ����������
	c.print(t);
	c += a;							//���Ծ���+=������
	c.print(t);
	c = ~a;							//���Ծ���ת������
	c.print(t);*/
	int nmark = 0;
	const char* strResult = TestMAT(nmark);
	cout << "ѧ�ţ�U201814604" << endl;
	cout << "�������ƿ��" << endl;
	cout << "ʵ���Ĳ��ԣ�" << strResult << ',' << nmark << endl;
	return 0;
}
template <typename T>
MAT<T>::MAT(int r, int c): e(new T [r*c]),r(r),c(c){

}
template <typename T>
MAT<T>::MAT(const MAT& a):e(new  T [a.r*a.c]),r(a.r),c(a.c) {
	for (int i = 0; i < r * c; i++) {
		e[i] = a.e[i];
	}
}
template <typename T>
MAT<T>::MAT(MAT&& a)noexcept :e(move(a.e)),r(a.r),c(a.c){
	(T*&)a.e = nullptr;
	(int&)a.r = 0;
	(int&)a.c = 0;
}
template <typename T>
MAT<T>::~MAT() noexcept{
	//if (e != 0) delete  e;
}
template <typename T>
T* const MAT<T>::operator[](int r) {
	if (r < 0||(r>=(this->r))) throw("overflowed!");
	return & e[c * r];
}
template <typename T>
MAT<T> MAT<T>:: operator+(const MAT<T>& a)const {
	if (r != a.r || c != a.c) throw("r c ");
	MAT<T> b(r, c);
	for (int i = 0; i < r * c; i++) {
		b.e[i] = e[i] + a.e[i];
	}
	return b;
}
template <typename T>
MAT<T> MAT<T>:: operator-(const MAT<T>& a)const {
	if (r != a.r || c != a.c) throw("r c ");
	MAT<T> b(r, c);
	for (int i = 0; i < r * c; i++) {
		b.e[i] = e[i] - a.e[i];
	}
	return b;
}
template <typename T>
MAT<T> MAT<T>:: operator*(const MAT<T>& a)const {
	if (c != a.r) throw("a r");
	MAT<T> b(r, a.c);
	int column = a.c;//��
	int row = r;//��
	int number = row * column;
	int i = 0;
	int j = 0;
	T* num = new T[number];
	int k;
	for (i = 0; i < r; i++) {
		for (j = 0; j < a.c; j++) {
			num[c * i + j] = 0;
			for (k = 0; k < c; k++) {
				num[c * i + j] += e[c * i + k] * a.e[c * k + j];
			}

		}
	}
	
	for (i = 0; i < r * c; i++) {
		b.e[i] = num[i];
	}
	delete[] num;
	return b;
}
template <typename T>
MAT<T> MAT<T>:: operator~()const {
	MAT<T> b(c, r);
	int i, j;
	if(r==c){
		for (i = 0; i < r; i++) {
			for (j = 0; j < c; j++) {
				b.e[c * j + i] = e[c * i + j];
			}
		}
	}
	else {
		for (i = 0; i < r; i++) {
			for (j = 0; j < c; j++) {
				b.e[(c-1) * j + i] = e[c * i + j];
			}
		}
	}
	return b;
}
template <typename T>
MAT<T>& MAT<T>::operator=(const MAT<T>& a) {
	if (e) delete[] e;
	if (e == a.e) return *this;
	(T*&)e = new T[a.r * a.c];
	for (int i = 0; i < a.r * a.c; i++) {
		e[i] = a.e[i];
	}
	(int&)r = a.r;
	(int&)c = a.c;
	return *this;
}
template <typename T>
MAT<T>& MAT<T>::operator=(MAT<T>&& a)noexcept {
	if (e == a.e) return *this;
	(T*&)e = a.e;
	(T*&)a.e = nullptr;
	//delete [] a.e;
	(int&)r = a.r;
	(int&)c = a.c;
	(int&)a.r = 0;
	(int&)a.c = 0;
	return *this;
}
template <typename T>
MAT<T>& MAT<T>::operator+=(const MAT<T>& a) {
	if (r != a.r || c != a.c) throw("r c ");
	for (int i = 0; i < r * c; i++) {
		e[i] += a.e[i];
	}
	return *this;
}
template <typename T>
MAT<T>& MAT<T>::operator-=(const MAT<T>& a) {
	if (r != a.r || c != a.c) throw("r c ");
	for (int i = 0; i < r * c; i++) {
		e[i] -= a.e[i];
	}
	return *this;
}
template <typename T>
MAT<T>& MAT<T>::operator*=(const MAT<T>& a) {
	if (c != a.r) throw("a r");
	int column = a.c;//��
	int row = r;//��
	int number = row * column;
	int i = 0;
	int j = 0;
	T* num = new T[number];
	int k;
	for (i = 0; i < r; i++) {
		for (j = 0; j < a.c; j++) {
			num[c * i + j] = 0;
			for (k = 0; k < c; k++) {
				num[c * i + j] += e[c * i + k] * a.e[c * k + j];
			}

		}
	}
	(int&)c = a.c;
	for (i = 0; i < r * c; i++) {
		e[i] = num[i];
	}
	delete[] num;
	return *this;
}
template <typename T>
char* MAT<T>::print(char* s)const noexcept {
	int i, j, k;
	i = 0;
	k = 0;
	//int count = 0;
	while (i < r) {
		j = 0;
		while (j < c) {
			k+=sprintf(s+k, "%ld ", e[i * c + j]);
			j++;
		}
		s[k] = '\n';
		k++;
		i++;
	}
	s[k] = '\0';
	//s[k] = '\n';
	//s[k + 1] = '\0';
	//cout << s  ;
	
	return s;
}