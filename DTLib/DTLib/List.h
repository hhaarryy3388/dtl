#ifndef LIST_H
#define LIST_H

#include "Object.h"

namespace DTLib {

template <typename T>
class List : public Object
{
protected:
    // 禁止拷贝构造函数和赋值操作,防止指针指向同一个空间的问题
    List(const List&);
    List& operator=(const List&);
public:
    List();
    virtual bool insert(const T& e) = 0;    // 向尾部插入一个数据
    virtual bool insert(int i, const T& e) = 0;
    virtual bool remove(int i) = 0;
    virtual bool set(int i, const T& e) = 0;
    virtual bool get(int i, T& e) const = 0;
    virtual int  find(const T& e) = 0;
    virtual int length() const = 0;
    virtual void clear() = 0;
};

template <typename T>
List<T>::List() {}

} /* namespace */


#endif // LIST_H
