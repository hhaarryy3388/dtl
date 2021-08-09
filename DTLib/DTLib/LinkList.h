#ifndef LINKLIST_H
#define LINKLIST_H

#include "Object.h"
#include "List.h"
#include "Exception.h"
//#include "SharedPointer.h"

namespace DTLib {

template <typename T>
class LinkList : public List<T>
{
protected:
    struct Node : public Object {
        T       value;
        Node*   next;
    };

    mutable struct : public Object {
        char    Reserved[sizeof(T)];
        Node*   next;
    } m_header;

    int m_length;                           // 当前链表中数据的个数

    // 为了增加遍历的速度,增加了游标的概念
    Node* m_current;                        // 游标: 指向当前一个有效的节点
    int m_step;                             // 游标移动的跨度

    Node* position(int pos) const ;         // 返回的 Node->next 指向的就是位置 pos 处的节点
public:
    LinkList();

    virtual bool insert(const T& e);
    virtual bool insert(int i, const T& e);
    virtual bool remove(int i);
    virtual bool set(int i, const T& e);
    virtual bool get(int i, T& e) const;
    virtual T    get(int i) const;
    virtual int  find(const T& e);                  // 返回:找到的序号; -1: 没有找到
    virtual int  find(const Node* node);            // 陈实增加的函数,在课程main()验证程序时,经常用 remove(find(current()))
                                                    // 其实删除的可能不是所想要删除的节点,比如:int链表里面有
                                                    // 几个节点的value是相同的,find将会晕菜...
    int  length() const;
    virtual void clear();

    // 与游标相关
    virtual bool move(int i, int step = 1); // 设置游标
    virtual bool next();                    // 游标下移
    virtual bool end();                     // 是否到了结尾
    virtual T     current();                // 返回当前游标指向的元素的值
    virtual Node* currentNode();            // 返回当前游标指向的节点的指针,配合前面增加的 find(Node*)

    virtual Node* create();
    virtual void destroy(Node* pn);

    // 陈实添加的两个函数
    T& operator[](int i);
    T  operator[](int i) const;

    virtual ~LinkList();
};

template <typename T>
LinkList<T>::LinkList() {
    m_header.next = nullptr;
    m_length = 0;
    m_step = 0;
    m_current = nullptr;
}

template <typename T>
typename LinkList<T>::Node* LinkList<T>::position(int pos) const {
    Node* pNext;

    // pos 的取值应该是 0 ~ length
    // 后面程序中经常用到 postion(length-1), 那么如果 length = 0 ? 所以...
    if ( pos < 0 ) {
        pos = 0;
    }

    pNext = reinterpret_cast<Node *>(&m_header);

    for (int i = 0; i < pos; i++) {
        pNext = pNext->next;
    }
    return pNext;
}

template <typename T>
bool LinkList<T>::insert(int i, const T& e) {
    bool ret;

    ret = (i >= 0) && (i <= m_length);
    if ( ret ) {
        Node* newNode = create();
        if ( newNode != nullptr ) {
            newNode->value = e;

            Node* current = position(i);
            newNode->next = current->next;
            current->next = newNode;

            m_length++;
        }
        else {
            THROW_EXCEPTION(NoEnoughMemoryException, "No Memorty for LinkList's insert...");
        }
    }
    else {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Index Out of Bounds for LinkList's insert...");
    }

    return ret;
}

template <typename T>
bool LinkList<T>::insert(const T& e) {
    return insert(m_length, e);
}

template <typename T>
bool LinkList<T>::remove(int i) {
    bool ret;

    ret = (i >= 0) && (i < m_length);
    if ( ret ) {
        Node* curNode = position(i);
        Node* toDel = curNode->next;    // 被删者
        curNode->next = toDel->next;

        // 此时游标有可能指向的是被删除的节点
        // 应用层调用remove()删除的是最后一个节点时,写程序要非常谨慎
        if ( m_current == toDel ) {
            m_current = toDel->next;
        }

        // 视频26课专门论述,下面要先"--",再来摧毁对象,防止某些类
        // 在析构中抛出异常,导致list的元素个数没有进行更新
        // 备注: Qt中不允许析构函数抛出异常!!!编译时就给封死.
        m_length--;
        destroy(toDel);
    }
    else {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Index Out of Bounds for LinkList's remove...");
    }

    return ret;
}

template <typename T>
bool LinkList<T>::set(int i, const T& e) {
    bool ret;

    ret = (i >= 0) && (i < m_length);
    if ( ret ) {
        Node* curNode = position(i);
        curNode->next->value = e;
    }
    else {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Index Out of Bounds for LinkList's set...");
    }

    return ret;
}

template <typename T>
bool LinkList<T>::get(int i, T& e) const {
    bool ret;

    ret = (i >= 0) && (i < m_length);
    if ( ret ) {
        Node* curNode = position(i);
        e = curNode->next->value;
    }

    return ret;
}

template <typename T>
T LinkList<T>::get(int i) const {
    T  e;

    if ( get(i, e) ) {
        return e;
    }
    else {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Index Out of Bounds for LinkList's get...");
    }
}

template <typename T>
int  LinkList<T>::find(const T& e) {
    int ret = -1;

    int i = 0;
    Node* nd = m_header.next;
    while ( nd != nullptr ) {
        if ( nd->value == e ) {
            ret = i;
            break;
        }
        else {
            nd = nd->next;
            i++;
        }
    }

    return ret;
}

template <typename T>
int  LinkList<T>::find(const typename LinkList<T>::Node* node) {
    int ret = -1;

    int i = 0;
    Node* nd = m_header.next;
    while ( nd != nullptr ) {
        if ( nd == node ) {
            ret = i;
            break;
        }
        else {
            nd = nd->next;
            i++;
        }
    }

    return ret;
}

template <typename T>
int LinkList<T>::length() const {
    return m_length;
}

template <typename T>
void LinkList<T>::clear() {
    Node* nd = reinterpret_cast<Node *>(&m_header);
    Node* pd;

    while ( nd->next != nullptr ) {
        pd = nd->next;

        nd->next = pd->next;

        // 这里的操作也是需要放在下面"destroy()"之前,防止摧毁的时候抛出异常
        m_length--;
        destroy(pd);
    }
    //m_length = 0;
}

template <typename T>
T& LinkList<T>::operator[](int i) {
    bool ret;

    ret = (i >= 0) && (i < m_length);
    if ( ret ) {
        Node* curNode = position(i);
        return curNode->next->value;
    }
    else {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Index Out of Bounds for LinkList's []...");
    }
}

template <typename T>
T  LinkList<T>::operator[](int i) const {
    return (const_cast<LinkList<T>&>(*this))[i];
}

template <typename T>
bool LinkList<T>::move(int i, int step) {
    bool ret = (i >= 0 && i < m_length && step > 0);

    if ( ret ) {
        m_current = position(i)->next;
        m_step = step;
    }

    return ret;
}

template <typename T>
bool LinkList<T>::next() {
    int i = 0;

    while ( i < m_step && !end() ) {
        m_current = m_current->next;
        i++;
    }

    return (i == m_step);
}

template <typename T>
bool LinkList<T>::end() {
    return (m_current == nullptr);
}

template <typename T>
T LinkList<T>::current() {
    if ( !end() ) {
        return m_current->value;
    }
    else {
        THROW_EXCEPTION(InvalidOperationException, "current() of LinkList ...");
    }
}

// 返回当前游标指向的节点的指针
template <typename T>
typename LinkList<T>::Node* LinkList<T>::currentNode() {
    return m_current;
}


template <typename T>
typename LinkList<T>::Node* LinkList<T>::create() {
    //return new Node();
    //return new LinkList<T>::Node();
    return new typename LinkList<T>::Node();

}

template <typename T>
void LinkList<T>::destroy(typename LinkList<T>::Node* pn) {
   delete pn;
}


template <typename T>
LinkList<T>::~LinkList() {
    clear();
}




} /* namespace */


#endif // LINKLIST_H
