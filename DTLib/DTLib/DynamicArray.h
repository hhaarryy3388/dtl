#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Array.h"
#include "Exception.h"

namespace DTLib {

template <typename T>
class DynamicArray : public Array<T>
{
protected:
    int m_length;

    T* copy(T* arr, int arr_len, int new_len);
    void init(T* arr, int len);
    void update(T* arr, int len);
public:
    DynamicArray(int len = 0);

    DynamicArray(const DynamicArray<T>& obj);
    DynamicArray<T>& operator=(const DynamicArray<T>& obj);

    int length() const;
    void resize(int newLen);

    ~DynamicArray();
};

template <typename T>
void DynamicArray<T>::init(T* arr, int len) {
    if ( arr != nullptr ) {
        this->m_array = arr;
        this->m_length = len;
    }
    else {
        THROW_EXCEPTION(NoEnoughMemoryException, "No Memory for init of DynamicArray");
    }
}

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

template <typename T>
void DynamicArray<T>::update(T* arr, int len) {
    if ( arr != nullptr ) {
        T* tmp = this->m_array;

        this->m_array = arr;
        this->m_length = len;

        delete[] tmp;
    }
    else {
        THROW_EXCEPTION(NoEnoughMemoryException, "No Memory for update of DynamicArray");
    }
}

template <typename T>
DynamicArray<T>::DynamicArray(int len) {
    init(new T[len], len);
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& obj) {
    T* arr = copy(obj.m_array, obj.m_length, obj.m_length);
    init(arr, obj.m_length);
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& obj) {
    if ( this != &obj ) {
        T* arr = copy(obj.m_array, obj.m_length, obj.m_length);
        update(arr, obj.m_length);
    }

    return *this;
}

template <typename T>
int DynamicArray<T>::length() const {
    return m_length;
}

template <typename T>
void DynamicArray<T>::resize(int newLen) {
    if ( m_length != newLen ) {
        T* arr = copy(this->m_array, m_length, newLen);
        update(arr, newLen);
    }

}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] this->m_array;
}



} /* namespace */

#endif // DYNAMICARRAY_H
