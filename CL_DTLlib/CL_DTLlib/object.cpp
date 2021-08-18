#include "Object.h"
#include <cstdio>
#include <iostream>
using namespace std;

namespace DTLib {
// noexcept/throw()表示不会抛出异常
void* Object::operator new (unsigned int size) noexcept
{
	//cout << "Object::operator new(): " << size << endl;
	return malloc(size);
}
void Object::operator delete (void* p)
{
	//cout << "Object::operator delete(): " << endl;
	free(p);
}
void* Object::operator new[] (unsigned int size) noexcept
{
	//cout << "Object::operator new[](): " << size << endl;
	return malloc(size);
}
void Object::operator delete[] (void* p)
{
	//cout << "Object::operator delete[](): " << endl;
	free(p);
}
Object::~Object()
{

}


}
