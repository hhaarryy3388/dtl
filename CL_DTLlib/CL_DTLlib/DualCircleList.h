#ifndef DUALCYCLELINKLIST_H
#define DUALCYCLELINKLIST_H

// 1) 本代码作为双向循环链表,和视频课程中同样风格
//      采用linux中的list技术
// 2) 视频中取名为: DualCircleList.h
//    本文件取名  : DualCycleLinkList.h
//    本库中还有另一个双向循环链表的实现:  DualCircleLinkList.h

#include "LinuxList.h"
#include "DualLinkList.h"

namespace DTLib {


template <typename T>
class DualCycleLinkList : public DualLinkList<T> {
protected:
	// 下面定义"struct Node"的代码,不要让它继承
	// 否则调用宏"list_entry()"会出一堆警告
	// 因为继承object,会继承
	//struct Node : public Object {     // 视频中的写法
	struct Node {                       // 我的写法
		list_head head;
		T value;
	};

	// linux下的list链表中,头结点是作为正常数据节点使用的
	// 而我们这里头结点要仅仅起到定位作用,所以在寻址和计算的时候
	// 要认为丢弃头结点
	list_head m_header;
	list_head *m_current;

	list_head* position(int i) const ;
	int   mod(int i) const;
public:
	DualCycleLinkList();

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
	bool next();                    // 游标下移
	bool pre();                     // 游标上移
	bool end();                     // 是否到了结尾

	T     current();                // 返回当前游标指向的元素的值

	// 下面这个自制的函数就不能再定义了,因为父类中有同名函数,但是两个类中的"Node"
	// 没有半毛钱关系了,如果去实现会提示错误
	//Node* currentNode();            // 返回当前游标指向的节点的指针,配合前面增加的 find(Node*)

	~DualCycleLinkList();
};

template <typename T>
DualCycleLinkList<T>::DualCycleLinkList() {
	this->m_length = 0;
	this->m_step = 1;

	m_current = nullptr;

	INIT_LIST_HEAD(&m_header);
}

template <typename T>
list_head* DualCycleLinkList<T>::position(int i) const {
	list_head* ret;

	// 1) position(i)返回的是指向第i个节点的指针
	// 2) 这里需要限定一下i的值,因为是双链表,且需要将头结点"m_header"忽视
	//    linuxList.h中的链条是包含了"m_header"在一条完整的双向链条中
	//    而我们这里的应用是想要人为故意去忽略"m_header",为的是保持和
	//    LinkList.h中逻辑设计思路一致！！！
	i = i % (this->m_length + 1);   // 备注: 视频中没有这句代码

	ret = const_cast<list_head*>(&m_header);
	for ( int p = 0; p < i; p++ ) {
		ret = ret->next;
	}

	return ret;
}

template <typename T>
int   DualCycleLinkList<T>::mod(int i) const {
	return (this->m_length == 0) ? 0:(i % this->m_length);
}

template <typename T>
bool DualCycleLinkList<T>::insert(int i, const T& e) {
	bool ret = true;

	Node* node = new Node;

	i = i % (this->m_length + 1);       // i 的取值为 0 ~ m_length, m_length表示插在最后面

	if ( node != nullptr ) {
		node->value = e;
		list_add_tail(&node->head, position(i)->next);
		this->m_length++;
	}
	else {
		THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to insert new element...");
	}

	return ret;
}

template <typename T>
bool DualCycleLinkList<T>::insert(const T& e) {
	return insert(this->m_length, e);
}

template <typename T>
bool DualCycleLinkList<T>::remove(int i) {
	bool ret = true;

	i = mod(i);

	ret = ((0 <= i) && (i < this->m_length));
	if (ret) {
		list_head* toDel = position(i)->next;
		if ( m_current == toDel ) {
			m_current = m_current->next;
		}
		list_del(toDel);
		this->m_length--;
		delete list_entry(toDel, Node, head);
	}

	return ret;
}

template <typename T>
bool DualCycleLinkList<T>::set(int i, const T&e) {
	bool ret = true;

	i = mod(i);
	ret = ( (0 <= i) && (i < this->m_length) );
	if (ret) {
		list_entry(position(i)->next, Node, head)->value = e;
	}

	return ret;
}

template <typename T>
bool DualCycleLinkList<T>::get(int i, T& e) const {
	bool ret = true;

	i = mod(i);
	ret = ( (0 <= i) && (i < this->m_length) );
	if ( ret ) {
		e = list_entry(position(i)->next, Node, head)->value;
	}
	return ret;
}

template <typename T>
T DualCycleLinkList<T>::get(int i) const {
	T ret;

	if ( get(i, ret) ) {
		return ret;
	}
	else {
		THROW_EXCEPTION(IndexOutOfBoundsException, "Invalid parameter i to get element...");
	}
}

template <typename T>
int DualCycleLinkList<T>::find(const T& e) {
	int ret = -1;
	int i = 0;

	list_head* slider = nullptr;

	list_for_each(slider, &m_header) {
		if (list_entry(slider, Node, head)->value == e ) {
			ret = i;
			break;
		}
		i++;
	}

	return ret;
}

template <typename T>
int  DualCycleLinkList<T>::find(const Node* node) {
	int ret = -1;
	int i = 0;

	list_head* slider = nullptr;

	list_for_each(slider, &m_header) {
		if (list_entry(slider, Node, head) == node ) {
			ret = i;
			break;
		}
		i++;
	}

	return ret;
}

template <typename T>
void DualCycleLinkList<T>::clear() {
	while ( this->m_length > 0 ) {
		remove( 0 );
	}
}

template <typename T>
bool DualCycleLinkList<T>::move(int i, int step) {
	bool ret = (step > 0);

	i = mod(i);

	ret = ret && ((0 <= i) && (i < this->m_length));

	if (ret) {
		m_current = position(i)->next;
		this->m_step = step;
	}

	return ret;
}

template <typename T>
bool DualCycleLinkList<T>::next() {
	int i = 0;

	while ( i < this->m_step && !end() ) {
		// 忽视且略过头结点
		if ( this->m_current != &m_header ) {
			i++;
		}
		this->m_current = this->m_current->next;

		if ( this->m_current == &m_header ) {
			this->m_current = this->m_current->next;
		}

	}

	return (i == this->m_step);
}

template <typename T>
bool DualCycleLinkList<T>::pre() {
	int i = 0;

	while ( i < this->m_step && !end() ) {
		// 忽视且略过头结点
		if ( this->m_current != &m_header ) {
			i++;
		}
		this->m_current = this->m_current->prev;

		if ( this->m_current == &m_header ) {
			this->m_current = this->m_current->prev;
		}

	}

	return (i == this->m_step);
}

template <typename T>
bool DualCycleLinkList<T>::end() {
	return (this->m_length == 0 || this->m_current == nullptr);
}

template <typename T>
T DualCycleLinkList<T>::current() {
	typedef DualCycleLinkList<T>::Node Node;
	if ( !end() ) {
		return list_entry(m_current, Node, head)->value;
	}
	else {
		THROW_EXCEPTION(InvalidOperationException, "No value at current position ...");
	}
}

/*
// 返回当前游标指向的节点的指针
template <typename T>
typename DualCycleLinkList<T>::Node* DualCycleLinkList<T>::currentNode() {
	return list_entry(m_current, Node, head);
}
*/

template <typename T>
DualCycleLinkList<T>::~DualCycleLinkList() {
	clear();
}


} /* namespace */



#endif // DUALCYCLELINKLIST_H
