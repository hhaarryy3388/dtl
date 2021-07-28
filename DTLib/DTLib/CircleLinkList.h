#ifndef CIRCLELINKLIST_H
#define CIRCLELINKLIST_H

#include "LinkList.h"

namespace DTLib {

// 视频中取名为: CircleList, 我觉得应该为: CircleLinkList 更加直观好记

template <typename T>
class CircleLinkList : public LinkList<T> {
    typedef typename LinkList<T>::Node Node;

protected:

    Node* last() const;
    void  last_to_first();
    int   mod(int i) const;
public:
    bool insert(int i, const T& e);
    bool insert(const T& e);
    bool remove(int i);
    bool set(int i, const T&e);
    bool get(int i, T& e) const;
    T    get(int i) const;
    int  find(const T& e);
    int  find(const Node* node);
    void clear();

    // 与游标相关
    bool move(int i, int step = 1); // 设置游标
    bool end();                     // 是否到了结尾


    ~CircleLinkList();
};

template <typename T>
int   CircleLinkList<T>::mod(int i) const {
    return (this->m_length == 0) ? 0:(i % this->m_length);
}

template <typename T>
typename LinkList<T>::Node* CircleLinkList<T>::last() const {
    return this->position(this->m_length-1)->next;
}

template <typename T>
void CircleLinkList<T>::last_to_first() {
    if ( this->m_length > 0 ) {
        last()->next = this->m_header.next;
    }
}

template <typename T>
bool CircleLinkList<T>::insert(int i, const T& e) {
    bool ret = true;

    i = i % (this->m_length + 1);       // i 的取值为 0 ~ m_length, m_length表示插在最后面
    ret = LinkList<T>::insert(i, e);
    if ( ret && i == 0 ) {
        last_to_first();
    }
    return ret;
}

template <typename T>
bool CircleLinkList<T>::insert(const T& e) {
    return insert(this->m_length, e);
}

template <typename T>
bool CircleLinkList<T>::remove(int i) {
    bool ret = true;

    typedef typename LinkList<T>::Node Node;

    i = mod(i);

    // 这里不能直接调用 "LinkList<T>::remove(i)"
    // 因为有可能抛出异常,而如果是删除的是第0号节点,此时可能会破坏循环链表
    if ( i == 0) {
        // 0号节点要细心处理
        Node* toDel = this->m_header.next;
        if ( toDel != nullptr ) {
            this->m_header.next = toDel->next;
            this->m_length--;
            if ( this->m_length > 0 ) {
                last_to_first();
                if ( this->m_current == toDel ) {
                    this->m_current = toDel->next;
                }
            }
            else {
                this->m_header.next = nullptr;
                this->m_current = nullptr;
            }

            this->destroy(toDel);

            ret = true;
        }
        else {
            ret = false;
        }
    }
    else {
        ret = LinkList<T>::remove(i);
    }
    return ret;
}

template <typename T>
bool CircleLinkList<T>::set(int i, const T&e) {
    return LinkList<T>::set(mod(i), e);     // 这里就是为了处理这个"mod(i)",所以要重写
}

template <typename T>
bool CircleLinkList<T>::get(int i, T& e) const {
    i = mod(i);
    return LinkList<T>::get(i, e);
}

template <typename T>
T CircleLinkList<T>::get(int i) const {
    i = this->mod(i);

    return LinkList<T>::get(i);
}

template <typename T>
int CircleLinkList<T>::find(const T& e) {
    int ret = -1;

    Node* slider = this->m_header.next;
    for (int i = 0; i < this->m_length;i++ ) {
        if (slider->value == e) {
            ret = i;
            break;
        }
        slider = slider->next;
    }
    return ret;
}

template <typename T>
int CircleLinkList<T>::find(const Node* node) {
    int ret = -1;

    Node* slider = this->m_header.next;
    for (int i = 0; i < this->m_length;i++ ) {
        if (slider == node) {
            ret = i;
            break;
        }
        slider = slider->next;
    }
    return ret;
}

template <typename T>
void CircleLinkList<T>::clear() {
    // 小心, 这里不能运用小聪明:
    //    1) 先变成单链表: last()->next = nullptr;
    //    2) 调用: LinkList<T>::clear
    // 原因: 可能会抛出异常,此时循环链表变成了单链表了...破坏了原始数据,用户怎么查bug???

    while ( this->m_length > 1 ) {
        // 这里去remove(1)，不会造成尾指针指向头指针的频繁操作
        remove(1);
    }
    if ( this->m_length == 1 ) {
        Node* toDel = this->m_header.next;

        this->m_header.next = nullptr;
        this->m_length = 0;
        this->m_current = nullptr;

        this->destroy(toDel);
    }

}


template <typename T>
bool CircleLinkList<T>::move(int i, int step) {
    i = mod(i);
    return LinkList<T>::move(i, step);
}

template <typename T>
bool CircleLinkList<T>::end() {
    return (this->m_length == 0 || this->m_current == nullptr);
}


template <typename T>
CircleLinkList<T>::~CircleLinkList() {
    clear();
}



} /* namespace */


#endif // CIRCLELINKLIST_H
