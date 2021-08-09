#ifndef OBJECT_H
#define OBJECT_H

namespace DTLib {


class Object
{
public:
    void* operator new(unsigned int size) noexcept;     // =throw(), 不要抛异常
    void operator delete(void* p);
    void* operator new[](unsigned int size) noexcept;
    void operator delete[](void* p);
    bool operator ==(const Object& obj);
    bool operator !=(const Object& obj);
    virtual ~Object() = 0;
};



} /* namespace */


#endif // OBJECT_H


