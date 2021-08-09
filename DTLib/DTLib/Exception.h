#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "Object.h"

namespace DTLib
{

#define THROW_EXCEPTION(e, m) (throw e(m, __FILE__, __LINE__))

class Exception : public Object
{
protected:
    char* m_message;
    char* m_location;

    void init(const char* message, const char* file, int line);
public:
    Exception(const char* message);
    Exception(const char* file, int line);
    Exception(const char* message, const char* file, int line );

    Exception(const Exception& e);
    Exception& operator=(const Exception& e);

    virtual const char* message() const;
    virtual const char* location() const;

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
    ArithmeticException(): Exception(nullptr, nullptr, 0) {}
    ArithmeticException(const char* message) : Exception(message, nullptr,0) {}
    ArithmeticException(const char* file, int line):Exception(nullptr, file, line) {}
    ArithmeticException(const char* message, const char* file, int line):Exception(message, file, line) {}

    ArithmeticException(const ArithmeticException& e) : Exception(e) {}
    ArithmeticException& operator=(const ArithmeticException& e);
    ArithmeticException& operator=(const ArithmeticException& e) {
        Exception::operator=(e);
        cout << "ArithmeticException::operator= return: " << this << endl;
        return *this;
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

}   /* namespace */

#endif // EXCEPTION_H
