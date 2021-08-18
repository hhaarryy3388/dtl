#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "LinkList.h"
#include "Exception.h"

namespace DTLib {


template <typename T, int N>
class StaticLinkList : public LinkList<T>
{
    //加typename是因为编译器不知道LinkList<T>::Node是LinkList的类型还是变量
    typedef typename LinkList<T>::Node Node;

    // 因为需要重写"new"操作,所以需要一个size相同且继承自"Node"的类: SNode
    struct SNode : public Node {
    public:
        void* operator new(unsigned int size, void* loc) {
            (void)size; //防止未使用报警
            return loc;
        }
    };

    char m_space[sizeof(SNode)*N];  //静态链表的空间
    int  m_used[N];                 //指定位置是否已经被使用

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
            ret = reinterpret_cast<SNode*>(m_space) + i;//在静态分配的内存上获取地址
            ret = new(ret) SNode();     // 在指定的地址"ret"上new出一个SNode对象
            m_used[i] = 1;              // 标记该位置可用
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
    //析构函数和构造函数不会多态调用,只会调用本类中的函数,
    this->clear();  //调用父类的clear,但是父类中调用的clear会调用destroy,析构不会多态,所以调用当前类的虚函数,也就是子类的destroy
}



} /* namespace */



#endif // STATICLINKLIST_H
