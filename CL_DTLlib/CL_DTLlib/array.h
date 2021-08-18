#ifndef ARRAY_H
#define ARRAY_H

#include "Object.h"
#include "Exception.h"

namespace DTLib {

template <typename T>
class Array : public Object
{
protected:
	T* m_array;			//数组长度
public:
	virtual bool set(int i, T& e);			//设置数组指定位置的值
	virtual bool get(int i, T& e) const;	//获取数组指定位置的值
	virtual int length() const = 0;			//获取数组长度

	T& operator[](int i);					//数组操作符号重载
	T  operator[](int i) const;				//数组本身是const时,数组操作符号重载

	T* array();
// // // };

template <typename T>
bool Array<T>::set(int i, T& e) {
	bool ret = (i >= 0 && i < length());

	if ( ret ) {
		m_array[i] = e;
	}
	return ret;
}

template <typename T>
bool Array<T>::get(int i, T& e) const {
	bool ret = (i >= 0 && i < length());

	if ( ret ) {
		e = m_array[i];
	}

	return ret;
}

template <typename T>
T& Array<T>::operator[](int i) {
	bool ret = (i >= 0 && i < length());

	if ( ret ) {
		return m_array[i];
	}
	else {
		//越界异常,访问数组的长度过界
		THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid...");
	}

}

template <typename T>
T  Array<T>::operator[](int i) const {
	return (const_cast<Array<T>&>(*this))[i];
}

template <typename T>
T* Array<T>::array() {
	return m_array;
}



}   /* namespace */


#endif // ARRAY_H

