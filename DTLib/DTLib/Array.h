#ifndef ARRAY_H
#define ARRAY_H

#include "Object.h"
#include "Exception.h"

namespace DTLib {

template <typename T>
class Array : public Object
{
protected:
    T* m_array;
public:
    virtual bool set(int i, T& e);
    virtual bool get(int i, T& e) const;
    virtual int length() const = 0;

    T& operator[](int i);
    T  operator[](int i) const;

    T* array();
};

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
