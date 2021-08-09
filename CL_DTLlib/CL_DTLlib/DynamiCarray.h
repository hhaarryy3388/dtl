#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "array.h"
#include "Exception.h"

namespace DTLib {

template <typename T>
class DynamicArray : public Array<T>
{
protected:
	int m_length;

	T* copy(T* arr, int arr_len, int new_len);	//内部拷贝操作
	void init(T* arr, int len);					//内部初始化操作
	void update(T* arr, int len);				//内部更新操作
public:
	DynamicArray(int len = 0);

	DynamicArray(const DynamicArray<T>& obj);
	DynamicArray<T>& operator=(const DynamicArray<T>& obj);

	int length() const;
	void resize(int newLen);

	~DynamicArray();
};

//新申请的数组空间初始化
template <typename T>
void DynamicArray<T>::init(T* arr, int len) {
	//判断数组空间是否是空(申请失败),申请空间的操作放在构造函数中
	if ( arr != nullptr ) {
		this->m_array = arr;
		this->m_length = len;
	}
	else {
		//数组初始化,空间异常
		THROW_EXCEPTION(NoEnoughMemoryException, "No Memory for init of DynamicArray");
	}
}

//复制,新申请一个数组空间,并将老空间的数据复制到新空间中,返回新空间地址
template <typename T>
T* DynamicArray<T>::copy(T* arr, int arr_len, int new_len) {
	T* tmp_arr = new T[new_len];

	if ( tmp_arr != nullptr ) {
		int size = arr_len < new_len ? arr_len : new_len;
		for ( int i = 0; i < size; i++ ) {
			tmp_arr[i] = arr[i];
		}
	}
	return tmp_arr;
}

//更新数组,用新空间更新数组,老空间销毁
template <typename T>
void DynamicArray<T>::update(T* arr, int len) {
	if ( arr != nullptr ) {
		//异常安全,先修改指针指向新空间,再销毁老空间
		T* tmp = this->m_array;

		this->m_array = arr;
		this->m_length = len;

		delete[] tmp;
	}
	else {
		//没有空间进行更新数组
		THROW_EXCEPTION(NoEnoughMemoryException, "No Memory for update of DynamicArray");
	}
}

template <typename T>
DynamicArray<T>::DynamicArray(int len) {
	//申请空间,并初始化
	init(new T[len], len);
}

//拷贝构造函数
template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& obj) {
	T* arr = copy(obj.m_array, obj.m_length, obj.m_length); //将外部数组的数据复制到一个新的空间
	init(arr, obj.m_length);	//用新空间来初始化数组类属性
}

//赋值操作符重载函数
template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& obj) {
	//排除自己赋值自己的情况
	if ( this != &obj ) {
		T* arr = copy(obj.m_array, obj.m_length, obj.m_length);	//将外部数组的数据复制到一个新空间中
		update(arr, obj.m_length);	//用新空间来更新本数组
	}

	return *this;
}

//返回数组长度
template <typename T>
int DynamicArray<T>::length() const {
	return m_length;
}

//改变数组大小
template <typename T>
void DynamicArray<T>::resize(int newLen) {
	if ( m_length != newLen ) {
		T* arr = copy(this->m_array, m_length, newLen);	//将本数组的数据复制到一个新大小的空间中
		update(arr, newLen);	//用新空间来更新本数组
	}

}

//析构函数,销毁数组空间
template <typename T>
DynamicArray<T>::~DynamicArray() {
	delete[] this->m_array;
}



} /* namespace */

#endif // DYNAMICARRAY_H
