#include <iostream>
#include "SmartPointer.h"
#include "Exception.h"
#include "object.h"
#include "StaticList.h"
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

//测试静态线性表
void testStaticList() {
	StaticList<int, 5> sl;


	for ( int i = 0; i < 5; i++ ) {
		sl.insert(0, i+1);
	}

	for ( int i = 0; i < 5; i++ ) {
		cout << sl[i] << endl;
	}

	sl[3] = 30;
	sl[2] = 20;

	for ( int i = 0; i < 5; i++ ) {
		cout << sl[i] << endl;
	}

	try {
		sl[5] = 50;
	}
	catch (Exception& e){
		cout << e.message() << endl;
		cout << e.location() << endl;
	}

}


int main()
{
	//testStaticList();
	int i = 5;
	switch(i)
	{
		case 0:
		case 5:
		case 10:
		case 35:
		{
			cout << "5>>case 35" << endl;
		}
		break;
		case 16:

		default:
		{
			cout << "5>>default" << endl;
		}
		break;
	}
	i = 1;
	switch(i)
	{
		case 0:
		case 5:
		case 10:
		case 35:
		{
			cout << "1>>case 35" << endl;
		}
		break;
		case 16:

		default:
		{
			cout << "1>>default" << endl;
		}
		break;
	}
	i = 16;
	switch(i)
	{
		case 0:
		case 5:
		case 10:
		case 35:
		{
			cout << "16>>case 35" << endl;
		}
		break;
		case 16:
		{
			cout << "16>>case 16" << endl;
		}
		break;
		default:
		{
			cout << "16>>default" << endl;
		}
		break;
	}
	return 0;
}
