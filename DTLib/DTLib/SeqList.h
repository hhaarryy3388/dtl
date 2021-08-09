#ifndef SEQLIST_H
#define SEQLIST_H

#include "List.h"
#include "Exception.h"

namespace DTLib {


template <typename T>
class SeqList : public List<T>
{
protected:
    T*  m_array;
    int m_length;
public:
    bool insert(const T& e);
    bool insert(int i, const T& e);
    bool remove(int i);
    bool set(int i, const T& e);
    bool get(int i, T& e) const;
    int  find(const T& e);
    int  length() const;
    void clear();

    T& operator[](int i);
    T  operator[](int i) const;

    virtual int capacity() const = 0;
};

template <typename T>
bool SeqList<T>::insert(int i, const T& e) {
    bool ret = ( (i >= 0) && (i <= m_length) );
    ret = ret && (m_length < capacity());

    if ( ret ) {
        int j = m_length - 1;
        while ( j >= i ) {
            m_array[j+1] = m_array[j];
            j--;
        }
        m_array[i] = e;
        m_length++;
    }

    return ret;
}

template <typename T>
bool SeqList<T>::insert(const T& e) {
    return insert(m_length, e);
}

template <typename T>
bool SeqList<T>::remove(int i) {
    bool ret = ( (i >= 0) && (i < m_length) );

    if ( ret ) {
        while ( i < m_length ) {
            m_array[i] = m_array[i+1];
            i++;
        }
        m_length--;
    }

    return ret;
}

template <typename T>
bool SeqList<T>::set(int i, const T& e) {
    bool ret = ( (i >= 0) && (i < m_length) );

    if ( ret ) {
        m_array[i] = e;
    }
    return ret;
}

template <typename T>
bool SeqList<T>::get(int i, T& e) const {
    bool ret = ( (i >= 0) && (i < m_length) );

    if ( ret ) {
        e = m_array[i];
    }
    return ret;
}

template <typename T>
int  SeqList<T>::find(const T& e) {
    int ret = -1;

    for ( int i = 0; i < m_length; i++ ) {
        if ( m_array[i] == e ) {
            ret = i;
            break;
        }
    }

    return ret;
}

template <typename T>
int SeqList<T>::length() const {
    return m_length;
}

template <typename T>
void SeqList<T>::clear() {
    m_length = 0;
}

template <typename T>
T& SeqList<T>::operator[](int i) {
    bool ret = ( (i >= 0) && (i < m_length) );

    if ( ret ) {
        return m_array[i];
    }
    else {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid...");
    }
}

template <typename T>
T  SeqList<T>::operator[](int i) const {
    return (const_cast<SeqList<T> &>(*this))[i];
}


}   /* namespace */

#endif // SEQLIST_H
