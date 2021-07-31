#ifndef STATICLIST_H
#define STATICLIST_H

#include "SeqList.h"


namespace DTLib
{

template <typename T, int N>
class StaticList : public SeqList<T>
{
protected:
	T m_space[N];	//顺序存储空间,N为模板参数
public:
	StaticList();	//指定父类成员的具体值
	int capacity() const;
};

template <typename T, int N>
StaticList<T, N>::StaticList()
{
	this->m_array = m_space;	//将list存储空间的指针指向一个具体的空间
	this->m_length = 0;			//线性表长度初始化为0
}

template <typename T, int N>
int StaticList<T, N>::capacity() const {
	return N;
}

}

#endif // STATICLIST_H
