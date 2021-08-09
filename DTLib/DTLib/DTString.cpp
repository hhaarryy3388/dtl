#include <cstring>
#include <cstdlib>
#include "DTString.h"
#include "Exception.h"

namespace DTLib {

unsigned int* String::make_pmt(const char* p) {
    unsigned int len = strlen(p);
    unsigned int* ret = static_cast<unsigned int*>(malloc(sizeof(unsigned int*) * len));

    if ( ret != nullptr ) {
        unsigned int ll = 0;

        ret[0] = 0;

        for ( unsigned int i = 1; i < len; i++ ) {
            while ( (ll > 0) && (p[ll] != p[i]) ) {
                ll = ret[ll-1];
            }

            if ( p[ll] == p[i] ) {
                ll++;
            }

            ret[i] = ll;
        }
    }
    return ret;
}

int String::kmp(const char* s, const char* p) {
    int ret = -1;
    unsigned int sl = strlen(s);
    unsigned int pl = strlen(p);
    unsigned int* pmt = make_pmt(p);

    if ( (pmt != nullptr) && (0 < pl) && (pl <= sl)) {
        for (unsigned int i = 0, j = 0; i < sl; i++ ) {
            while ( (j > 0) && (s[i] != p[j]) ) {
                j = pmt[j-1];
            }

            if ( s[i] == p[j] ) {
                j++;
            }

            if ( j == pl ) {
                ret = static_cast<int>(i + 1 - pl);
                break;
            }
        }
    }

    free(pmt);

    return ret;
}


void String::init(const char* s) {
    m_str = strdup(s);
    if ( m_str != nullptr ) {
        m_length = static_cast<int>(strlen(m_str));
    }
    else {
        THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create String object...");
    }
}

bool String::equal(const char* l, const char* d, int len) const {
    return ( strncmp(l, d, static_cast<size_t>(len)) == 0 );
}

String::String()
{
    init("");
}

String::String(char c) {
    char s[2] = {c, '\0'};
    init( s );
}

String::String(const char* s) {
    init(s ? s : "");
}

String::String(const String& s) {
    init(s.str());
}

int String::length() const {
    return m_length;
}

const char* String::str() const {
    return m_str;
}


char& String::operator[](int i) {
    if ( i >= 0 && i <= m_length ) {
        return m_str[i];
    }
    else {
        THROW_EXCEPTION(IndexOutOfBoundsException, "assign parameter for [] invalid...");
    }
}
char  String::operator[](int i) const {
    return (const_cast<String&>(*this))[i];
}

bool  String::startWith(const char* s) const {
    bool ret = (s != nullptr);

    if ( ret ) {
        int len = static_cast<int>(strlen(s));

        ret = (len <= m_length) && equal(m_str, s, len);
    }

    return ret;
}

bool String::startWith(const String& s) const {
    return startWith(s.m_str);
}

bool String::endOf(const char* s) const {
    bool ret = (s != nullptr);

    if ( ret ) {
        int len = static_cast<int>(strlen(s));

        ret = (len <= m_length) && equal(m_str+m_length-len, s, len);
    }

    return ret;

}

bool String::endOf(const String& s) const {
    return endOf(s.m_str);
}

String& String::insert(int i, const char* s) {
    if ( i >= 0 && i <= m_length ) {
        if ( (s != nullptr) && (s[0] != '\0') ) {
            int len = static_cast<int>(strlen(s));
            char* str = reinterpret_cast<char*>(malloc(static_cast<size_t>(len+m_length+1)));
            if (str) {
                strncpy(str, m_str, static_cast<unsigned int>(i));
                strncpy(str + i, s, static_cast<size_t>(len));
                strncpy(str + i + len, m_str + i, static_cast<size_t>(m_length - i));
                str[len + m_length] = '\0';

                free(m_str);
                m_str = str;
                m_length = len + m_length;

            }
            else {
                THROW_EXCEPTION(NoEnoughMemoryException, "no enough memory to insert...");
            }
        }
    }
    else {
        THROW_EXCEPTION(IndexOutOfBoundsException, "assign parameter to insert invalid...");
    }

    return *this;
}

String& String::insert(int i, const String s) {
    return insert(i, s.m_str);
}

String& String::trim() {
    int b = 0;
    int e = m_length - 1;

    if ( m_length > 0 ) {
        while (m_str[b] == ' ') b++;
        while ( (m_str[e] == ' ') && (e != 0) ) e--;

        if (b > e) {
            m_str[0] = '\0';
        }
        else {
            if (b == 0) {
                m_str[e+1] = '\0';
                m_length = e + 1;
            }
            else {
                int i, j;
                for ( i = 0, j = b; j <= e; j++,i++ ) {
                    m_str[i] = m_str[j];
                }
                m_length = e - b + 1;
                m_str[m_length] = '\0';
            }
        }
    }

    return *this;
}

int String::indexOf(const char* s) const {
    return (kmp(m_str, s ? s : ""));
}

int String::indexOf(const String& s) const {
    return (kmp(m_str, s.str()));
}

String& String::remove(int i, int len) {
    if ( (0 <= i) && (i < m_length)) {
        int n = i;
        int m = i + len;

        while ( (n < m) && (m < m_length) ) {
            m_str[n++] = m_str[m++];
        }
        m_str[n] = '\0';
        m_length = n;
    }
    return *this;
}

String& String::remove(const char* s) {
    return remove(indexOf(s), s ? static_cast<int>(strlen(s)) : 0);
}

String& String::remove(const String& s) {
    return remove(indexOf(s), s.length());
}

String& String::replace(const char* t, const char* s) {
    int index = indexOf(t);

    if ( index >= 0 ) {
        remove(t);
        insert(index, s);
    }

    return *this;
}

String& String::replace(const String& t, const char* s) {
    return replace(t.str(), s);
}

String& String::replace(const char* t, const String& s) {
    return replace(t, s.str());
}

String& String::replace(const String& t, const String& s) {
    return replace(t.str(), s.str());
}

String String::sub(int i, int len) const {
    String ret;

    if ( ( i >= 0) && (i < m_length) ) {
        if ( len < 0 ) len  = 0;
        if ( (len + i) > m_length ) len = m_length - i;
        char* str = reinterpret_cast<char*>(malloc(static_cast<size_t>(len+1)));

        strncpy(str, m_str + i, static_cast<size_t>(len));
        str[len] = '\0';

        ret = str;
    }
    else {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Sub, Parameter i is invalid...");
    }

    return ret;
}



bool String::operator == (const char* s) {
    return ( strcmp(m_str, s ? s : "") == 0 );
}

bool String::operator == (const String& s) {
    return ( strcmp(m_str, s.str()) == 0 );
}

bool String::operator != (const char* s) {
    return !(*this == s);
}

bool String::operator != (const String& s) {
    return !(*this == s);
}

bool String::operator > (const char* s) {
    return ( strcmp(m_str, s ? s : "") > 0 );
}

bool String::operator > (const String& s) {
    return ( strcmp(m_str, s.str()) > 0 );
}

bool String::operator < (const char* s) {
    return ( strcmp(m_str, s ? s : "") < 0 );
}

bool String::operator < (const String& s) {
    return ( strcmp(m_str, s.str()) < 0 );
}

bool String::operator >= (const char* s) {
    return ( strcmp(m_str, s ? s : "") >= 0 );
}

bool String::operator >= (const String& s) {
    return ( strcmp(m_str, s.str()) >= 0 );
}

bool String::operator <= (const char* s) {
    return ( strcmp(m_str, s ? s : "") <= 0 );
}

bool String::operator <= (const String& s) {
    return ( strcmp(m_str, s.str()) <= 0 );
}

String String::operator + (const char* s) {
    String ret;
    int len = m_length + static_cast<int>(strlen(s ? s : ""));

    char* str = reinterpret_cast<char *>(malloc(static_cast<size_t>(len+1)));

    if ( str != nullptr ) {
        strcpy( str, m_str );
        strcat( str, s ? s : "");

        free(ret.m_str);
        ret.m_str = str;
        ret.m_length = len;
    }
    else {
        THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to add String values...");
    }
    return ret;
}

String String::operator + (const char c) {
    char str[] = {c, '\0'};

    return (*this + str);
}

String String::operator + (String& s) {
    return (*this + s.str());
}


String& String::operator += (const char* s) {
    return (*this = *this + s);
}

String& String::operator += (const char c) {
    char str[] = {c, '\0'};
    return (*this = *this + str);
}

String& String::operator += (String& s) {
    return (*this = *this + s.str());
}

String& String::operator = (const char* s) {
    if ( s != m_str ) {
        char* str = strdup(s ? s : "");

        if ( str != nullptr ) {
            free(m_str);
            m_str = str;
            m_length = static_cast<int>(strlen(str));
        }
        else {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to assign new String value...");
        }
    }
    return *this;

}

String& String::operator = (const String& s) {
    return (*this = s.str());
}


String& String::operator = (const char c) {
    char s[] = {c, '\0'};

    return (*this = s);
}



String::~String() {
    free(m_str);
}



}   /* namespace */
