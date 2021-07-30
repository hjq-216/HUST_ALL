#define _CRT_SECURE_NO_WARNINGS 
#include <iomanip> 
#include <exception>
#include <typeinfo>
#include <string.h>
#include<iostream>
extern const char* TestMAT(int& s);	//用于实验四

using namespace std;
template <typename T>
class MAT {
	T* const e;							//指向所有整型矩阵元素的指针
	const int r, c;							//矩阵的行r和列c大小
public:
	MAT(int r, int c);						//矩阵定义
	MAT(const MAT& a);				//深拷贝构造
	MAT(MAT&& a)noexcept;			//移动构造
	virtual ~MAT()noexcept;
	virtual T* const operator[ ](int r);//取矩阵r行的第一个元素地址，r越界抛异常
	virtual MAT operator+(const MAT& a)const;	//矩阵加法，不能加抛异常
	virtual MAT operator-(const MAT& a)const;	//矩阵减法，不能减抛异常
	virtual MAT operator*(const MAT& a)const;	//矩阵乘法，不能乘抛异常
	virtual MAT operator~()const;					//矩阵转置
	virtual MAT& operator=(const MAT& a);		//深拷贝赋值运算
	virtual MAT& operator=(MAT&& a)noexcept;	//移动赋值运算
	virtual MAT& operator+=(const MAT& a);		//“+=”运算
	virtual MAT& operator-=(const MAT& a);		//“-=”运算
	virtual MAT& operator*=(const MAT& a);		//“*=”运算
//print输出至s并返回s：列用空格隔开，行用回车结束
	virtual char* print(char* s)const noexcept;
};
template MAT<int>;
template MAT<long long>;
int main(int argc, char* argv[]) 					//请扩展main()测试其他运算
{
	
	/*MAT<int>   a(1, 2), b(2, 2), c(1, 2);
	char t[2048];
	a[0][0] = 1;			//类似地初始化矩阵的所有元素
	a[0][1] = 2; 			//等价于“*(a.operator[ ](0)+1)=2;”即等价于“*(a[0]+1)=2;”
	a.print(t);			//初始化矩阵后输出该矩阵
	b[0][0] = 3; 	b[0][1] = 4;		//调用T* const operator[ ](int r)初始化数组元素
	b[1][0] = 5; 	b[1][1] = 6;
	b.print(t);
	c = a * b;						//测试矩阵乘法运算
	c.print(t);
	(a + c).print(t);					//测试矩阵加法运算
	c = c - a;						//测试矩阵减法运算
	c.print(t);
	c += a;							//测试矩阵“+=”运算
	c.print(t);
	c = ~a;							//测试矩阵转置运算
	c.print(t);*/
	int nmark = 0;
	const char* strResult = TestMAT(nmark);
	cout << "学号：U201814604" << endl;
	cout << "姓名：黄俊淇" << endl;
	cout << "实验四测试：" << strResult << ',' << nmark << endl;
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
	int column = a.c;//列
	int row = r;//行
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
	int column = a.c;//列
	int row = r;//行
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