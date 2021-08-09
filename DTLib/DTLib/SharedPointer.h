#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include <cstdlib>
#include "Pointer.h"
#include "Exception.h"

namespace DTLib {

template <typename T>
class SharedPointer : public Pointer<T>
{
protected:
    int* m_ref;       // 计数机制

    void assign(const SharedPointer& obj);  // 辅助
public:
    SharedPointer(T* p = nullptr);
    SharedPointer(const SharedPointer& obj);
    SharedPointer& operator=(const SharedPointer& obj);
    void clear();
    ~SharedPointer();
};


template <typename T>
SharedPointer<T>::SharedPointer(T* p) : m_ref(nullptr) {
    this->m_pointer = p;

    if ( p ) {
        m_ref = static_cast<int*>(malloc(sizeof(int)));
        if ( m_ref ) {
            *m_ref = 1;
        }
        else {
            THROW_EXCEPTION(NoEnoughMemoryException, "No Memory for ShardPointer to create...");
        }
    }
}

template <typename T>
void SharedPointer<T>::assign(const SharedPointer& obj) {
    this->m_pointer = obj.m_pointer;
    m_ref = obj.m_ref;

    if ( m_ref ) {
        (*m_ref)++;
    }
}

template <typename T>
SharedPointer<T>::SharedPointer(const SharedPointer& obj) : Pointer<T>(nullptr) {
    assign(obj);
}

template <typename T>
SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer& obj) {
    if ( this != &obj ) {
        clear();
        assign(obj);
    }
    return *this;
}

template <typename T>
void SharedPointer<T>::clear() {
    T*   toDel = this->m_pointer;
    int* pRef = m_ref;

    if ( toDel ) {
        this->m_pointer = nullptr;
        m_ref = nullptr;

        if ( *pRef != 0 ) {
            (*pRef)--;
            if ( *pRef == 0 ) {
                free( pRef );
                delete toDel;
            }
        }
    }
}

template <typename T>
SharedPointer<T>::~SharedPointer() {
    clear();
}

template <typename T>
bool operator==(const SharedPointer<T>& l, const SharedPointer<T>& r ) {
    return (l.get() == r.get());
}

template <typename T>
bool operator!=(const SharedPointer<T>& l, const SharedPointer<T>& r ) {
    return (l.get() != r.get());
}

} /* namespace */


#endif // SHAREDPOINTER_H
