#ifndef BTREENODE_H
#define BTREENODE_H

#include "TreeNode.h"

namespace DTLib {

template<typename T>
class BTreeNode : public TreeNode<T> {
public:
    BTreeNode* left;
    BTreeNode* right;

    static BTreeNode* newNode();

    BTreeNode();
};


template<typename T>
BTreeNode<T>* BTreeNode<T>::newNode() {
    BTreeNode<T>* node = new BTreeNode<T>();

    if ( node != nullptr ) {
        node->m_flag = true;
    }

    return node;
}

template<typename T>
BTreeNode<T>::BTreeNode() {
    left = nullptr;
    right = nullptr;
}



}



#endif // BTREENODE_H
