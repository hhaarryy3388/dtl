#ifndef POINTER_H
#define POINTER_H

#include "Object.h"




namespace DTLib {

template <typename T>
class Pointer : public Object
{
protected:
    T* m_pointer;   /* 指针的值,也就是所用空间的地址 */
public:
    Pointer(T* p = nullptr);
    T* operator->();
    T& operator*();
    const T* operator->() const;    //const对象的操作
    const T& operator*() const;
    T* get() const;                 //const对象的操作,只读,所以不用重载普通对象的
    bool isNull();

    // 这里不需要再来定义纯虚的析构函数来声明是一个抽象类,
    // 因为继承自 Object 这个抽象类,不去实现这个析构函数就自动成为抽象类
};

template <typename T>
Pointer<T>::Pointer(T* p) {
    m_pointer = p;
}

template <typename T>
T* Pointer<T>::operator->() {
    return m_pointer;
}

template <typename T>
T& Pointer<T>::operator*() {
    return *m_pointer;
}

template <typename T>
const T* Pointer<T>::operator->() const {
    return m_pointer;
}

/* 重载对象的指针操作符"*"
 * 用引用的方式返回,外部操作这个引用(实际空间别名),智能指针指向的空间,也会改变
 */
template <typename T>
const T& Pointer<T>::operator*() const {
    return *m_pointer;
}


template <typename T>
T* Pointer<T>::get() const {
    return m_pointer;
}

template <typename T>
bool Pointer<T>::isNull() {
    return (m_pointer == nullptr);
}


} /* namespace */




#endif // POINTER_H
