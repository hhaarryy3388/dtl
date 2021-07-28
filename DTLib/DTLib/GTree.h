#ifndef GTREE_H
#define GTREE_H

#include "GTreeNode.h"
#include "Tree.h"
#include "LinkList.h"
#include "Exception.h"
#include "LinkQueue.h"
//#include <iostream>
//using namespace std;

namespace DTLib {

template <typename T>

class GTree : public Tree<T>
{

protected:
    LinkQueue<GTreeNode<T>*> m_queue;

    GTreeNode<T>* find(GTreeNode<T>* node, const T& value) const;
    bool find(GTreeNode<T>* node, GTreeNode<T>* obj) const;
    void free(GTreeNode<T>* node);
    void remove(GTreeNode<T>* node, GTree<T>* &ret);
    int  count(GTreeNode<T>* node) const;
    int  height(GTreeNode<T>* node) const;
    int  degree(GTreeNode<T>* node) const;
public:
    GTree();

    bool insert(TreeNode<T>* node);
    bool insert(const T& value, TreeNode<T>* parent);

    SharedPointer<Tree<T>> remove(const T& value);
    SharedPointer<Tree<T>> remove(TreeNode<T>* node);

    GTreeNode<T>* find(const T& value) const;
    bool find(TreeNode<T>* node) const;

    GTreeNode<T>* root() const;
    int degree() const;
    int count() const;
    int height() const;
    void clear();

    // 遍历时的游标控制
    bool begin();
    bool end();
    bool next();
    T    current();

    ~GTree();


};

//-------------------------------------------------------------------------
// private member function
//-------------------------------------------------------------------------
template <typename T>
GTreeNode<T>* GTree<T>::find(GTreeNode<T>* node, const T& value) const {
    GTreeNode<T>* ret = nullptr;

    if ( node != nullptr ) {
        if ( node->value == value ) {
            return node;
        }
        else {
            for ( node->child.move(0); !node->child.end() && !ret; node->child.next() ) {
                ret = find(node->child.current(), value);
            }

        }
    }

    return ret;
}

template <typename T>
bool GTree<T>::find(GTreeNode<T>* node, GTreeNode<T>* obj) const {
    bool ret = false;

    if ( node == obj ) {
        return true;
    }

    if ( node != nullptr ) {
        if ( node == obj ) {
            ret = true;
        }
        else {
            for ( node->child.move(0); !node->child.end() && !ret; node->child.next() ) {
                ret = find(node->child.current(), obj);
            }
        }
    }

    return ret;

}

template <typename T>
void GTree<T>::free(GTreeNode<T>* node) {
    if ( node != nullptr ) {
        for (node->child.move(0); !node->child.end(); node->child.next() ) {
            free(node->child.current());
        }

        if ( node->flag() ) {
            delete node;
        }
        //else {
        //    cout << node->value << endl;
        //}
    }
}

template <typename T>
void GTree<T>::remove(GTreeNode<T>* node, GTree<T>* &ret) {
    ret = new GTree<T>();

    if ( ret == nullptr) {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to creat new tree...");
    }
    else {
        if ( node == root() ) {
            this->m_root = nullptr;
        }
        else {
            LinkList<GTreeNode<T>*>& child = dynamic_cast<GTreeNode<T>*>(node->parent)->child;
            child.remove(child.find(node));
            node->parent = nullptr;
        }

        ret->m_root = node;
    }
}

template <typename T>
int GTree<T>::count(GTreeNode<T>* node) const
{
    int ret = 0;

    if ( node != nullptr ) {
        ret = 1;

        for ( node->child.move(0); !node->child.end(); node->child.next() ) {
            ret += count(node->child.current());
        }
    }

    return ret;

}

template <typename T>
int GTree<T>::height(GTreeNode<T>* node) const {
    int ret = 0;

    if ( node != nullptr ) {
        for ( node->child.move(0); !node->child.end(); node->child.next() ) {
            int h = height(node->child.current());
            if ( h > ret ) {
                ret = h;
            }
        }
        ret += 1;

    }

    return ret;
}

template <typename T>
int GTree<T>::degree(GTreeNode<T>* node) const {
    int ret = 0;

    if ( node != nullptr ) {
        ret = node->child.length();
        ret = ret == 0 ? 1 : ret;   // 度的最小值至少也为1,否则如果child数为0,算出来的度为0,不合理!!!

        for ( node->child.move(0); !node->child.end(); node->child.next() ) {
            int h = degree(node->child.current());
            if ( h > ret ) {
                ret = h;
            }
        }

    }

    return ret;
}

//-------------------------------------------------------------------------
template <typename T>
GTree<T>::GTree() {
}


template <typename T>
bool GTree<T>::insert(TreeNode<T>* node) {
    bool ret = false;

    if ( node != nullptr ) {
        if ( this->m_root ) {
            GTreeNode<T>* parent = dynamic_cast<GTreeNode<T>*>(node->parent);
            if ( find(parent) ) {             // 这个是在整棵树中找"待插入节点:node"的父节点
                GTreeNode<T>* n = dynamic_cast<GTreeNode<T>*>(node);
                if ( parent->child.find(n) < 0 ) {   // 这个是在child这个"LinkList"的链条里面找是否已经存在"node"
                    parent->child.insert(n);
                    ret = true;
                }
            }
            else {
                THROW_EXCEPTION(InvalidParameterException, "Invalid parent node");
            }
        }
        else {
            this->m_root = node;
            node->parent = nullptr;
            ret = true;
        }
    }
    else {
        THROW_EXCEPTION(InvalidParameterException, "insert tree with a null node ...");
    }
    return ret;
}

template <typename T>
bool GTree<T>::insert(const T& value, TreeNode<T>* parent) {
    bool ret = true;

    GTreeNode<T> * node = GTreeNode<T>::newNode();

    if ( node ) {
        if ( find(parent) ) {
            node->parent = parent;
            node->value = value;

            insert(node);
        }
        else {
            delete node;
            ret = false;
        }
    }
    else {
        THROW_EXCEPTION(NoEnoughMemoryException, "No enought memroy to insert new node ...");
    }

    return ret;
}

template <typename T>
SharedPointer<Tree<T>> GTree<T>::remove(const T& value) {
    GTree<T>* ret = nullptr;
    GTreeNode<T>* node = find(value);

    if ( node == nullptr ) {
        THROW_EXCEPTION(InvalidParameterException, "Can not find the node by parameter...");
    }
    else {
        remove(node, ret);
        m_queue.clear();
    }

    //return ret;                           // 课程中的写法
    return SharedPointer<Tree<T>>(ret);     // 更容易理解的写法
}

template <typename T>
SharedPointer<Tree<T>> GTree<T>::remove(TreeNode<T>* node) {
    GTree<T>* ret = nullptr;

    if ( !find(node) ) {
        THROW_EXCEPTION(InvalidParameterException, "Parameter node is invalid...");
    }
    else {
        remove(dynamic_cast<GTreeNode<T>*>(node), ret);
        m_queue.clear();
    }

    //return ret;                           // 课程中的写法
    return SharedPointer<Tree<T>>(ret);     // 更容易理解的写法
}

template <typename T>
GTreeNode<T>* GTree<T>::find(const T& value) const {
    return find(root(), value);
}

template <typename T>
bool GTree<T>::find(TreeNode<T>* node) const {
    return find(root(), dynamic_cast<GTreeNode<T>*>(node));
}

template <typename T>
GTreeNode<T>* GTree<T>::root() const {
    return dynamic_cast<GTreeNode<T>*>(this->m_root);
}

template <typename T>
int GTree<T>::degree() const {
    return degree(root());
}

template <typename T>
int GTree<T>::count() const {
    return count(root());
}

template <typename T>
int GTree<T>::height() const {
    return height(root());
}

template <typename T>
void GTree<T>::clear() {
    free(root());
    this->m_root = nullptr;

    m_queue.clear();
}

template <typename T>
bool GTree<T>::begin() {
    bool ret = (root() != nullptr);

    if ( ret ) {
        m_queue.clear();
        m_queue.add(root());
    }

    return ret;
}

template <typename T>
bool GTree<T>::end() {
    return (m_queue.length() == 0);
}

template <typename T>
bool GTree<T>::next() {
    bool ret = (m_queue.length() > 0);

    if (ret) {
        GTreeNode<T>* node = m_queue.front();
        m_queue.remove();
        for ( node->child.move(0); !node->child.end(); node->child.next() ) {
            m_queue.add(node->child.current());
        }
    }

    return ret;
}

template <typename T>
T GTree<T>::current() {
    if (!end()) {
        return m_queue.front()->value;
    }
    else {
        THROW_EXCEPTION(InvalidOperationException, "No value at current position...");
    }
}

template <typename T>
GTree<T>::~GTree() {
    clear();
}





}





#endif // GTREE_H
