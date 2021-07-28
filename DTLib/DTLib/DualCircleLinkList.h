#ifndef DUALCIRCLELINKLIST_H
#define DUALCIRCLELINKLIST_H

#include "DualLinkList.h"

// 1) 本代码基于"CircleLinkList.h"进行修改
// 2) 本代码属于课程中的作业题
// 3) 稍微修改了几个类名,几乎没做代码修改
// 4) CircleLinkList 和 DualLinkList 有太多相同的代码, 应该进行继承处理
// 5) 和视频课程中双向循环链表相同的是"DualCycleLinkList.h"

namespace DTLib {


template <typename T>
class DualCircleLinkList : public DualLinkList<T> {
    typedef typename DualLinkList<T>::Node Node;

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
    //bool next();                    // 游标下移
    //bool pre();                     // 游标上移
    bool end();                     // 是否到了结尾


    ~DualCircleLinkList();
};

template <typename T>
int   DualCircleLinkList<T>::mod(int i) const {
    return (this->m_length == 0) ? 0:(i % this->m_length);
}

template <typename T>
typename DualLinkList<T>::Node* DualCircleLinkList<T>::last() const {
    return this->position(this->m_length-1)->next;
}

template <typename T>
void DualCircleLinkList<T>::last_to_first() {
    if ( this->m_length > 0 ) {
        last()->next = this->m_header.next;
    }
}

template <typename T>
bool DualCircleLinkList<T>::insert(int i, const T& e) {
    bool ret = true;

    i = i % (this->m_length + 1);       // i 的取值为 0 ~ m_length, m_length表示插在最后面
    ret = DualLinkList<T>::insert(i, e);
    if ( ret && i == 0 ) {
        last_to_first();
    }
    return ret;
}

template <typename T>
bool DualCircleLinkList<T>::insert(const T& e) {
    return insert(this->m_length, e);
}

template <typename T>
bool DualCircleLinkList<T>::remove(int i) {
    bool ret = true;

    typedef typename DualLinkList<T>::Node Node;

    i = mod(i);

    // 这里不能直接调用 "DualLinkList<T>::remove(i)"
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
        ret = DualLinkList<T>::remove(i);
    }
    return ret;
}

template <typename T>
bool DualCircleLinkList<T>::set(int i, const T&e) {
    return DualLinkList<T>::set(mod(i), e);     // 这里就是为了处理这个"mod(i)",所以要重写
}

template <typename T>
bool DualCircleLinkList<T>::get(int i, T& e) const {
    i = mod(i);
    return DualLinkList<T>::get(i, e);
}

template <typename T>
T DualCircleLinkList<T>::get(int i) const {
    i = this->mod(i);

    return DualLinkList<T>::get(i);
}

template <typename T>
int DualCircleLinkList<T>::find(const T& e) {
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
int  DualCircleLinkList<T>::find(const Node* node) {
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
void DualCircleLinkList<T>::clear() {
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
bool DualCircleLinkList<T>::move(int i, int step) {
    i = mod(i);
    return DualLinkList<T>::move(i, step);
}

/*
template <typename T>
bool DualCircleLinkList<T>::next() {
    int i = 0;

    while ( i < this->m_step && !end() ) {
        this->m_current = this->m_current->next;
        i++;
    }

    return (i == this->m_step);
}

template <typename T>
bool DualCircleLinkList<T>::pre() {
    int i = 0;

    while ( i < this->m_step && !end() ) {
        this->m_current = this->m_current->pre;
        i++;
    }

    return (i == this->m_step);
}
*/

template <typename T>
bool DualCircleLinkList<T>::end() {
    return (this->m_length == 0 || this->m_current == nullptr);
}

template <typename T>
DualCircleLinkList<T>::~DualCircleLinkList() {
    clear();
}





}   /* namespace */



#endif // DUALCIRCLELINKLIST_H
