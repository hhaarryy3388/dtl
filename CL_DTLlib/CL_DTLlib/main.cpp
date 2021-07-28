#include <iostream>
#include "SmartPointer.h"
#include "Exception.h"
using namespace std;
using namespace DTLib;
class Test
{
public:
	Test()
	{
		cout << "Test()" <<endl;
	}
	~Test()
	{
		cout << "~Test()" <<endl;
	}
};

int main()
{
	try
	{
		THROW_EXCEPTION(NullPointerException,"test");
	}
	catch(const Exception& e)
	{
		cout << "catch(const Exception& e)" << endl;
		cout << e.location() << " >> " << e.message() << endl;
	}
	SmartPointer<Test> sp(new Test());
	SmartPointer<Test> nsp;
	nsp = sp;
	cout <<sp.isNull() << endl;
	cout <<nsp.isNull() << endl;
	return 0;
}
