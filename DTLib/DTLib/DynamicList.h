#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "SeqList.h"
#include "Exception.h"

namespace DTLib {


template <typename T>
class DynamicList : public SeqList<T>
{
protected:
    int m_capacity;
public:
    DynamicList(int capacity);
    int capacity() const;
    void resize(int capacity);
    ~DynamicList();
};

template <typename T>
DynamicList<T>::DynamicList(int capacity) {
    this->m_array = new T[capacity];
    if ( this->m_array != nullptr ) {
        this->m_length = 0;
        this->m_capacity = capacity;
    }
    else {
        THROW_EXCEPTION(NoEnoughMemoryException, "No Memory to Create DynamicList object ...");
    }

}

template <typename T>
int DynamicList<T>::capacity() const {
    return m_capacity;
}

template <typename T>
void DynamicList<T>::resize(int capacity) {
    if ( capacity != m_capacity ) {
        T* arr = new T[capacity];
        if ( arr != nullptr ) {
            int size = (capacity < this->m_length) ? capacity : this->m_length;

            for ( int i = 0; i < size; i++ ) {
                arr[i] = this->m_array[i];
            }

            T* tmp = this->m_array;     // 这里不要直接 delete[] this->m_array; 容易抛出异常导致退出
            this->m_array = arr;
            this->m_length = size;
            this->m_capacity = capacity;

            delete [] tmp;
        }
        else {
            THROW_EXCEPTION(NoEnoughMemoryException, "No Memory to Resize DynamicList object...");
        }
    }
}

template <typename T>
DynamicList<T>::~DynamicList() {
    delete [] this->m_array;
}



} /* namespace */



#endif // DYNAMICLIST_H
