#ifndef TREENODE_H
#define TREENODE_H

#include "Object.h"

namespace DTLib {

template<typename T>
class TreeNode : public Object
{
protected:
    bool    m_flag;

    // "封死"拷贝构造函数和赋值操作
    TreeNode(const TreeNode&);
    TreeNode& operator=(const TreeNode&);

    void* operator new(unsigned int size) noexcept;

public:
    T   value;
    TreeNode<T>* parent;

    TreeNode();
    virtual ~TreeNode() = 0;

    bool flag();
};

template<typename T>
TreeNode<T>::TreeNode() {
    parent = nullptr;
    m_flag = false;
}

template<typename T>
bool TreeNode<T>::flag() {
    return m_flag;
}


template<typename T>
void* TreeNode<T>::operator new(unsigned int size) noexcept {
    return Object::operator new(size);
}




template<typename T>
TreeNode<T>::~TreeNode() {
}


}   // namespace

#endif // TREENODE_H
