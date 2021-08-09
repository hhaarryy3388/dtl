#ifndef LIST_H
#define LIST_H
#include "object.h"
namespace DTLib
{

template< typename T >
class List : public Object
{
protected:
	// 禁止拷贝构造函数和赋值操作,防止指针指向同一个空间的问题
	List(const List&);
	List& operator=(const List&);
public:
	List();//上面手工指定了构造函数,编译器就不会自动生成默认的构造函数
	virtual bool insert(const T& e) = 0;		//向线性表尾部插入一个数据
	virtual bool insert(int i, const T& e) = 0;	//向线性表指定位置插入一个数据
	virtual bool remove(int i) = 0;				//移除线性表指定位置的数据
	virtual bool set(int i, const T& e) = 0;	//设置线性表指定位置的数据
	virtual bool get(int i, T& e) const = 0;	//获取线性表指定位置的数据
	virtual int  find(const T& e) = 0;
	virtual int length() const = 0;				//获取线性表的长度
	virtual void clear() = 0;					//清空线性表
};

template <typename T>
List<T>::List() {}

}	/* namespace */


#endif // LIST_H
