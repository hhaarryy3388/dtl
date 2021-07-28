#include "Exception.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>
namespace DTLib
{
/* 初始化异常信息,和异常位置信息 */
void Exception::init(const char* message, const char* file, int line)
{
	char lineStr[16];
	/* strdup,在堆中新建并拷贝字符串,因为传进来的字符串不确定储存位置,所以重新拷贝一份字符串 */
	m_message = message ? strdup(message) : nullptr;
	if (file != nullptr) {
		//itoa(line, lineStr, 10);
		snprintf(lineStr, 16, "%d", line );
		m_location = new char[strlen(file)+strlen(lineStr)+2];
		strcpy(m_location, file);
		strcat(m_location, ":");
		strcat(m_location, lineStr);
	}
	else {
		m_location = nullptr;
	}
}
/* 构造函数 */
Exception::Exception(const char* message)
{
	init(message, nullptr, 0);
}
/* 构造函数重载 */
Exception::Exception(const char* file, int line)
{
	init(nullptr, file, line);
}
/* 构造函数重载 */
Exception::Exception(const char* message, const char* file, int line )
{
	init(message, file, line);
}
/*拷贝构造函数,深拷贝 */
Exception::Exception(const Exception& e)
{
	m_message = strdup(e.m_message);
	m_location = strdup(e.m_location);
}
Exception& Exception::operator=(const Exception& e)
{
	/* 排除自己拷贝自己的情况 */
	if( this !=&e )
	{
		free(m_message);
		free(m_location);
		m_message = strdup(e.m_message);
		m_location = strdup(e.m_location);
	}
	return *this;
}
/* 函数后添加const,是对this的修饰
 * 所以函数所在类的成员变量,不能在这个函数内被改变
 * 除了被mutable修饰的成员变量
 */
const char* Exception::message() const
{
	return m_message;
}
const char* Exception::location() const
{
	return m_location;
}
/* 纯虚析构函数,也必须实现,因为子类析构的时候,需要先调用父类的析构 */
Exception::~Exception()
{
	free(m_message);
	free(m_location);
}

ArithmeticException::ArithmeticException(): Exception(nullptr, nullptr, 0) {
}

ArithmeticException::ArithmeticException(const char* message) : Exception(message, nullptr,0) {
}

ArithmeticException::ArithmeticException(const char* file, int line):Exception(nullptr, file, line) {
}

ArithmeticException::ArithmeticException(const char* message, const char* file, int line):Exception(message, file, line) {
}

ArithmeticException::ArithmeticException(const ArithmeticException& e) : Exception(e) {
}

ArithmeticException& ArithmeticException::operator=(const ArithmeticException& e) {
	Exception::operator=(e);
	//std::cout << "ArithmeticException::operator= return: " << this << std::endl;

	return *this;
}
//-------------------------------------------------------
NullPointerException::NullPointerException(): Exception(nullptr, nullptr, 0) {
}

NullPointerException::NullPointerException(const char* message) : Exception(message, nullptr,0) {
}

NullPointerException::NullPointerException(const char* file, int line):Exception(nullptr, file, line) {
}

NullPointerException::NullPointerException(const char* message, const char* file, int line):Exception(message, file, line) {
}

NullPointerException::NullPointerException(const NullPointerException& e) : Exception(e) {
}

NullPointerException& NullPointerException::operator=(const NullPointerException& e) {
	Exception::operator=(e);

	return *this;
}
//-------------------------------------------------------
IndexOutOfBoundsException::IndexOutOfBoundsException(): Exception(nullptr, nullptr, 0) {
}

IndexOutOfBoundsException::IndexOutOfBoundsException(const char* message) : Exception(message, nullptr,0) {
}

IndexOutOfBoundsException::IndexOutOfBoundsException(const char* file, int line):Exception(nullptr, file, line) {
}

IndexOutOfBoundsException::IndexOutOfBoundsException(const char* message, const char* file, int line):Exception(message, file, line) {
}

IndexOutOfBoundsException::IndexOutOfBoundsException(const IndexOutOfBoundsException& e) : Exception(e) {
}

IndexOutOfBoundsException& IndexOutOfBoundsException::operator=(const IndexOutOfBoundsException& e) {
	Exception::operator=(e);

	return *this;
}
//-------------------------------------------------------
NoEnoughMemoryException::NoEnoughMemoryException(): Exception(nullptr, nullptr, 0) {
}

NoEnoughMemoryException::NoEnoughMemoryException(const char* message) : Exception(message, nullptr,0) {
}

NoEnoughMemoryException::NoEnoughMemoryException(const char* file, int line):Exception(nullptr, file, line) {
}

NoEnoughMemoryException::NoEnoughMemoryException(const char* message, const char* file, int line):Exception(message, file, line) {
}

NoEnoughMemoryException::NoEnoughMemoryException(const NoEnoughMemoryException& e) : Exception(e) {
}

NoEnoughMemoryException& NoEnoughMemoryException::operator=(const NoEnoughMemoryException& e) {
	Exception::operator=(e);

	return *this;
}
//-------------------------------------------------------
InvalidParameterException::InvalidParameterException(): Exception(nullptr, nullptr, 0) {
}

InvalidParameterException::InvalidParameterException(const char* message) : Exception(message, nullptr,0) {
}

InvalidParameterException::InvalidParameterException(const char* file, int line):Exception(nullptr, file, line) {
}

InvalidParameterException::InvalidParameterException(const char* message, const char* file, int line):Exception(message, file, line) {
}

InvalidParameterException::InvalidParameterException(const InvalidParameterException& e) : Exception(e) {
}

InvalidParameterException& InvalidParameterException::operator=(const InvalidParameterException& e) {
	Exception::operator=(e);

	return *this;
}
//-------------------------------------------------------
InvalidOperationException::InvalidOperationException(): Exception(nullptr, nullptr, 0) {
}

InvalidOperationException::InvalidOperationException(const char* message) : Exception(message, nullptr,0) {
}

InvalidOperationException::InvalidOperationException(const char* file, int line):Exception(nullptr, file, line) {
}

InvalidOperationException::InvalidOperationException(const char* message, const char* file, int line):Exception(message, file, line) {
}

InvalidOperationException::InvalidOperationException(const InvalidOperationException& e) : Exception(e) {
}

InvalidOperationException& InvalidOperationException::operator=(const InvalidOperationException& e) {
	Exception::operator=(e);

	return *this;
}

}
