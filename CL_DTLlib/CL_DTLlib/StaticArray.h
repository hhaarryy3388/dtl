#ifndef STATICARRAY_H
#define STATICARRAY_H

#include "Array.h"

namespace DTLib {

template <typename T, int N>
class StaticArray : public Array<T>
{
protected:
	T m_space[N];	//用模板的N来定义原生数组
public:
	StaticArray();

	StaticArray(const StaticArray<T,N>& obj);
	StaticArray<T,N>& operator=(const StaticArray<T,N>& obj);

	int length() const;
};

template <typename T, int N>
StaticArray<T,N>::StaticArray() {
	this->m_array = m_space;		//父类数组指针指向原生数组
}

//拷贝构造函数
template <typename T, int N>
StaticArray<T,N>::StaticArray(const StaticArray<T,N>& obj) {
	this->m_array = m_space;

	for ( int i = 0; i < N; i++ ) {
		m_space[i] = obj.m_space[i];
	}
}

//赋值操作费的重载函数
template <typename T, int N>
StaticArray<T,N>& StaticArray<T,N>::operator=(const StaticArray<T,N>& obj) {
	//排除自赋值操作
	if ( this != &obj ) {
		for ( int i = 0; i < N; i++ ) {
			m_space[i] = obj.m_space[i];
		}
	}
	return *this;
}

//返回数组长度
template <typename T, int N>
int StaticArray<T,N>::length() const {
	return N;
}


}


#endif // STATICARRAY_H
