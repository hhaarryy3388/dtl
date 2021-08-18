#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Pointer.h"

/*
 * 1,智能指针只能用来指向堆空间中的单个对象(变量)
 * 2,不同类型的智能指针对象不能混合使用
 * 3,不要使用delete释放智能指针指向的堆空间
 */

namespace DTLib
{
/* 智能指针,只能用来指向堆空间中的单个对象或者对象
 * 意义在于最大程度的避免内存泄漏
 * 1>指针周期结束时主动释放堆空间
 * 2>一片堆空间最多只能由一个指针标识
 * 3>杜绝指针运算和指针比较,如:p++
 */
template<typename T>
class SmartPointer : public Pointer<T>
{
protected:
    /* 智能指针的值,也就是所用空间的地址,在父类实现 */
public:
	/* 构造函数,将初始化的值存到,m_pointer
	 * explicit,不允许将一个内置指针隐式转换为一个智能指针
	 * 错误:SmartPointer<Test> sp = new Test();
	 * 正确:SmartPointer<Test> sp(new Test());
	 */
//	explicit SmartPointer(T* p = nullptr);
    SmartPointer(T* p = nullptr);
    SmartPointer(const SmartPointer<T>& obj);
    SmartPointer& operator=(const SmartPointer<T>& obj);
    ~SmartPointer<T>();
};
/* 直接调用父类的构造函数*/
template<typename T>
SmartPointer<T>::SmartPointer(T* p) : Pointer<T>(p)
{
    //cout << "SmartPointer(T* p)" << endl;
}

/* 拷贝构造函数,用智能指针给新智能指针构造赋值构造时,把老智能指针指向的值变为NULL
 * 保证同一个空间,只有一个智能指针
 */
template<typename T>
SmartPointer<T>::SmartPointer(const SmartPointer<T>& obj) : Pointer<T>(nullptr) {
    //cout << "SmartPointer(const SmartPointer<T>& obj)" << endl;

    this->m_pointer = obj.m_pointer;
    const_cast<SmartPointer<T>&>(obj).m_pointer = nullptr;  //把const属性去掉后,将用来赋值的指针清空
}
/* 重载赋值操作符"="
 * 保证同一个空间,只有一个智能指针
 */
template<typename T>
SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer<T>& obj) {
    //cout << "SmartPointer<T>::operator=" << endl;
    /* 排除自己赋值给自己的情况 */
    if ( obj != this ) {
        T* toDel = this->m_pointer;
        this->m_pointer = obj.m_pointer;

        const_cast<SmartPointer&>(obj).m_pointer = nullptr;

        delete toDel;       // 最后释放,防止抛出异常爆掉
    }
    return *this;
}

/*  */
template<typename T>
SmartPointer<T>::~SmartPointer<T>() {
    delete this->m_pointer;
}



}
#endif // SMARTPOINTER_H
