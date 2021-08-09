#include <iostream>
#include <cstring>
#include <cstdio>
#include <ctime>

#include "SmartPointer.h"
#include "Exception.h"
#include "Object.h"
#include "List.h"
#include "SeqList.h"
#include "StaticList.h"
#include "DynamicList.h"
#include "StaticArray.h"
#include "DynamicArray.h"
#include "LinkList.h"
#include "StaticLinkList.h"
#include "SharedPointer.h"
#include "CircleLinkList.h"
#include "DualLinkList.h"
#include "DualStaticLinkList.h"
#include "DualCircleLinkList.h"
#include "DualCycleLinkList.h"
#include "StaticStack.h"
#include "LinkStack.h"
#include "StaticQueue.h"
#include "LinkQueue.h"
#include "DTString.h"
#include "Sort.h"
#include "GTreeNode.h"
#include "GTree.h"
#include "BTreeNode.h"
#include "BTree.h"
#include "Graph.h"
#include "MatrixGraph.h"
#include "ListGraph.h"

using namespace std;
using namespace DTLib;


void testSmartPoint(void) {
    class TestPoint {

    public:
        TestPoint() {
            cout << "TestPoint()" << endl;
        }

        ~TestPoint() {
            cout << "~TestPoint()" << endl;
        }
    };

    cout << "new start..." << endl;
    SmartPointer<TestPoint> sp = new TestPoint();
    cout << "------" << endl;

    SmartPointer<TestPoint> nsp = sp;
    cout << " sp is NULL :" << sp.isNull() << endl;
    cout << "nsp is NULL :" << nsp.isNull() << endl;
}

void testException(void) {
    try {
        //throw(Exception("error", __FILE__, __LINE__));
        //THROW_EXCEPTION(Exception, "error");
        THROW_EXCEPTION(ArithmeticException, "error");
    }
    catch ( const ArithmeticException& e) {
        cout << "catch ArithmeticException" << endl;
        cout << e.message() << endl;
        cout << e.location() << endl;
    }
    catch ( const Exception& e) {
        cout << "catch Exception" << endl;
        cout << e.message() << endl;
        cout << e.location() << endl;
    }

    ArithmeticException e1("err_e1");
    ArithmeticException e2;
    e2 = e1;
    ArithmeticException e3(e1);
    cout << "e2.message(): " << e2.message() << endl;
    cout << "e3.message(): " << e3.message() << endl;


}

void testObject() {
    class Child1 : public Object {
    public:
        int i;
        int j;
    };

    class Child2 : public Child1 {
    public:
        int k;
    };

    Child1* c1 = new Child1();
    Child2* c2 = new Child2();

    delete c1;
    delete c2;

    Child1* c3 = new Child1[5];
    delete [] c3;
}

// 测试智能指针和异常类是否确实继承自Object
void testObjectInherit() {
    SmartPointer<int> *sp = new SmartPointer<int>();
    delete sp;

    InvalidOperationException *e = new InvalidOperationException();
    delete e;
}

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

void testDynamicList() {
    DynamicList<int> sl(5);

    for ( int i = 0; i < 5; i++ ) {
        sl.insert(0, i+1);
    }

    for ( int i = 0; i < 5; i++ ) {
        cout << sl[i] << endl;
    }

    cout << "sl.capacity() = " << sl.capacity() << endl;
    cout << "sl.length() = " << sl.length() << endl;

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

        sl.resize(20);
        sl.insert(5, 50);
    }

    for ( int i = 0; i < sl.length(); i++ ) {
        cout << sl[i] << endl;
    }

    cout << "sl.capacity() = " << sl.capacity() << endl;
    cout << "sl.length() = " << sl.length() << endl;


}

void testDynamicList_2() {
    DynamicList<int> dl(5);

    for ( int i = 0; i < dl.capacity(); i++ ) {
        dl.insert(i+10);
    }

    for ( int i = 0; i < dl.capacity(); i++ ) {
        cout << dl[i] << endl;
    }
}

void testStaticArray() {
    StaticArray<int,5> s1;
    StaticArray<int,5> s2;

    for ( int i = 0; i < s1.length(); i++ ) {
        s1[i] = 10 + i;
    }

    s2 = s1;

    cout << "s2 array:" << endl;
    for ( int i = 0; i < s2.length(); i++ ) {
        cout << s2[i] << endl;
    }

    StaticArray<int,5> s3 = s1;
    cout << "s3 array:" << endl;
    for ( int i = 0; i < s3.length(); i++ ) {
        cout << s3[i] << endl;
    }

    //s3[20] = 100;
}

void testDynamicArray() {
    DynamicArray<int> s1(5);
    DynamicArray<int> s2(5);

    for ( int i = 0; i < s1.length(); i++ ) {
        s1[i] = 10 + i;
    }

    s2 = s1;

    cout << "s2 array:" << endl;
    for ( int i = 0; i < s2.length(); i++ ) {
        cout << s2[i] << endl;
    }

    DynamicArray<int> s3 = s1;
    cout << "s3 array:" << endl;
    for ( int i = 0; i < s3.length(); i++ ) {
        cout << s3[i] << endl;
    }

    s3.resize(10);
    s3[7] = 100;

    cout << "s3 array after resize:" << endl;
    for ( int i = 0; i < s3.length(); i++ ) {
        cout << s3[i] << endl;
    }
}

void testLinkList() {
    LinkList<int> sl;


    for ( int i = 0; i < 5; i++ ) {
        sl.insert(0, i+1);
    }
    for ( int i = 0; i < 5; i++ ) {
        cout << sl.get(i) << endl;
    }


    sl.set(2, 20);
    sl.set(3, 30);

    for ( int i = 0; i < 5; i++ ) {
        cout << sl.get(i) << endl;
    }

    sl.remove(0);
    sl.insert(200);

    for ( int i = 0; i < 5; i++ ) {
        cout << sl.get(i) << endl;
    }

    // test overload function []
    for ( int i = 0; i < 5; i++ ) {
        sl[i] = 100*i;
    }
    for ( int i = 0; i < 5; i++ ) {
        cout << sl[i] << endl;
    }

    try {
        sl.set(5, 50);
    }
    catch (Exception& e){
        cout << e.message() << endl;
        cout << e.location() << endl;
    }
}

void testListFind() {
    //*********************************************
    LinkList<int> ls;
    for ( int i = 0; i < 5; i++ ) {
        ls.insert(0, i+1);
    }
    for ( int i = 0; i < 5; i++ ) {
        cout << ls.get(i) << endl;
    }

    cout << ls.find(3) << endl;
    //*********************************************
    class Test : public Object {
        int m_v;
    public:
        Test(int v = 0) {
            m_v = v;
        }

        bool operator==(const Test& t ) {
            return (m_v == t.m_v);
        }
    };
    //--------------------------------------
    LinkList<Test> lt;
    Test    t1(1);
    Test    t2(2);
    Test    t3(3);

    lt.insert(t1);
    lt.insert(t2);
    lt.insert(t3);

    cout << lt.find(t3) << endl;
    //*********************************************
}

void testLinkListQuickGoThrough() {
    LinkList<int> lt;

    LinkList<int> ls;
    for ( int i = 0; i < 5; i++ ) {
        ls.insert(0, i+1);
    }
    for ( ls.move(0); !ls.end(); ls.next() ) {
        cout << ls.current() << endl;
    }

    cout << ls.find(3) << endl;
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

    ls.insert(6, 100);
}

// 测试 StaticLinkList 类的析构函数
void testStaticLinkListBug() {
    StaticLinkList<int, 10> list;

    for ( int i = 0; i < 5; i++ ) {
        list.insert(i);
    }

    for ( int i = 0; i < list.length(); i++ ) {
        cout << list.get(i) << endl;
    }
}

// 测试多维数组
void testMultiArray() {
    DynamicArray<DynamicArray<int>> d;

    d.resize(3);
    for (int i = 0; i < 3; i++ ) {
        d[i].resize(i+3);
        for ( int j = 0; j < d[i].length(); j++ ) {
            d[i][j] = i + j;
        }
    }

    for (int i = 0; i < d.length(); i++ ) {
        for (int j = 0; j < d[i].length(); j++ ) {
            cout << d[i][j] << " ";
        }
        cout << endl;
    }
}

void testSharedPointer() {
    class Test : public Object {
    public:
        int v;
        Test(int i = 0) {
           v = i;
           cout << "Test()" << endl;
        }
        ~Test() {
            cout << "~Test()" << endl;
        }
    };

    const SharedPointer<Test> sp1 = new Test();
    SharedPointer<Test> sp2 = sp1;
    SharedPointer<Test> sp3;

    sp3 = sp1;
    sp2->v = 200;
    cout << sp1->v << endl;
    cout << sp2->v << endl;
    cout << sp3->v << endl;

    cout << (sp1==sp2) << endl;

    sp2.clear();
    cout << (sp1==sp2) << endl;
    //sp1.clear();
    sp3.clear();

    cout << "end" << endl;


}

/*
 *  n: 多少人玩游戏
 *  s: 从哪个序号开始     取值: 1 ...
 *  m: 第几个人死        取值: 1 ...
 */
void josephus(int n, int s, int m) {
    CircleLinkList<int> cl;

    for ( int i = 0; i < n; i++ ) {
        cl.insert(i, i+1);
    }

    cl.move(s-1, m-1);
    while ( cl.length() > 0 ) {
        cl.next();
        cout << cl.current() << " ";

        //cl.remove(cl.find(cl.current()));     // 这种find方式有缺陷!!!!
        cl.remove(cl.find(cl.currentNode()));   // 用我们设计的调用方式,更加合理
    }
    cout << endl;
}

void testCircleLinkList() {
    josephus(41, 1, 3);     // 从序号1开始,序号3、6、9 依次死掉
}

void testDualLinkList() {
    DualLinkList<int> dl;

#if 1
    // 测试尾部插入
    for ( int i = 0; i < 5; i++ ) {
        dl.insert(i + 1);
        //dl.insert(10);
    }
#endif

#if 0
    // 测试头部插入
    for ( int i = 0; i < 5; i++ ) {
        dl.insert(0, i + 1);
    }
#endif

#if 0
    // 测试中间插入
    for ( int i = 0; i < 5; i++ ) {
        dl.insert(dl.length()/2, i + 1);
    }
#endif

#if 1
    // 测试: 三种删除节点,然后进行前后遍历打印
    while (dl.length() > 1) {
        dl.remove(0);
        //dl.remove(dl.length() - 1);
        //dl.remove(dl.length()/2);

        for ( dl.move(0); !dl.end(); dl.next() ) {
            cout << dl.current() << " ";
        }
        cout << endl;

        for ( dl.move(dl.length()-1); !dl.end(); dl.pre() ) {
            cout << dl.current() << " ";
        }
        cout << endl;

    }

#endif

#if 0
    for ( dl.move(0); !dl.end(); dl.next() ) {
        cout << dl.current() << " ";
    }
    cout << endl;
#endif

#if 0
    for ( dl.move(dl.length()-1); !dl.end(); dl.pre() ) {
        cout << dl.current() << " ";
    }
    cout << endl;
#endif

#if 0
    // 下面的代码专门用来测试视频中find()的缺陷
    dl.move(dl.length()-1);
    for ( int i = 0; i < 4; i++ ) {
        if ( dl.current() == 10 ) {
            // 1) 用原始设计进行调用
            //      此时每次remove的并不是我们预想的从尾部开始且value=10的节点
            //dl.remove(dl.find(dl.current()));

            // 2) 这才是我们希望删除的节点
            dl.remove(dl.find(dl.currentNode()));
        }

        // 前面是删除的最后一个节点,此时 dl.m_current指向了nullptr
        if ( dl.end() ) {
            dl.move(dl.length()-1);
        }
        else {
            dl.pre();
        }
    }
    for ( int i = 0; i < dl.length(); i++) {
        cout << dl.get(i) << " ";
    }
    cout << endl;
#endif
}

void testDualStaticLinkList() {
    DualStaticLinkList<int, 5> dl;

#if 1
    // 测试尾部插入
    for ( int i = 0; i < 5; i++ ) {
        dl.insert(i + 1);
        //dl.insert(10);
    }
#endif

#if 0
    // 测试头部插入
    for ( int i = 0; i < 5; i++ ) {
        dl.insert(0, i + 1);
    }
#endif

#if 0
    // 测试中间插入
    for ( int i = 0; i < 5; i++ ) {
        dl.insert(dl.length()/2, i + 1);
    }
#endif

#if 1
    // 测试: 三种删除节点,然后进行前后遍历打印
    while (dl.length() > 1) {
        dl.remove(0);
        //dl.remove(dl.length() - 1);
        //dl.remove(dl.length()/2);

        for ( dl.move(0); !dl.end(); dl.next() ) {
            cout << dl.current() << " ";
        }
        cout << endl;

        for ( dl.move(dl.length()-1); !dl.end(); dl.pre() ) {
            cout << dl.current() << " ";
        }
        cout << endl;

    }

#endif

#if 0
    for ( dl.move(0); !dl.end(); dl.next() ) {
        cout << dl.current() << " ";
    }
    cout << endl;
#endif

#if 0
    for ( dl.move(dl.length()-1); !dl.end(); dl.pre() ) {
        cout << dl.current() << " ";
    }
    cout << endl;
#endif

#if 0
    // 下面的代码专门用来测试视频中find()的缺陷
    dl.move(dl.length()-1);
    for ( int i = 0; i < 4; i++ ) {
        if ( dl.current() == 10 ) {
            // 1) 用原始设计进行调用
            //      此时每次remove的并不是我们预想的从尾部开始且value=10的节点
            //dl.remove(dl.find(dl.current()));

            // 2) 这才是我们希望删除的节点
            dl.remove(dl.find(dl.currentNode()));
        }

        // 前面是删除的最后一个节点,此时 dl.m_current指向了nullptr
        if ( dl.end() ) {
            dl.move(dl.length()-1);
        }
        else {
            dl.pre();
        }
    }
    for ( int i = 0; i < dl.length(); i++) {
        cout << dl.get(i) << " ";
    }
    cout << endl;
#endif
}

/*
 *  n: 多少人玩游戏
 *  s: 从哪个序号开始     取值: 1 ...
 *  m: 第几个人死        取值: 1 ...
 */
void josephus_dual(int n, int s, int m) {
    DualCircleLinkList<int> cl;

    for ( int i = 0; i < n; i++ ) {
        cl.insert(i, i+1);
    }

    cl.move(s-1, m-1);
    while ( cl.length() > 0 ) {
        cl.next();
        cout << cl.current() << " ";

        //cl.remove(cl.find(cl.current()));
        cl.remove(cl.find(cl.currentNode()));
    }
    cout << endl;

}

void testDualCircleLinkList() {
    josephus_dual(41, 1, 3);     // 从序号1开始,序号3、6、9 依次死掉

}

void josephus_DualCycle(int n, int s, int m) {
    DualCycleLinkList<int> cl;

    for ( int i = 0; i < n; i++ ) {
        cl.insert(i, i+1);
    }

    cl.move(s-1, m-1);
    while ( cl.length() > 0 ) {
        cl.next();
        cout << cl.current() << " ";

        cl.remove(cl.find(cl.current()));
        //cl.remove(cl.find(cl.currentNode()));
    }
    cout << endl;

}
void testDualCycleLinkList() {
    josephus_DualCycle(41, 1, 3);     // 从序号1开始,序号3、6、9 依次死掉


    DualCycleLinkList<int> cl;

    for ( int i = 0; i < 10; i++ ) {
        cl.insert(i+1);
    }

#if 0
    while ( cl.length() > 0 ) {
        cl.remove(cl.length()/2);

        for ( int i = 0; i < cl.length(); i++ ) {
            cout << cl.get(i) << " ";
        }
        cout << endl;
    }
#endif


#if 1
    cl.move(cl.length()-1);
    for ( int i = 0; i < cl.length() * 2; i++ ) {
        cout << cl.current() << " ";
        cl.pre();
    }
    cout << endl;
#endif

}

void testStaticStack() {
    StaticStack<int, 5> ss;

    for ( int i = 0; i < 5; i++ ) {
        ss.push(i+1);
    }

    //ss.push(10);

    for ( int i = 0; i < 5; i++ ) {
        cout << ss.top() << " ";
        ss.pop();
    }
    cout << endl;

    ss.pop();
}

void testLinkStatck() {
    LinkStack<int> ls;

    for ( int i = 0; i < 5; i++ ) {
        ls.push(i+1);
    }

    //ls.push(10);  // 抛出异常

    for ( int i = 0; i < 5; i++ ) {
        cout << ls.top() << " ";
        ls.pop();
    }
    cout << endl;

    ls.pop();       // 抛出异常

}

void testStaticQueue() {
    StaticQueue<int, 5> sq;

    for (int i = 0; i < 5; i++ ) {
        sq.add(i+1);
    }

    for (int i = 0; i < 5; i++ ) {
        cout << sq.front() << " ";
        sq.remove();
    }
    cout << endl;

    sq.remove();
}

void testLinkQueue() {
    LinkQueue<int> lq;

    for (int i = 0; i < 5; i++ ) {
        lq.add(i+1);
    }

    while ( lq.length() > 0 ) {
        cout << lq.front() << " ";
        lq.remove();
    }
    cout << endl;

    lq.remove();

}

void testString() {
    String c1 = "chenshi";
    String c2 = "chenlong";

    cout << "c1 = " << c1.str() << endl;
    cout << "c2 = " << c2.str() << endl;

    cout << (c1 == c2) << endl;
    cout << (c1 > c2) << endl;
    cout << (c1 < c2) << endl;

    c1 = c2;
    cout << "c1 = " << c1.str() << endl;
    cout << "c2 = " << c2.str() << endl;

    cout << "compare with String object..." << endl;

    cout << (c1 == c2) << endl;
    cout << (c1 > c2) << endl;
    cout << (c1 < c2) << endl;

    cout << "compare with char..." << endl;

    cout << (c1 == 'c') << endl;
    cout << (c1 > 'c') << endl;
    cout << (c1 < 'c') << endl;

    cout << "compare with char* ..." << endl;

    cout << (c1 == "cc") << endl;
    cout << (c1 > "cc") << endl;
    cout << (c1 < "cc") << endl;

    cout << "test String add..." << endl;

    cout << (c1 += " is ").str() << endl;
    cout << (c1 += 'a').str() << endl;
    c2 = "good man!";
    cout << (c1 += c2).str() << endl;

}

void testString2(void) {
    String cc = "  chenshi  ";

    cout << cc.startWith("   c") << endl;
    cout << cc.startWith("  ") << endl;
    cout << cc.endOf("  ") << endl;
    cout << cc.endOf("s  ") << endl;
    cout << cc.endOf("i  ") << endl;

    for ( int i = 0; i < cc.length(); i++ ) {
        cout << cc[i];
    }
    cout << endl;

    cout << cc.trim().insert(4, " is ").str() << endl;

    cc = "    ";
    cc = cc.trim() + "hello";
    cout << cc.str() << endl;

    cc = "  chen";
    cout << cc.trim().str() << endl;

    cc = "chen  ";
    cout << cc.trim().str() << endl;

    cc = "  c";
    cout << cc.trim().str() << endl;

    cc = "c  ";
    cout << cc.trim().str() << endl;
}

unsigned int* make_pmt(const char* p) {
    unsigned int len = strlen(p);
    unsigned int* ret = static_cast<unsigned int*>(malloc(sizeof(unsigned int*) * len));

    if ( ret != nullptr ) {
        unsigned int ll = 0;

        ret[0] = 0;

        for ( unsigned int i = 1; i < len; i++ ) {
            while ( (ll > 0) && (p[ll] != p[i]) ) {
                ll = ret[ll-1];
            }

            if ( p[ll] == p[i] ) {
                ll++;
            }

            ret[i] = ll;
        }
    }
    return ret;
}

int kmp(const char* s, const char* p) {
    int ret = -1;
    unsigned int sl = strlen(s);
    unsigned int pl = strlen(p);
    unsigned int* pmt = make_pmt(p);

    if ( (pmt != nullptr) && (0 < pl) && (pl <= sl)) {
        for (unsigned int i = 0, j = 0; i < sl; i++ ) {
            while ( (j > 0) && (s[i] != p[j]) ) {
                j = pmt[j-1];
            }

            if ( s[i] == p[j] ) {
                j++;
            }

            if ( j == pl ) {
                ret = static_cast<int>(i + 1 - pl);
                break;
            }
        }
    }

    free(pmt);

    return ret;
}

void testPMT() {
    //char s[] = "ababax";
    char s[] = "ABCDABD";
    unsigned int *pmt = make_pmt(s);

    for (unsigned int i = 0; i < strlen(s); i++ ) {
        cout << i << ":" << pmt[i] << endl;
    }
    free(pmt);
}

void testKMP(void) {
    cout << kmp("abcdefefabcd", "ef") << endl;
    cout << kmp("abcdefefabcd", "def") << endl;
    cout << kmp("abcdefefabcd", "") << endl;
}

void testString3(void) {
    String s1 = "abcdefefabcd";

    cout << s1.indexOf("ef") << endl;
    cout << s1.indexOf("def") << endl;
    cout << s1.indexOf("") << endl;

    cout << s1.remove(5,20).str() << endl;

    String s2 = "abcdefefabcd";
    cout << s2.replace("cdef", "chen").str() << endl;

}

void testSort(void) {
    int array[] = {3, 4, 9, 7, 8, 6, 0, 2, 1, 5};

    //Sort::Select(array, 10, true);
    //Sort::Insert(array, 10, true);
    //Sort::Bubble(array, 10, false);
    Sort::Shell(array, 10, false);
    //Sort::Merge(array, 10, true);
    //Sort::Quick(array, 10, false);

    for ( int i = 0; i < 10; i++ ) {
        cout << array[i] << " ";
    }
    cout << endl;

}

void testArraySort() {
    StaticArray<int, 5> sa;

    for ( int i = 0; i < sa.length(); i++ ) {
        sa[i] = i;
    }

    Sort::Bubble(sa, false);

    for ( int i = 0; i < sa.length(); i++ ) {
        cout << " " << sa[i];
    }
    cout << endl;


}

#if 0
struct Test
{
    int id;
    int data1[1000];
    double data2[500];


    bool operator < (const Test& obj) {
        return id < obj.id;
    }
    bool operator > (const Test& obj) {
        return id > obj.id;
    }
};


class TestProxy
{
protected:
    Test* m_pTest;
public:
    int id() {
        return m_pTest->id;
    }

    Test& test() const {
        return *m_pTest;
    }

    void operator = (Test& obj) {
        m_pTest = &obj;
    }

    bool operator > (const TestProxy& obj) {
        return test() > obj.test();
    }

    bool operator < (const TestProxy& obj) {
        return test() < obj.test();
    }
};

Test        t[1000];
TestProxy   tp[1000];

void testPoxyClassSort() {
    clock_t begin;
    clock_t end;

    for ( int i = 0; i < 1000; i++ ) {
        t[i].id = i;

        tp[i] = t[i];
    }

    begin = clock();
    Sort::Bubble(t, 1000, false);
    end = clock();
    cout << "spend: " << end - begin << endl;


    begin = clock();
    Sort::Bubble(tp, 1000, true);
    end = clock();
    cout << "spend: " << end - begin << endl;

    for ( int i = 0; i < 1000; i++ ) {
        cout << t[i].id << "    " << tp[i].id() << endl;
    }

}
#endif

void testTree_1() {
    GTree<char> t;
    GTreeNode<char>* node = nullptr;

    GTreeNode<char> nd;
    nd.value = 'A';
    t.insert(&nd);

    //t.insert('A', nullptr);

    node = t.find('A');
    t.insert('B', node);
    t.insert('C', node);
    t.insert('D', node);

    node = t.find('B');
    t.insert('E', node);
    t.insert('F', node);

    node = t.find('E');
    t.insert('K', node);
    t.insert('L', node);

    node = t.find('C');
    t.insert('G', node);

    node = t.find('D');
    t.insert('H', node);
    t.insert('I', node);
    t.insert('J', node);

    node = t.find('H');
    t.insert('M', node);



    t.clear();



    char s[] = "KLFGMIJ";
    for ( int i = 0; i < 7; i++ ) {
        node = t.find(s[i]);
        while (node != nullptr) {
            cout << node->value << " ";
            node = dynamic_cast<GTreeNode<char>*>(node->parent);
        }
        cout << endl;
    }
}

// 测试 remove 操作
void testTree_2() {
    GTree<char> t;
    GTreeNode<char>* node = nullptr;

    GTreeNode<char> nd;
    nd.value = 'A';
    t.insert(&nd);
    //t.insert('A', nullptr);

    node = t.find('A');
    t.insert('B', node);
    t.insert('C', node);
    t.insert('D', node);

    node = t.find('B');
    t.insert('E', node);
    t.insert('F', node);

    node = t.find('E');
    t.insert('K', node);
    t.insert('L', node);

    node = t.find('C');
    t.insert('G', node);

    node = t.find('D');
    t.insert('H', node);
    t.insert('I', node);
    t.insert('J', node);

    node = t.find('H');
    t.insert('M', node);

    cout << "count : " << t.count() << endl;
    cout << "height: " << t.height() << endl;
    cout << "degree: " << t.degree() << endl;

    cout << "start traverse..." << endl;
    for ( t.begin(); !t.end(); t.next() ) {
        cout << t.current() << " ";
    }
    cout << endl;

    //t.remove('D');
    //t.remove(t.find('D'));
    SharedPointer<Tree<char>> p = t.remove(t.find('D'));

    char s[] = "KLFGMIJ";
    for ( int i = 0; i < 7; i++ ) {
        node = t.find(s[i]);
        while (node != nullptr) {
            cout << node->value << " ";
            node = dynamic_cast<GTreeNode<char>*>(node->parent);
        }
        cout << endl;
    }

}

// 测试 remove 操作: 自动销毁所有子孙节点
void testTree_3() {
    GTree<char> t;
    GTreeNode<char>* node = nullptr;

    GTreeNode<char> nd;
    nd.value = 'A';
    t.insert(&nd);
    //t.insert('A', nullptr);

    node = t.find('A');
    t.insert('B', node);
    t.insert('C', node);
    t.insert('D', node);

    node = t.find('B');
    t.insert('E', node);
    t.insert('F', node);

    node = t.find('E');
    t.insert('K', node);
    t.insert('L', node);

    node = t.find('C');
    t.insert('G', node);

    node = t.find('D');
    t.insert('H', node);
    t.insert('I', node);
    t.insert('J', node);

    node = t.find('H');
    t.insert('M', node);

    cout << "start traverse..." << endl;
    for ( t.begin(); !t.end(); t.next() ) {
        cout << t.current() << " ";
    }
    cout << endl;

    //t.remove('D');
    //t.remove(t.find('D'));
    SharedPointer<Tree<char>> p = t.remove(t.find('D'));

    char s[] = "KLFGMIJ";
    for ( int i = 0; i < 7; i++ ) {
        node = t.find(s[i]);
        while (node != nullptr) {
            cout << node->value << " ";
            node = dynamic_cast<GTreeNode<char>*>(node->parent);
        }
        cout << endl;
    }

}

void testBTree_1() {
    BTree<int> bt;
    BTreeNode<int> *n = nullptr;

    bt.insert(1, nullptr);

    n = bt.find(1);
    bt.insert(2, n);
    bt.insert(3, n);

    n = bt.find(2);
    bt.insert(4, n);
    bt.insert(5, n);

    n = bt.find(4);
    bt.insert(8, n);
    bt.insert(9, n);

    n = bt.find(5);
    bt.insert(10, n);

    n = bt.find(3);
    bt.insert(6, n);
    bt.insert(7, n);

    //n = bt.find(6);
    //bt.insert(11, n, LEFT);

    cout << "count  : " << bt.count() << endl;
    cout << "height : " << bt.height() << endl;
    cout << "degree : " << bt.degree() << endl;

    cout << "start level-traverse..." << endl;
    for ( bt.begin(); !bt.end(); bt.next() ) {
        cout << bt.current() << " ";
    }
    cout << endl;

    cout << "start order traverse..." << endl;
    SharedPointer<Array<int>> sp = nullptr;
    //sp = bt.traversal(preOrder);
    //sp = bt.traversal(inOrder);
    sp = bt.traversal(postOrder);
    for ( int i = 0; i < (*sp).length(); i++ ) {
        cout << (*sp)[i] << " ";
    }
    cout << endl;


/*
    SharedPointer<Tree<int>> sp2 = bt.remove(bt.find(3));

    int a[] = {8, 9, 10, 11, 7};
    for (int i = 0; i < 5; i++ ) {
        //TreeNode<int>* node = bt.find(a[i]);
        TreeNode<int>* node = sp2->find(a[i]);
        while ( node != nullptr ) {
            cout << node->value << " ";
            node = node->parent;
        }
        cout << endl;
    }
*/

}

void testBTree_2() {
    BTree<int> bt;
    BTreeNode<int> *n = nullptr;

    bt.insert(1, nullptr);

    n = bt.find(1);
    bt.insert(2, n);
    bt.insert(3, n);

    n = bt.find(2);
    bt.insert(4, n);
    bt.insert(5, n);

    n = bt.find(4);
    bt.insert(8, n);
    bt.insert(9, n);

    n = bt.find(5);
    bt.insert(10, n);

    n = bt.find(3);
    bt.insert(6, n);
    bt.insert(7, n);


    SharedPointer<BTree<int>> sp = bt.clone();


    cout << "source data: " << endl;

    int a[] = {8, 9, 10, 7};
    for (int i = 0; i < 4; i++ ) {
        TreeNode<int>* node = bt.find(a[i]);
        while ( node != nullptr ) {
            cout << node->value << " ";
            node = node->parent;
        }
        cout << endl;
    }

    cout << "clone data: " << endl;

    for (int i = 0; i < 4; i++ ) {
        TreeNode<int>* node = sp->find(a[i]);
        while ( node != nullptr ) {
            cout << node->value << " ";
            node = node->parent;
        }
        cout << endl;
    }

    cout << "compare bt==*sp :" << (bt == *sp) << endl;
    cout << "compare bt!=*sp :" << (bt != *sp) << endl;
}

void testBTree_3() {
    BTree<int> bt1, bt2;
    BTreeNode<int> *n = nullptr;

    bt1.insert(1, nullptr);

    n = bt1.find(1);
    bt1.insert(2, n);
    bt1.insert(3, n);

    n = bt1.find(2);
    bt1.insert(4, n);
    bt1.insert(5, n);

    n = bt1.find(4);
    bt1.insert(8, n);
    bt1.insert(9, n);

    n = bt1.find(5);
    bt1.insert(10, n);

    n = bt1.find(3);
    bt1.insert(6, n);
    bt1.insert(7, n);
    //-----------------------
    bt2.insert(0, nullptr);

    n = bt2.find(0);
    bt2.insert(6, n);
    bt2.insert(2, n);

    n = bt2.find(2);
    bt1.insert(7, n);
    bt1.insert(8, n);
    //-----------------------
    SharedPointer<BTree<int>> spbt = bt1.add(bt2);
    //----------------------------------------------
    cout << "start order traverse..." << endl;
    SharedPointer<Array<int>> sp = nullptr;
    //sp = spbt->traversal(preOrder);
    //sp = spbt->traversal(inOrder);
    //sp = spbt->traversal(postOrder);
    sp = spbt->traversal(levelOrder);
    for ( int i = 0; i < (*sp).length(); i++ ) {
        cout << (*sp)[i] << " ";
    }
    cout << endl;
    //----------------------------------------------
    cout << "start level-traverse..." << endl;
    for ( spbt->begin(); !spbt->end(); spbt->next() ) {
        cout << spbt->current() << " ";
    }
    cout << endl;

}

void testBTree_4() {
    BTree<int> bt1, bt2;
    BTreeNode<int> *n = nullptr;

    bt1.insert(1, nullptr);

    n = bt1.find(1);
    bt1.insert(2, n);
    bt1.insert(3, n);

    n = bt1.find(2);
    bt1.insert(4, n);
    bt1.insert(5, n);

    n = bt1.find(4);
    bt1.insert(8, n);
    bt1.insert(9, n);

    n = bt1.find(5);
    bt1.insert(10, n);

    n = bt1.find(3);
    bt1.insert(6, n);
    bt1.insert(7, n);
    //-----------------------
    //----------------------------------------------
    //BTreeNode<int>* head = bt1.thread(preOrder);
    //BTreeNode<int>* head = bt1.thread(inOrder);
    //BTreeNode<int>* head = bt1.thread(postOrder);
    BTreeNode<int>* head = bt1.thread(levelOrder);

    BTreeNode<int>* tail = nullptr;

    while ( head != nullptr ) {
        tail = head;
        cout << head->value << " ";
        head = head->right;
    }
    cout << endl;

    head = tail;
    while ( head != nullptr ) {
        cout << head->value << " ";
        head = head->left;
    }
    cout << endl;
}

void testGraph_1() {
    MatrixGraph<3, int,int> g;

    g.setEdge(0, 1, 1);
    g.setEdge(1, 0, 2);
    g.setEdge(1, 2, 3);

    cout << "vCount:" << g.vCount() << endl;
    cout << "eCount:" << g.eCount() << endl;
    cout << "ID(1) :" << g.ID(1) << endl;
    cout << "OD(1) :" << g.OD(1) << endl;
    cout << "TD(1) :" << g.TD(1) << endl;

    cout << "W(0,1): " << g.getEdge(0, 1) << endl;
    cout << "W(1,0): " << g.getEdge(1, 0) << endl;
    cout << "W(1,2): " << g.getEdge(1, 2) << endl;

    SharedPointer<Array<int>> aj = g.getAdjacent(0);
    //SharedPointer<Array<int>> aj = g.getAdjacent(2);

    for ( int i = 0; i < aj->length(); i++ ) {
        cout << (*aj)[i] << " ";
    }
    cout << endl;

    cout << "Delete Edge:" << endl;
    g.removeEdge(0, 1);
    cout << "eCount: " << g.eCount() << endl;
    g.setVertex(0, 100);
    cout << "V(0): " << g.getVertex(0) << endl;
    cout << "W(0, 1)" << g.getEdge(0, 1) << endl;

}

void testGraph_2() {
/*
    ListGraph<char, int> g(4);

    g.setVertex(0, 'A');
    g.setVertex(1, 'B');
    g.setVertex(2, 'C');
    g.setVertex(3, 'D');
*/
    ListGraph<char, int> g;

    g.addVertex('A');
    g.addVertex('B');
    g.addVertex('C');
    g.addVertex('D');

    //g.removeEdge();
    //----------------------------------
    for ( int i = 0; i < g.vCount(); i++ ) {
        cout << i << " : " << g.getVertex(i) << endl;
    }
    //----------------------------------
    g.setEdge(0, 1, 5);
    g.setEdge(0, 3, 6);
    g.setEdge(1, 2, 8);
    g.setEdge(2, 3, 2);
    g.setEdge(3, 1, 9);

    cout << "W(0,1) :" << g.getEdge(0, 1) << endl;
    cout << "W(0,3) :" << g.getEdge(0, 3) << endl;
    cout << "W(1,2) :" << g.getEdge(1, 2) << endl;
    cout << "W(2,3) :" << g.getEdge(2, 3) << endl;
    cout << "W(3,1) :" << g.getEdge(3, 1) << endl;

    cout << "eCount :" << g.eCount() << endl;
    //g.removeEdge(3, 1);
    //cout << "W(3,1) :" << g.getEdge(3, 1) << endl;
    cout << "eCount :" << g.eCount() << endl;
    //----------------------------------
    SharedPointer<Array<int>> aj = g.getAdjacent(0);
    for ( int i = 0; i < aj->length(); i++ ) {
        cout << (*aj)[i] << " ";
    }
    cout << endl;
    //----------------------------------
    cout << "ID(1) :" << g.ID(1) << endl;
    cout << "OD(1) :" << g.OD(1) << endl;
    cout << "TD(1) :" << g.TD(1) << endl;
    //----------------------------------
    g.removeVertex();
    cout << "eCount :" << g.eCount() << endl;
    cout << "W(0,1) :" << g.getEdge(0, 1) << endl;
    cout << "W(1,2) :" << g.getEdge(1, 2) << endl;
    //cout << "W(2,3) :" << g.getEdge(2, 3) << endl;

    //----------------------------------

}

//-------------------------------------------------
// 第75课中图的递归方式深度优先遍历
template<typename V, typename E>
void DFS(Graph<V,E>& g, int v, Array<bool>& visited ) {
    if ( (0 <= v) && (v < g.vCount()) ) {
        cout << v << endl;
        visited[v] =true;
        SharedPointer<Array<int>> aj = g.getAdjacent(v);
        for ( int i = 0; i < aj->length(); i++ ) {
            if ( !visited[(*aj)[i]] ) {
                DFS(g, (*aj)[i], visited);
            }
        }
    }
    else {
        THROW_EXCEPTION(InvalidParameterException, "Index v is invalid...");
    }
}

template<typename V, typename E>
void DFS(Graph<V,E>& g, int v) {
    DynamicArray<bool> visited(g.vCount());

    for ( int i = 0; i < visited.length(); i++ ) {
        visited[i] = false;
    }

    DFS(g, v, visited);
}
//-------------------------------------------------
void testGraph_3() {
    MatrixGraph<9, char, int> g;
    const char* VD = "ABEDCGFHI";

    for ( int i = 0; i < 9; i++ ) {
        g.setVertex(i, VD[i]);
    }

    g.setEdge(0, 1, 0);
    g.setEdge(1, 0, 0);

    g.setEdge(0, 3, 0);
    g.setEdge(3, 0, 0);

    g.setEdge(0, 4, 0);
    g.setEdge(4, 0, 0);

    g.setEdge(1, 2, 0);
    g.setEdge(2, 1, 0);

    g.setEdge(1, 4, 0);
    g.setEdge(4, 1, 0);

    g.setEdge(2, 5, 0);
    g.setEdge(5, 2, 0);

    g.setEdge(3, 6, 0);
    g.setEdge(6, 3, 0);

    g.setEdge(4, 6, 0);
    g.setEdge(6, 4, 0);

    g.setEdge(6, 7, 0);
    g.setEdge(7, 6, 0);

    g.setEdge(7, 8, 0);
    g.setEdge(8, 7, 0);

    //SharedPointer<Array<int>> sa = g.BFS(0);
    SharedPointer<Array<int>> sa = g.DFS(0);

    for ( int i = 0; i < sa->length(); i++ ) {
        cout << (*sa)[i] << " ";
    }
    cout << endl;

    DFS(g, 0);
}

template <typename V, typename E>
Graph<V,E>& GraphEasy() {
    static MatrixGraph<4, V, E> g;

    g.setEdge(0, 1, 1);
    g.setEdge(1, 0, 1);

    g.setEdge(0, 2, 3);
    g.setEdge(2, 0, 3);

    g.setEdge(1, 2, 1);
    g.setEdge(2, 1, 1);

    g.setEdge(1, 3, 4);
    g.setEdge(3, 1, 4);

    g.setEdge(2, 3, 1);
    g.setEdge(3, 2, 1);

    return g;
}


template< typename V, typename E >
Graph<V, E>& GraphComplex()
{
    static ListGraph<V, E> g(9);

    g.setEdge(0, 1, 10);
    g.setEdge(1, 0, 10);

    g.setEdge(0, 5, 11);
    g.setEdge(5, 0, 11);

    g.setEdge(1, 2, 18);
    g.setEdge(2, 1, 18);

    g.setEdge(1, 8, 12);
    g.setEdge(8, 1, 12);

    g.setEdge(1, 6, 16);
    g.setEdge(6, 1, 16);

    g.setEdge(2, 3, 22);
    g.setEdge(3, 2, 22);

    g.setEdge(2, 8, 8);
    g.setEdge(8, 2, 8);

    g.setEdge(3, 8, 21);
    g.setEdge(8, 3, 21);

    g.setEdge(3, 6, 24);
    g.setEdge(6, 3, 24);

    g.setEdge(3, 7, 16);
    g.setEdge(7, 3, 16);

    g.setEdge(3, 4, 20);
    g.setEdge(4, 3, 20);

    g.setEdge(4, 5, 26);
    g.setEdge(5, 4, 26);

    g.setEdge(4, 7, 7);
    g.setEdge(7, 4, 7);

    g.setEdge(5, 6, 17);
    g.setEdge(6, 5, 17);

    g.setEdge(6, 7, 19);
    g.setEdge(7, 6, 19);

    return g;
}

// 76课: 测试"prim"最小生成树
void testGraph_4() {
    // 测试1
    //Graph<int, int>& g = GraphEasy<int, int>();
    //SharedPointer<Array<Edge<int>>> sa = g.prim(65535);
    // 测试2
    Graph<int, int>& g = GraphComplex<int, int>();
    //SharedPointer<Array<Edge<int>>> sa = g.prim(65535);
    SharedPointer<Array<Edge<int>>> sa = g.prim(0, false);

    int w = 0;

    for ( int i = 0; i < sa->length(); i++ ) {
        w += (*sa)[i].data;
        cout << (*sa)[i].b << " " << (*sa)[i].e << " " << (*sa)[i].data << endl;
    }
    cout << "Weight: " << w << endl;

}

// 77课: 测试"kruskal"最小生成树
void testGraph_5() {
    // 测试1
    //Graph<int, int>& g = GraphEasy<int, int>();
    //SharedPointer<Array<Edge<int>>> sa = g.kruskal(false);
    // 测试2
    Graph<int, int>& g = GraphComplex<int, int>();
    SharedPointer<Array<Edge<int>>> sa = g.kruskal(false);

    int w = 0;

    for ( int i = 0; i < sa->length(); i++ ) {
        w += (*sa)[i].data;
        cout << (*sa)[i].b << " " << (*sa)[i].e << " " << (*sa)[i].data << endl;
    }
    cout << "Weight: " << w << endl;

}

// 78课, 测试"dijkstra"最短路径
template< typename V, typename E >
Graph<V, E>& GraphEasy2()
{
    static MatrixGraph<4, V, E> g;

    g.setEdge(0, 1, 1);
    g.setEdge(0, 2, 3);
    g.setEdge(1, 2, 1);
    g.setEdge(1, 3, 4);
    g.setEdge(2, 3, 1);

    return g;
}

template< typename V, typename E >
Graph<V, E>& GraphComplex2()
{
    static ListGraph<V, E> g(5);

    g.setEdge(0, 1, 10);
    g.setEdge(0, 3, 30);
    g.setEdge(0, 4, 100);

    g.setEdge(1, 2, 50);

    g.setEdge(2, 4, 10);

    g.setEdge(3, 2, 20);
    g.setEdge(3, 4, 60);

    return g;
}

void testGraph_6() {
    //Graph<int, int>& g = GraphEasy2<int, int>();
    //SharedPointer< Array<int> > p = g.dijkstra(0, 3, 65535);
    Graph<int, int>& g = GraphComplex2<int, int>();
    SharedPointer< Array<int> > p = g.dijkstra(0, 4, 65535);

    for(int i=0; i<p->length(); i++)
    {
        cout << (*p)[i] << " ";
    }

    cout << endl;

}

template< typename V, typename E >
Graph<V, E>& GraphSample()
{
    static ListGraph<V, E> g(3);

    g.setEdge(0, 1, 4);
    g.setEdge(0, 2, 11);

    g.setEdge(1, 2, 2);
    g.setEdge(1, 0, 6);

    g.setEdge(2, 0, 3);

    return g;
}

void testGraph_7() {
    /*
    Graph<int, int>& g = GraphSample<int, int>();

    int r = g.floyd(0, 2, 65535);
    cout << r << endl;

    for ( int i = 0; i < g.vCount(); i++ ) {
        for ( int j = 0; j < g.vCount(); j++ ) {
            cout << g.floyd(i, j, 65535) << " ";
        }
        cout << endl;
    }
    */
    Graph<int, int>& g = GraphSample<int, int>();
    SharedPointer<Array<int>> r = g.floyd(0, 2, 65535);

    for ( int i = 0; i < r->length(); i++ ) {
        cout << (*r)[i] << " ";
    }

    cout << endl;
}

// 第80课
int search_max_path(Graph<int,int>& g, int v, Array<int>& count, Array<LinkList<int>*>& path, Array<bool>& mark) {
    int ret = 0;
    SharedPointer<Array<int>> aj = g.getAdjacent(v);

    for ( int i = 0; i < aj->length(); i++ ) {
        int num = 0;

        if ( !mark[(*aj)[i]] ) {
            num = search_max_path(g, (*aj)[i], count, path, mark);
        }
        else {
            num = count[(*aj)[i]];
        }

        if ( ret < num ) {
            ret = num;
        }
    }

    for ( int i = 0; i < aj->length(); i++ ) {
        if ( ret == count[(*aj)[i]] ) {
            path[v]->insert((*aj)[i]);
        }
    }
    ret++;

    count[v] = ret;
    mark[v] = true;

    return ret;
}

SharedPointer<Graph<int,int>> create_graph(int* a, int len) {
    ListGraph<int, int>* ret = new ListGraph<int, int>(static_cast<unsigned int>(len));

    for ( int i = 0; i < len; i++ ) {
        ret->setVertex(i, a[i]);
    }

    for ( int i = 0; i < len; i++ ) {
        for ( int j = i+1; j < len; j++ ) {
            if ( a[i] <= a[j] ) {
                ret->setEdge(i, j, 1);
            }
        }
    }

    return ret;
}

void init_array(Array<int>& count, Array<LinkList<int>*>& path, Array<bool>& mark ) {
    for ( int i = 0; i < count.length(); i++ ) {
        count[i] = 0;
    }

    for ( int i = 0; i < path.length(); i++ ) {
        path[i] = new LinkList<int>();
    }

    for ( int i = 0; i < mark.length(); i++ ) {
        mark[i] = false;
    }
}

void print_path(Graph<int,int>& g, int v, Array<LinkList<int>*>& path, LinkList<int>& cp) {
    cp.insert(v);

    if ( path[v]->length() > 0 ) {
        for ( path[v]->move(0); !path[v]->end(); path[v]->next() ) {
            print_path(g, path[v]->current(), path, cp);
        }
    }
    else {
        cout << "Element:";
        for ( cp.move(0); !cp.end(); cp.next() ) {
            cout << g.getVertex(cp.current()) << " ";
        }
        cout << endl;
    }

    cp.remove(cp.length()-1);
}

void print_max_path(Graph<int,int>& g, Array<int>& count, Array<LinkList<int>*>& path ) {
    int max = 0;
    LinkList<int> cp;

    for ( int i = 0; i < count.length(); i++ ) {
        if ( max < count[i] ) {
            max = count[i];
        }
    }

    cout << "Len: " << max << endl;

    for ( int i = 0; i < count.length(); i++ ) {
        if ( max == count[i] ) {
            print_path(g, i, path, cp);
        }
    }
}

void search_max_path(Graph<int,int>& g, Array<int>& count, Array<LinkList<int>*>& path, Array<bool>& mark) {
    for ( int i = 0; i < g.vCount(); i++ ) {
        if ( !mark[i] ) {
            search_max_path(g, i, count, path, mark);
        }
    }
}

void solution( int *a, int len ) {
    DynamicArray<int>  count(len);
    DynamicArray<LinkList<int>*>  path(len);
    DynamicArray<bool> mark(len);
    SharedPointer<Graph<int, int>> g;

    g = create_graph(a, len);
    init_array(count, path, mark);
    search_max_path(*g, count, path, mark);
    print_max_path(*g, count, path);

}

void testSolute() {
    //int a[] = {3, 18, 7, 14, 10, 12, 23, 41, 16, 24};
    //int a[] = {1, 3, 4, 2, 5};
    //int a[] = {10, 30, 50, 1, 3, 5};
    int a[] = {1, 2, 3, 4, 5};
    //int a[] = {5, 4, 3, 2, 1};

    //int a[] = {1, 3, 5, 4};
    //int a[] = {2, 1, 3, 5, 4};

    solution(a, sizeof(a)/sizeof(*a));
}

int main() {
    //testSmartPoint();
    //testException();
    //testObject();
    //testObjectInherit();
    //List<int>* t = nullptr;
    //SeqList<int>* t = nullptr;
    //testStaticList();
    //testDynamicList();
    //testDynamicList_2();
    //testStaticArray();
    //testDynamicArray();
    //testLinkList();
    //testListFind();
    //testLinkListQuickGoThrough();
    //testStaticLinkList();
    //testStaticLinkListBug();
    //testMultiArray();
    //testSharedPointer();
    //testCircleLinkList();
    //testDualLinkList();
    //testDualStaticLinkList();
    //testDualCircleLinkList();
    //testDualCycleLinkList();
    //testStaticStack();
    //testLinkStatck();
    //testStaticQueue();
    //testLinkQueue();
    //testString();
    //testString2();
    //testPMT();
    //testKMP();
    //testString3();
    //testSort();
    //testArraySort();
    //testPoxyClassSort();
    //testTree_2();
    //testBTree_1();
    //testBTree_4();
    //testGraph_1();
    //testGraph_2();
    //testGraph_3();
    //testGraph_5();
    //testGraph_6();
    //testGraph_7();

    testSolute();

    return 0;
}
