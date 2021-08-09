#ifndef LINKSTACK_H
#define LINKSTACK_H

#include "Stack.h"
#include "LinkList.h"

namespace DTLib {

template <typename T>
class LinkStack : public Stack<T> {
protected:
    LinkList<T> m_list;
public:
    void push(const T& t);
    void pop();
    T    top() const;
    void clear();
    int  size() const;
};

template <typename T>
void LinkStack<T>::push(const T& t) {
    m_list.insert(0, t);
}

template <typename T>
void LinkStack<T>::pop() {
    if ( m_list.length() > 0 ) {
        m_list.remove(0);
    }
    else {
        THROW_EXCEPTION(InvalidOperationException, "no element to pop...");
    }
}

template <typename T>
T LinkStack<T>::top() const {
    if ( m_list.length() > 0 ) {
        return m_list.get(0);
    }
    else {
        THROW_EXCEPTION(InvalidOperationException, "no element to pop...");
    }
}

template <typename T>
void LinkStack<T>::clear() {
    m_list.clear();
}

template <typename T>
int LinkStack<T>::size() const {
    return m_list.length();
}







} /* namespace */



#endif // LINKSTACK_H
