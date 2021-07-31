#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "seqlist.h"
#include "Exception.h"

namespace DTLib {


template <typename T>
class DynamicList : public SeqList<T>
{
protected:
	int m_capacity;				//顺序存储空间大小
public:
	DynamicList(int capacity);	//在构建函数中申请空间
	int capacity() const;		//获取空间占用大小
	void resize(int capacity);	//重置设置存储大小
	~DynamicList();				//在析构函数中归还空间
};

template <typename T>
DynamicList<T>::DynamicList(int capacity) {
	this->m_array = new T[capacity];	//父类存储空间指针指向新申请的存储空间
	//判断是否申请成功
	if ( this->m_array != nullptr ) {
		//申请成功就初始化线性表的大小和占用空间大小
		this->m_length = 0;
		this->m_capacity = capacity;
	}
	else {
		//申请失败
		THROW_EXCEPTION(NoEnoughMemoryException, "No Memory to Create DynamicList object ...");
	}

}

//获取顺序表占用空间大小
template <typename T>
int DynamicList<T>::capacity() const {
	return m_capacity;
}

//重置设置存储大小
template <typename T>
void DynamicList<T>::resize(int capacity) {
	if ( capacity != m_capacity ) {
		T* arr = new T[capacity];//申请新的空间
		if ( arr != nullptr ) {
			// 判断改变大小后,多少个数据可以保留
			int size = (capacity < this->m_length) ? capacity : this->m_length;

			for ( int i = 0; i < size; i++ ) {
				arr[i] = this->m_array[i];
			}
			// 这里不要直接 delete[] this->m_array; 容易抛出异常导致退出
			// delete的时候可能因为T的析构函数而导致异常,而让本函数中途调出,让后面的操作无法完成
			// this->m_array指向的地址就被破坏了,所以要先赋值再delete
			// delete [] this->m_array;
			T* tmp = this->m_array;
			this->m_array = arr;
			this->m_length = size;
			this->m_capacity = capacity;

			delete [] tmp;				//
		}
		else {
			THROW_EXCEPTION(NoEnoughMemoryException, "No Memory to Resize DynamicList object...");
		}
	}
}

template <typename T>
DynamicList<T>::~DynamicList() {
	delete [] this->m_array;	//释放之前申请的空间
}



} /* namespace */



#endif // DYNAMICLIST_H
