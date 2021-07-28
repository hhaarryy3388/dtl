#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include "Queue.h"
#include "Exception.h"
#include "LinuxList.h"

// -------------------------------------------------------------------------
// 这里使用了Linux中的技术,但是这里用了模板类技术,是会有警告的
//      #define container_of(ptr, type, member) \
//            (reinterpret_cast<type *>(reinterpret_cast<char *>(ptr) - offsetof(type,member)))
// 如果type是一个类名,使用"reinterpret_cast"就会有警告的
//
// 具体应用在76课左右:
//      DynamicArray<T>* Graph<V,E>::toArray(LinkQueue<T>& queue) {
//          ...
//      }
// 形参是: LinkQueue<T>& queue
//
// main.c测试代码中调用:
//      SharedPointer<Array<Edge<int>>> sa = g.prim(0, false);
// 此时 LinkQueue<T> 中的T为: Edge<int>, 是一个模板类, 代码中展开会去调用 container_of, 警告就会到来:
//  warning: offsetof within non-standard-layout type 'DTLib::LinkQueue<DTLib::Edge<int> >::Node'
//  is undefined [-Winvalid-offsetof]
//         delete list_entry(toDel, Node, head);
//                                ^
//  具体原因就是用了"reinterpret_cast"修饰一个非标准类型...
// -------------------------------------------------------------------------
// 所以: 本文代码仅仅作为练习技术使用,不能作为真正的开放式代码库...
// -------------------------------------------------------------------------

namespace DTLib {

template <typename T>
class LinkQueue : public Queue<T> {
protected:
    struct Node {
        list_head   head;
        T           value;
    };
    list_head   m_header;
    int         m_length;

public:
    LinkQueue();
    ~LinkQueue();

    void add(const T& t);
    void remove();
    T    front() const;
    void clear();
    int  length() const;
};

template <typename T>
LinkQueue<T>::LinkQueue() {
    m_length = 0;
    INIT_LIST_HEAD(&m_header);
}


template <typename T>
void LinkQueue<T>::add(const T& t) {
    Node* node = new Node;

    if ( node != nullptr ) {
        node->value = t;
        m_length++;
        list_add_tail(&node->head, &m_header);
    }
    else {
        THROW_EXCEPTION(InvalidOperationException, "No memory to add new element...");
    }
}

template <typename T>
void LinkQueue<T>::remove() {
    if ( m_length > 0 ) {
        list_head* toDel = m_header.next;
        list_del(toDel);
        m_length--;     // 这里要放在下面delete之前,防止抛出异常
        delete list_entry(toDel, Node, head);
    }
    else {
        THROW_EXCEPTION(InvalidOperationException, "No element in current queue...");
    }
}

template <typename T>
T LinkQueue<T>::front() const {
    if ( m_length > 0 ) {
        return list_entry(m_header.next, Node, head)->value;
    }
    else {
        THROW_EXCEPTION(InvalidOperationException, "No element in current queue...");
    }
}

template <typename T>
void LinkQueue<T>::clear() {
    while ( m_length > 0 ) {
        remove();
    }
}

template <typename T>
int LinkQueue<T>::length() const {
    return m_length;
}

template <typename T>
LinkQueue<T>::~LinkQueue() {
    clear();
}



}   /* namespace */


#endif // LINKQUEUE_H
