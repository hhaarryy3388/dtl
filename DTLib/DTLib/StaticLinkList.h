#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "LinkList.h"
#include "Exception.h"

namespace DTLib {


template <typename T, int N>
class StaticLinkList : public LinkList<T>
{
    typedef typename LinkList<T>::Node Node;

    // 因为需要重写"new"操作,所以需要一个size相同且继承自"Node"的类: SNode
    struct SNode : public Node {
    public:
        void* operator new(unsigned int size, void* loc) {
            (void)size;
            return loc;
        }
    };

    char m_space[sizeof(SNode)*N];
    int  m_used[N];

    Node* create();
    void  destroy(Node* pn);

public:
    StaticLinkList();
    ~StaticLinkList();

    int capacity();
};

template <typename T, int N>
StaticLinkList<T,N>::StaticLinkList() {
    for ( int i = 0; i < N; i++ ) {
        m_used[i] = 0;
    }
}

template <typename T, int N>
typename LinkList<T>::Node* StaticLinkList<T,N>::create() {
    SNode* ret = nullptr;
    for (int i = 0; i < N; i++ ) {
        if ( m_used[i] == 0 ) {
            ret = reinterpret_cast<SNode*>(m_space) + i;
            ret = new(ret) SNode();     // 在指定的地址"ret"上new出一个SNode对象
            m_used[i] = 1;
            break;
        }
    }

    // 注意: 这里不进行抛异常判断,因为在 LinkList 类中 调用 create()不能分配时 会抛出异常
    return ret;
}

template <typename T, int N>
void StaticLinkList<T,N>::destroy(typename LinkList<T>::Node* pn) {
    SNode* sd = reinterpret_cast<SNode*>(m_space);
    SNode* psn = dynamic_cast<SNode*>(pn);

    for ( int i = 0; i < N; i++ ) {
        if ( psn == (sd + i) ) {
            m_used[i] = 0;
            psn->~SNode();          // 虽然我们没有显示定义"析构函数",但是它还是存在的
            break;
        }
    }
}

template <typename T, int N>
int StaticLinkList<T,N>::capacity() {
    return N;
}

template <typename T, int N>
StaticLinkList<T,N>::~StaticLinkList() {
    this->clear();
}



} /* namespace */



#endif // STATICLINKLIST_H
