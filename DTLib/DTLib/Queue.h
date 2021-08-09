#ifndef QUEUE_H
#define QUEUE_H

#include "Object.h"

namespace DTLib {

template <typename T>

class Queue : public Object {
public:
    virtual void add(const T& t) = 0;
    virtual void remove() = 0;
    virtual T front() const = 0;
    virtual void clear() = 0;
    virtual int length() const = 0;

};






}  /* namespace*/




#endif // QUEUE_H
