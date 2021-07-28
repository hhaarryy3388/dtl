#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

namespace DTLib
{
/* 智能指针,只能用来指向堆空间中的单个对象或者对象
 * 意义在于最大程度的避免内存泄漏
 * 1>指针周期结束时主动释放堆空间
 * 2>一片堆空间最多只能由一个指针标识
 * 3>杜绝指针运算和指针比较,如:p++
 */
template<typename T>
class SmartPointer
{
protected:
	T* m_pointer;	/* 智能指针的值,也就是所用空间的地址 */
public:
	/* 构造函数,将初始化的值存到,m_pointer
	 * explicit,不允许将一个内置指针隐式转换为一个智能指针
	 * 错误:SmartPointer<Test> sp = new Test();
	 * 正确:SmartPointer<Test> sp(new Test());
	 */
	explicit SmartPointer(T* p = nullptr)
	{
		m_pointer = p;
	}
	/* 拷贝构造函数,用智能指针给新智能指针构造赋值构造时,把老智能指针指向的值变为NULL
	 * 保证同一个空间,只有一个智能指针
	 */
	SmartPointer(const SmartPointer<T>& obj)
	{
		m_pointer = obj.m_pointer;
		const_cast<SmartPointer<T>&>(obj).m_pointer = nullptr;	//把const属性去掉后,将用来赋值的指针清空
	}
	/* 重载赋值操作符"="
	 * 保证同一个空间,只有一个智能指针
	 */
	SmartPointer<T>& operator = (const SmartPointer<T>& obj)
	{
		/* 排除自己赋值给自己的情况 */
		if( this != &obj )
		{
			delete m_pointer;		//释放自己原来指向的空间
			m_pointer = obj.m_pointer;
			const_cast<SmartPointer<T>&>(obj).m_pointer = nullptr;	//把const属性去掉后,将用来赋值的指针清空
		}
		return *this;	//返回智能指针自己的引用,可以用来连续赋值,x=y=z的情况
	}
	/* 重载对象的指针操作符"->" */
	T* operator -> ()
	{
		return m_pointer;	//返回智能指针地址
	}
	/* 重载对象的指针操作符"*"
	 * 用引用的方式返回,外部操作这个引用(实际空间别名),只能指针指向的空间,也会改变
	 */
	T& operator * ()
	{
		return *m_pointer;	//返回智能指针指向的内容
	}
	/* 智能指针是否为空 */
	bool isNull()
	{
		return (m_pointer == nullptr);
	}
	/* 获取智能指针 */
	T* get()
	{
		return m_pointer;	//返回智能指针地址
	}
	/* 析构函数,释放智能指针的空间 */
	~SmartPointer()
	{
		delete m_pointer;
	}
};
}
#endif // SMARTPOINTER_H
