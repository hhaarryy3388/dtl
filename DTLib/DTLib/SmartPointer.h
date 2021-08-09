#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include <iostream>
#include "Object.h"
#include "Pointer.h"

using namespace std;

namespace  DTLib {

template<typename T>
class SmartPointer : public Pointer<T> {
public:
    SmartPointer(T* p = nullptr);
    SmartPointer(const SmartPointer<T>& obj);
    SmartPointer& operator=(const SmartPointer<T>& obj);
    ~SmartPointer<T>();
};

template<typename T>
SmartPointer<T>::SmartPointer(T* p) : Pointer<T>(p)
{
    //cout << "SmartPointer(T* p)" << endl;
}

template<typename T>
SmartPointer<T>::SmartPointer(const SmartPointer<T>& obj) : Pointer<T>(nullptr) {
    //cout << "SmartPointer(const SmartPointer<T>& obj)" << endl;

    this->m_pointer = obj.m_pointer;
    const_cast<SmartPointer<T>&>(obj).m_pointer = nullptr;
}

template<typename T>
SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer<T>& obj) {
    //cout << "SmartPointer<T>::operator=" << endl;

    if ( obj != this ) {
        T* toDel = this->m_pointer;

        this->m_pointer = obj.m_pointer;

        const_cast<SmartPointer&>(obj).m_pointer = nullptr;

        delete toDel;       // 最后释放,防止抛出异常爆掉
    }
    return *this;
}

template<typename T>
SmartPointer<T>::~SmartPointer<T>() {
    delete this->m_pointer;
}



}


#endif // SMARTPOINTER_H
