#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include "BTreeNode.h"
#include "Tree.h"
#include "LinkList.h"
#include "Exception.h"
#include "LinkQueue.h"
#include "DynamicArray.h"

namespace DTLib {

enum BTNodePos {
    ANY,
    LEFT,
    RIGHT
};

enum BTTraversal {
    preOrder,
    inOrder,
    postOrder,
    levelOrder
};

template <typename T>
class BTree : public Tree<T>
{
protected:
    LinkQueue<BTreeNode<T>*> m_queue;

    virtual BTreeNode<T>* find(BTreeNode<T>* node, const T& value) const;
    virtual bool find(BTreeNode<T>* node, const BTreeNode<T>* obj) const;
    virtual void remove(BTreeNode<T>* node, BTree<T>* &ret);

    void free(BTreeNode<T>* node);
    int  count(BTreeNode<T>* node) const;
    int  height(BTreeNode<T>* node) const;
    int  degree(BTreeNode<T>* node) const;

    void preOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*> &queue);
    void inOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*> &queue);
    void postOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*> &queue);
    void levelOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*> &queue);

    BTreeNode<T>* clone(BTreeNode<T>* node) const;
    bool equal(BTreeNode<T>* ln, BTreeNode<T>* rn) const;
    BTreeNode<T>* add(BTreeNode<T>* ln, BTreeNode<T>* rn) const;

    void traversal(BTTraversal order, LinkQueue<BTreeNode<T>*> &queue);
    BTreeNode<T>* connect(LinkQueue<BTreeNode<T>*> &queue);
public:
    virtual bool insert(BTreeNode<T>* n, BTreeNode<T>* np, BTNodePos pos);
    virtual bool insert(const T& value, TreeNode<T>*parent, BTNodePos pos);
    bool insert(TreeNode<T>* node);
    bool insert(const T& value, TreeNode<T>* parent);

    SharedPointer<Tree<T>> remove(const T& value);
    SharedPointer<Tree<T>> remove(TreeNode<T>* node);

    BTreeNode<T>* find(const T& value) const;
    bool find(TreeNode<T>* node) const;
    BTreeNode<T>* root() const;
    int degree() const;
    int count() const;
    int height() const;
    void clear();

    // 遍历时的游标控制
    bool begin();
    bool end();
    bool next();
    T    current();

    SharedPointer<Array<T>> traversal(BTTraversal order);
    SharedPointer<BTree<T>> clone() const;

    bool operator == (BTree<T>& obj) const;
    bool operator != (BTree<T>& obj) const;

    SharedPointer<BTree<T>> add(const BTree<T>& bt) const;
    BTreeNode<T>* thread(BTTraversal order);        // 线索化

    BTree();
    ~BTree();
};

//-------------------------------------------------------------
template <typename T>
BTreeNode<T>* BTree<T>::find(BTreeNode<T>* node, const T& value) const {
    BTreeNode<T>* ret = nullptr;

    if ( node != nullptr ) {
        if ( node->value == value ) {
            ret = node;
        }
        else {
            if ( ret == nullptr ) {
                ret = find(node->left, value);
            }
            if ( ret == nullptr ) {
                ret = find(node->right, value);
            }
        }
    }

    return ret;
}

template <typename T>
bool BTree<T>::find(BTreeNode<T>* node, const BTreeNode<T>* obj) const {
    bool ret = false;

    if ( node == obj ) {
        ret = true;
    }
    else {
        if ( node != nullptr ) {
            ret = find(node->left, obj) || find(node->right, obj);
        }
    }

    return ret;
}

template <typename T>
void BTree<T>::remove(BTreeNode<T>* node, BTree<T>* &ret) {
    ret = new BTree<T>();

    if ( ret == nullptr ) {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree");
    }
    else {
        if ( node == root() ) {
            this->m_root = nullptr;
        }
        else {
            BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent);
            if ( parent->left == node ) {
                parent->left = nullptr;
            }
            else if ( parent->right == node ) {
                parent->right = nullptr;
            }
        }

        node->parent = nullptr;
        ret->m_root = node;
    }
}

template <typename T>
void BTree<T>::free(BTreeNode<T>* node) {
    if ( node != nullptr ) {
        free(node->left);
        free(node->right);

        if ( node->flag() ) {
            //std::cout << node->value << std::endl;
            delete node;
        }
        //else {
        //    cout << node->value << endl;
        //}
    }
}

template <typename T>
int BTree<T>::count(BTreeNode<T>* node) const {
    return (node == nullptr) ? 0 : (count(node->left) + count(node->right) + 1);
}

template <typename T>
int BTree<T>::height(BTreeNode<T>* node) const {
    int ret = 0;

    if ( node != 0 ) {
        int lh = height(node->left);
        int rh = height(node->left);

        ret = ((lh > rh) ? lh : rh) + 1;
    }

    return ret;
}

template <typename T>
int BTree<T>::degree(BTreeNode<T>* node) const {
    int ret = 0;

    if ( node != 0 ) {
        BTreeNode<T>* child[] = {node->left, node->right};
        ret = (!!node->left + !!node->right);

        for ( int i = 0; (ret < 2) && (i < 2); i++ ) {
            int d = degree(child[i]);
            if ( d > ret ) {
                ret = d;
            }
        }
    }

    return ret;
}

template <typename T>
void BTree<T>::preOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*> &queue) {
    if ( node != nullptr ) {
        queue.add(node);
        preOrderTraversal(node->left, queue);
        preOrderTraversal(node->right, queue);
    }
}

template <typename T>
void BTree<T>::inOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*> &queue) {
    if ( node != nullptr ) {
        inOrderTraversal(node->left, queue);
        queue.add(node);
        inOrderTraversal(node->right, queue);
    }
}

template <typename T>
void BTree<T>::postOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*> &queue) {
    if ( node != nullptr ) {
        postOrderTraversal(node->left, queue);
        postOrderTraversal(node->right, queue);
        queue.add(node);
    }
}

template <typename T>
void BTree<T>::levelOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*> &queue) {
    if ( node != nullptr ) {
        LinkQueue<BTreeNode<T>*> tmp;

        tmp.add(node);
        while ( tmp.length() > 0 ) {
            BTreeNode<T>* n = tmp.front();
            if ( n->left ) {
                tmp.add(n->left);
            }
            if ( n->right ) {
                tmp.add(n->right);
            }
            tmp.remove();
            queue.add(n);
        }
    }
}

template <typename T>
BTreeNode<T>* BTree<T>::clone(BTreeNode<T>* node) const {
    BTreeNode<T>* ret = nullptr;

    if ( node != nullptr ) {
        ret = BTreeNode<T>::newNode();

        if ( ret == nullptr ) {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create clone node...");
        }
        else {
            ret->value = node->value;
            ret->parent = node->parent;
            ret->left = clone(node->left);
            ret->right = clone(node->right);

            if ( ret->left != nullptr ) {
                ret->left->parent = ret;
            }
            if ( ret->right != nullptr ) {
                ret->right->parent = ret;
            }
        }
    }

    return ret;
}

template <typename T>
bool BTree<T>::equal(BTreeNode<T>* ln, BTreeNode<T>* rn) const {
    if ( ln == rn ) {
        return true;
    }
    else if ( (ln != nullptr) && (rn != nullptr) ) {
        return (ln->value == rn->value) && equal(ln->left, rn->left) && equal(ln->right, rn->right);
    }
    else {
        return false;
    }
}

template <typename T>
BTreeNode<T>* BTree<T>::add(BTreeNode<T>* ln, BTreeNode<T>* rn) const {
    BTreeNode<T>* ret = nullptr;

    if ( ln == nullptr && rn != nullptr ) {
        ret = clone(rn);
    }
    else if ( ln != nullptr && rn == nullptr ) {
        ret = clone(ln);
    }
    else if (ln != nullptr && rn != nullptr ) {
        ret = BTreeNode<T>::newNode();

        if ( ret != nullptr ) {
            ret->value = ln->value + rn->value;
            ret->left = add(ln->left, rn->left);
            ret->right = add(ln->right, rn->right);

            if ( ret->left ) {
                ret->left->parent = ret;
            }
            if ( ret->right ) {
                ret->right->parent = ret;
            }
        }
        else {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create node for add...");
        }
    }

    return ret;
}

template <typename T>
void BTree<T>::traversal(BTTraversal order, LinkQueue<BTreeNode<T>*> &queue) {
    if ( order == preOrder ) {
        preOrderTraversal(root(), queue);
    }
    else if ( order == inOrder ) {
        inOrderTraversal(root(), queue);
    }
    else if ( order == postOrder ) {
        postOrderTraversal(root(), queue);
    }
    else if ( order == levelOrder ) {
        levelOrderTraversal(root(), queue);
    }
    else {
        THROW_EXCEPTION(InvalidParameterException, "Invalid order parameter...");
    }
}

template <typename T>
BTreeNode<T>* BTree<T>::connect(LinkQueue<BTreeNode<T>*> &queue) {
    BTreeNode<T>* ret = nullptr;

    if ( queue.length() > 0 ) {
        ret = queue.front();
        BTreeNode<T>* slider = queue.front();
        slider->left = nullptr;
        queue.remove();

        while ( queue.length() > 0 ) {
            slider->right = queue.front();
            queue.front()->left = slider;
            slider = queue.front();
            queue.remove();
        }
        slider->right = nullptr;
    }

    return ret;
}
//-------------------------------------------------------------
template <typename T>
BTree<T>::BTree() {
}

template <typename T>
bool BTree<T>::insert(BTreeNode<T>* n, BTreeNode<T>* np, BTNodePos pos) {
    bool ret = false;

    if ( pos == ANY ) {
        if ( np->left == nullptr ) {
            np->left = n;
            ret = true;
        }
        else if ( np->right == nullptr ) {
            np->right = n;
            ret = true;
        }
    }
    else if ( pos == LEFT ) {
        if ( np->left == nullptr ) {
            np->left = n;
            ret = true;
        }
    }
    else if ( pos  == RIGHT ) {
        if ( np->right == nullptr ) {
            np->right = n;
            ret = true;
        }
    }

    // 这里从逻辑上讲,就应该加上下面的语句
    if ( ret ) {
        n->parent = np;
    }

    return ret;
}

// 视频中还定义了一个函数
// BTree<T>::insert(TreeNode<T>* node, BTNodePos pos);
// 我觉得已经没必要那么啰嗦了
template <typename T>
bool BTree<T>::insert(TreeNode<T>* node) {
    bool ret;

    if ( node == nullptr ) {
        THROW_EXCEPTION(InvalidParameterException, "Can not Insert a null node into BTree");
    }

    if ( root() == nullptr ) {
        this->m_root = node;
        node->parent = nullptr;
        ret = true;
    }
    else {
        if ( node->parent != nullptr && find(node->parent) ) {
            ret = insert(dynamic_cast<BTreeNode<T>*>(node), dynamic_cast<BTreeNode<T>*>(node->parent), ANY);
        }
        else {
            THROW_EXCEPTION(InvalidParameterException, "Invalid parent node for insert...");
        }
    }

    return ret;
}

template <typename T>
bool BTree<T>::insert(const T& value, TreeNode<T>*parent, BTNodePos pos) {
    bool    ret = true;
    BTreeNode<T>* node = BTreeNode<T>::newNode();

    if ( node != nullptr ) {
        if ( parent == nullptr ) {
            // parent指定为空, 那就是需要插入根节点,如果有数据,全清空
            clear();

            node->value = value;
            this->m_root = node;
            node->parent = nullptr;
        }
        else {
            node->value = value;
            node->parent = parent;

            ret = insert(node, dynamic_cast<BTreeNode<T>*>(parent), pos);
            if ( !ret ) {
                delete node;
            }
        }
    }
    else {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create node for insert...");
    }

    return ret;
}


template <typename T>
bool BTree<T>::insert(const T& value, TreeNode<T>* parent) {
    return insert(value, parent, ANY);
}

template <typename T>
SharedPointer<Tree<T>> BTree<T>::remove(const T& value) {
    BTree<T>* ret = nullptr;
    BTreeNode<T>* node = find(value);

    if ( node == nullptr ) {
        THROW_EXCEPTION(InvalidParameterException, "Can find node via value...");
    }
    else {
        remove(node, ret);
        m_queue.clear();
    }

    //return ret;
    return SharedPointer<Tree<T>>(ret);     // 这样写更加直白
}

template <typename T>
SharedPointer<Tree<T>> BTree<T>::remove(TreeNode<T>* node) {
    BTree<T>* ret = nullptr;

    if ( node == nullptr || !find(node) ) {
        THROW_EXCEPTION(InvalidParameterException, "Parameter node is invalid...");
    }
    else {
        remove(dynamic_cast<BTreeNode<T>*>(node), ret);
        m_queue.clear();
    }

    //return ret;
    return SharedPointer<Tree<T>>(ret);     // 这样写更加直白
}

template <typename T>
BTreeNode<T>* BTree<T>::find(const T& value) const {
    return find(root(), value );
}

template <typename T>
bool BTree<T>::find(TreeNode<T>* node) const {
    return find(root(), dynamic_cast<BTreeNode<T>*>(node) );
}

template <typename T>
BTreeNode<T>* BTree<T>::root() const {
    return dynamic_cast<BTreeNode<T>*>(this->m_root);
}

template <typename T>
int BTree<T>::degree() const {
    return degree(root());
}

template <typename T>
int BTree<T>::count() const {
    return count(root());
}

template <typename T>
int BTree<T>::height() const {
    return height(root());
}

template <typename T>
void BTree<T>::clear() {
    free(root());
    this->m_root = nullptr;
    m_queue.clear();
}


template <typename T>
bool BTree<T>::begin() {
    bool ret = (root() != nullptr);

    if ( ret ) {
        m_queue.clear();
        m_queue.add(root());
    }

    return ret;
}

template <typename T>
bool BTree<T>::end() {
    return (m_queue.length() == 0);
}

template <typename T>
bool BTree<T>::next() {
    bool ret = (m_queue.length() > 0);

    if (ret) {
        BTreeNode<T>* node = m_queue.front();
        m_queue.remove();

        if ( node->left ) {
            m_queue.add(node->left);
        }
        if ( node->right ) {
            m_queue.add(node->right);
        }
    }

    return ret;
}

template <typename T>
T BTree<T>::current() {
    if (!end()) {
        return m_queue.front()->value;
    }
    else {
        THROW_EXCEPTION(InvalidOperationException, "No value at current position...");
    }
}

template <typename T>
SharedPointer<Array<T>> BTree<T>::traversal(BTTraversal order) {
    DynamicArray<T>* ret = nullptr;

    LinkQueue<BTreeNode<T>*> queue;

    traversal(order, queue);

    ret = new DynamicArray<T>(queue.length());
    if ( ret == nullptr ) {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create return result for traversal...");
    }
    else {
        for ( int i = 0; i < ret->length(); i++, queue.remove() ) {
            ret->set(i, queue.front()->value);
        }
    }

    return ret;
}

template <typename T>
SharedPointer<BTree<T>> BTree<T>::clone() const {
    BTree<T>* ret = new BTree<T>();

    if (ret != nullptr) {
        ret->m_root = clone(root());
    }
    else {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to clone...");
    }

    return ret;
}

template <typename T>
bool BTree<T>::operator ==(BTree<T>& obj) const {
    return equal(root(), obj.root());
}

template <typename T>
bool BTree<T>::operator !=(BTree<T>& obj) const {
    return !(*this == obj);
}

template <typename T>
SharedPointer<BTree<T>> BTree<T>::add(const BTree<T>& bt) const {
    BTree<T>* ret = new BTree<T>();

    if ( ret != nullptr ) {
        ret->m_root = add(root(), bt.root());
    }
    else {
        THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create tree for add...");
    }

    return ret;
}

// 线索化
template <typename T>
BTreeNode<T>* BTree<T>::thread(BTTraversal order) {
    BTreeNode<T>* ret;
    LinkQueue<BTreeNode<T>*> queue;

    traversal(order, queue);
    ret = connect(queue);

    this->m_root = nullptr;
    m_queue.clear();

    return ret;
}

template <typename T>
BTree<T>::~BTree() {
    clear();
}



}

#endif // BTREE_H
