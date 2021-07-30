#ifndef OBJECT_H
#define OBJECT_H

namespace DTLib
{
class Object
{
public:
	// noexcept/throw()表示不会抛出异常
	void* operator new (unsigned int size) noexcept;
	void operator delete (void* p);
	void* operator new[] (unsigned int size) noexcept;
	void operator delete[] (void* p);
	virtual ~Object() = 0;
};

}


#endif // OBJECT_H
