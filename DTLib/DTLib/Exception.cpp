#include "Exception.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>

//using namespace std;

namespace DTLib
{

void Exception::init(const char* message, const char* file, int line) {
    char lineStr[16];

    // 视频中第26课专门讲述, 某些编译器比如glibc2.2,在函数库strdup中
    // 不进行message空指针的判断,直接进行:strlen(),有安全隐患
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

Exception::Exception(const char* message) {
    init(message, nullptr, 0);
}

Exception::Exception(const char* file, int line) {
    init(nullptr, file, line);
}

Exception::Exception(const char* message, const char* file, int line ) {
    init(message, file, line);
}

Exception::Exception(const Exception& e) {
    //std::cout << "Exception::Exception(const Exception& e)" << std::endl;

    m_message = strdup(e.m_message);
    m_location = strdup(e.m_location);

}

Exception& Exception::operator=(const Exception& e) {
    if (this != &e) {
        free(m_message);
        free(m_location);

        m_message = strdup(e.m_message);
        m_location = strdup(e.m_location);
    }

    //std::cout << "Exception::operator= return: " << this << std::endl;
    return *this;
}

const char* Exception::message() const {
    return m_message;
}

const char* Exception::location() const {
    return m_location;
}

Exception::~Exception() {
    delete m_message;
    delete m_location;
}
//-------------------------------------------------------
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
//-------------------------------------------------------

} /* namespace */
