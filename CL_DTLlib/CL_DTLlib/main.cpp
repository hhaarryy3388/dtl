#include <iostream>
#include "SmartPointer.h"
#include "Exception.h"
#include "Object.h"
#include "StaticList.h"
#include "staticlinklist.h"
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

void testStaticLinkList() {
    StaticLinkList<int, 5> ls;

    for ( int i = 0; i < 5; i++ ) {
        ls.insert(0, i+1);
    }
    for ( ls.move(0); !ls.end(); ls.next() ) {
        cout << ls.current() << endl;
    }

    for ( ls.move(0); !ls.end(); ls.next() ) {
        if (ls.current() == 3 ) {
            ls.remove(ls.find(ls.current()));
        }
        cout << ls.current() << endl;
    }
    for ( ls.move(0); !ls.end(); ls.next() ) {
        cout << ls.current() << endl;
    }

    ls.insert(6, 100);  //insert调用LinkList的insert,insert中的create,调用StaticLinkList中单create,所以在insert中抛出异常
}

int main()
{
    testStaticList();

	return 0;
}
