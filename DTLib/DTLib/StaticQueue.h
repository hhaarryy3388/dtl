#ifndef STATICQUEUE_H
#define STATICQUEUE_H

#include "Queue.h"
#include "Exception.h"

namespace DTLib {

template <typename T, int N>
class StaticQueue : public Queue<T> {
protected:
    T m_space[N];
    int m_front;
    int m_rear;
    int m_length;
public:
    StaticQueue();
    int Capacity();

    void add(const T& t);
    void remove();
    T front() const;
    void clear();
    int length() const;
};

template <typename T, int N>
StaticQueue<T,N>::StaticQueue() {
    m_front = 0;
    m_rear = 0;
    m_length = 0;
}


template <typename T, int N>
int StaticQueue<T,N>::Capacity() {
    return m_length;
}

template <typename T, int N>
void StaticQueue<T,N>::add(const T& t) {
    if ( m_length < N ) {
        m_space[m_rear] = t;
        m_rear = (m_rear + 1) % N;
        m_length++;
    }
    else {
        THROW_EXCEPTION(InvalidOperationException, "No space in current queue...");
    }
}

template <typename T, int N>
void StaticQueue<T,N>::remove() {
    if ( m_length > 0 ) {
        m_front = (m_front+1) % N;
        m_length--;
    }
    else {
        THROW_EXCEPTION(InvalidOperationException, "No element in current queue...");
    }
}

template <typename T, int N>
T StaticQueue<T,N>::front() const {
    if ( m_length > 0 ) {
        return m_space[m_front];
    }
    else {
        THROW_EXCEPTION(InvalidOperationException, "No element in current queue...");
    }
}

template <typename T, int N>
void StaticQueue<T,N>::clear() {
    m_front = 0;
    m_rear = 0;
    m_length = 0;
}

template <typename T, int N>
int StaticQueue<T,N>::length() const {
    return m_length;
}






} /* namespace */



#endif // STATICQUEUE_H
