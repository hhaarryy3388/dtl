#include "Object.h"
//#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

namespace DTLib {

void* Object::operator new(unsigned int size) noexcept {
    //cout << "Object::operator new(): " << size << endl;
    return malloc(size);
}


void Object::operator delete(void* p) {
    //cout << "Object::operator delete(): " << endl;
    free(p);
}

void* Object::operator new[](unsigned int size) noexcept {
    //cout << "Object::operator new[](): " << size << endl;
    return malloc(size);
}

void Object::operator delete[](void* p) {
    //cout << "Object::operator delete[](): " << endl;
    free(p);
}

bool Object::operator ==(const Object& obj) {
    return (this == &obj);
}

bool Object::operator !=(const Object& obj) {
    return (this != &obj);
}

Object::~Object() {

}




} /* namespace */
