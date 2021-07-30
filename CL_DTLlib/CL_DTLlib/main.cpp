#include <iostream>
#include "SmartPointer.h"
#include "Exception.h"
#include "object.h"
using namespace std;
using namespace DTLib;
void testObject() {
	class Child1 : public Object {
	public:
		int i;
		int j;
		~Child1(){

		}

	};

	class Child2 : public Child1 {
	public:
		int k;
		~Child2(){

		}
	};

	Child1* c1 = new Child1();
	Child2* c2 = new Child2();

	delete c1;
	delete c2;

	Child1* c3 = new Child1[5];
	delete [] c3;
}

//测试smart_pointer和exception是否继承自Object
void test_object_sp_exc() {
	SmartPointer<int>* sp = new SmartPointer<int>();
	delete sp;
	InvalidOperationException* e = new InvalidOperationException();
	delete e;
}

int main()
{
	test_object_sp_exc();

	return 0;
}
