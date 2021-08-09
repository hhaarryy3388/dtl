#ifndef POINTER_H
#define POINTER_H

#include "Object.h"

namespace DTLib {

template <typename T>
class Pointer : public Object
{
protected:
    T* m_pointer;
public:
    Pointer(T* p = nullptr);
    T* operator->();
    T& operator*();
    const T* operator->() const;
    const T& operator*() const;
    T* get() const;
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
