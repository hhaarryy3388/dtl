#ifndef LIST_H
#define LIST_H
#include "object.h"
namespace DTLib
{

template< typename T >
class List : public Object
{
public:
	List();
	virtual bool insert(const T& e) = 0;		//向列表尾部插入一个数据
	virtual bool insert(int i, const T& e) = 0;	//向列表指定位置插入一个数据
	virtual bool remove(int i) = 0;				//移除列表指定位置的数据
	virtual bool set(int i, const T& e) = 0;	//设置列表指定位置的数据
	virtual bool get(int i, T& e) const = 0;	//获取猎豹指定位置的数据
	virtual int  find(const T& e) = 0;
	virtual int length() const = 0;
	virtual void clear() = 0;
};

}


#endif // LIST_H
