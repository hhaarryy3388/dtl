#ifndef STRING_H
#define STRING_H

#include "Object.h"


namespace DTLib {



class String : public Object
{
protected:
    char*           m_str;
    int             m_length;

    void init(const char* s);
    bool equal(const char* l, const char* d, int len) const;

    static unsigned int* make_pmt(const char* p);
    static int kmp(const char* s, const char* p);
public:
    String();
    String(char c);
    String(const char* s);
    String(const String& s);

    int length() const;
    const char* str() const;

    char& operator[](int i);
    char  operator[](int i) const;
    bool  startWith(const char* s) const;
    bool  startWith(const String& s) const;
    bool  endOf(const char* s) const;
    bool  endOf(const String& s) const;
    String& insert(int i, const char* s);
    String& insert(int i, const String s);
    String& trim();
    int   indexOf(const char* s) const;
    int   indexOf(const String& s) const;
    String& remove(int i, int len);
    String& remove(const char* s);
    String& remove(const String& s);
    String& replace(const char* t, const char* s);
    String& replace(const String& t, const char* s);
    String& replace(const char* t, const String& s);
    String& replace(const String& t, const String& s);
    String  sub(int i, int len) const;


    bool operator == (const char* s);
    bool operator == (const String& s);
    bool operator != (const char* s);
    bool operator != (const String& s);
    bool operator > (const char* s);
    bool operator > (const String& s);
    bool operator < (const char* s);
    bool operator < (const String& s);
    bool operator >= (const char* s);
    bool operator >= (const String& s);
    bool operator <= (const char* s);
    bool operator <= (const String& s);

    String operator + (const char* s);
    String& operator += (const char* s);
    String operator + (const char c);
    String& operator += (const char c);
    String operator + (String& s);
    String& operator += (String& s);

    String& operator = (const char c);
    String& operator = (const char* s);
    String& operator = (const String& s);


    ~String();
};





}  /* namespace */

#endif // STRING_H
