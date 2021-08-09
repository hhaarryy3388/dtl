#ifndef GTREENODE_H
#define GTREENODE_H

#include "TreeNode.h"
#include "LinkList.h"
#include <iostream>
#include <cstdio>
using namespace std;


namespace DTLib {


template<typename T>
class GTreeNode : public TreeNode<T>
{
public:
    LinkList<GTreeNode<T>*> child;

    static GTreeNode* newNode();

    //void operator delete(void *p);
};

template<typename T>
GTreeNode<T>* GTreeNode<T>::newNode() {
    GTreeNode<T>* node = new GTreeNode<T>();

    if ( node != nullptr ) {
        node->m_flag = true;
    }

    cout << "new obj =" << node << endl;
    return node;
}

/*
template<typename T>
void GTreeNode<T>::operator delete(void *p) {
    // 将它的子孙后代也统统删除
    GTreeNode<T>* node = reinterpret_cast<GTreeNode<T> *>(p);

    if ( node->child.length() != 0 ) {
        for ( node->child.move(0); !node->child.end(); node->child.next() ) {
            if ( node->child.current()->m_flag ) {
                GTreeNode<T>::operator delete (node->child.current());
            }
        }
    }

    if ( node->m_flag ) {
        cout << "delete obj =" << node->value << "," << node << endl;
        Object::operator delete(node);
    }
}
*/



}


#endif // GTREENODE_H
