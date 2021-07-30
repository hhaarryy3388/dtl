#include "object.h"
#include <cstdlib>
namespace DTLib {

void* Object::operator new (unsigned int size) noexcept()
{
	return mallor(size);
}
void Object::operator delete (void* p)
{
	free(p);
}
void* Object::operator new[] (unsigned int size) noexcept()
{
	return mallor(size);
}
void Object::operator delete[] (void* p)
{
	free(p);
}
~Object::Object()
{

}


}
