#ifndef EXCEPTION_H
#define EXCEPTION_H

namespace DTLib
{
/* 异常类
 * 类型可以是自定义
 * 对类类型异常的匹配依旧是自上而下严格匹配
 * 赋值兼容性原则,在异常匹配中依然使用,(子类可以当做父类来匹配)
 * 所以catch匹配之类的一定要放到父类之上
 * 计算异常,空指针异常,越界异常,内存不足异常,参数错误异常
 */
#define THROW_EXCEPTION(e,m) (throw e(m,__FILE__,__LINE__))
/* 异常类抽象类 */
class Exception
{
protected:
	char* m_message;	//异常信息
	char* m_location;	//发生异常的位置
	/* 初始化异常信息,和异常位置信息 */
	void init(const char* message, const char* file, int line);
public:
	Exception(const char* message);
	Exception(const char* file, int line);
	Exception(const char* message, const char* file, int line );

	Exception(const Exception& e);
	Exception& operator=(const Exception& e);

	virtual const char* message() const;
	virtual const char* location() const;
	/* ~x() = 0,表示是纯虚析构函数,表示这个类是个抽象类 */
	virtual ~Exception() = 0;
};

class ArithmeticException : public Exception {

public:

	ArithmeticException();
	ArithmeticException(const char* message);
	ArithmeticException(const char* file, int line);
	ArithmeticException(const char* message, const char* file, int line);
	ArithmeticException(const ArithmeticException& e);

	ArithmeticException& operator=(const ArithmeticException& e);

	/*
	//构建函数,直接继承父的构建函数
	ArithmeticException(): Exception(nullptr, nullptr, 0) {}
	ArithmeticException(const char* message) : Exception(message, nullptr,0) {}
	ArithmeticException(const char* file, int line):Exception(nullptr, file, line) {}
	ArithmeticException(const char* message, const char* file, int line):Exception(message, file, line) {}

	ArithmeticException(const ArithmeticException& e) : Exception(e) {}
	ArithmeticException& operator=(const ArithmeticException& e);
	ArithmeticException& operator=(const ArithmeticException& e) {
		Exception::operator=(e);		//调用父类的赋值操作函数
		cout << "ArithmeticException::operator= return: " << this << endl;
		return *this;				//返回本身,可以连续赋值x=y=z
	}
	*/
	//~ArithmeticException() {}
};

class NullPointerException : public Exception {

public:
	NullPointerException();
	NullPointerException(const char* message);
	NullPointerException(const char* file, int line);
	NullPointerException(const char* message, const char* file, int line);
	NullPointerException(const NullPointerException& e);

	NullPointerException& operator=(const NullPointerException& e);
};

class IndexOutOfBoundsException : public Exception {

public:
	IndexOutOfBoundsException();
	IndexOutOfBoundsException(const char* message);
	IndexOutOfBoundsException(const char* file, int line);
	IndexOutOfBoundsException(const char* message, const char* file, int line);
	IndexOutOfBoundsException(const IndexOutOfBoundsException& e);

	IndexOutOfBoundsException& operator=(const IndexOutOfBoundsException& e);
};

class NoEnoughMemoryException : public Exception {

public:
	NoEnoughMemoryException();
	NoEnoughMemoryException(const char* message);
	NoEnoughMemoryException(const char* file, int line);
	NoEnoughMemoryException(const char* message, const char* file, int line);
	NoEnoughMemoryException(const NoEnoughMemoryException& e);

	NoEnoughMemoryException& operator=(const NoEnoughMemoryException& e);
};

class InvalidParameterException : public Exception {

public:
	InvalidParameterException();
	InvalidParameterException(const char* message);
	InvalidParameterException(const char* file, int line);
	InvalidParameterException(const char* message, const char* file, int line);
	InvalidParameterException(const InvalidParameterException& e);

	InvalidParameterException& operator=(const InvalidParameterException& e);
};

class InvalidOperationException : public Exception {

public:
	InvalidOperationException();
	InvalidOperationException(const char* message);
	InvalidOperationException(const char* file, int line);
	InvalidOperationException(const char* message, const char* file, int line);
	InvalidOperationException(const InvalidOperationException& e);

	InvalidOperationException& operator=(const InvalidOperationException& e);
};

}
#endif // EXCEPTION_H
