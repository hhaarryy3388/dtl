#ifndef GRAPH_H
#define GRAPH_H


#include "Object.h"
#include "Array.h"
#include "SharedPointer.h"
#include "DynamicArray.h"
#include "LinkQueue.h"
#include "LinkStack.h"
#include "Sort.h"

namespace DTLib {

template <typename E>
struct Edge : public Object
{
    int b;
    int e;
    E   data;

    Edge(int i = -1, int j = -1) {
        b = i;
        e = j;
    }

    Edge(int i, int j, const E& value)
    {
        b = i;
        e = j;
        data = value;
    }

    bool operator == (const Edge<E>& obj) {
        return (b == obj.b) && (e == obj.e);
    }

    bool operator != (const Edge<E>& obj) {
        return !(*this == obj);
    }

    bool operator < (const Edge<E>& obj ) {
        return (data < obj.data);
    }

    bool operator > (const Edge<E>& obj ) {
        return (data > obj.data);
    }
};

template<typename V, typename E>
class Graph : public Object
{
protected:
    template<typename T>
    DynamicArray<T>* toArray(LinkQueue<T>& queue);

    virtual bool isAdjacent(int i, int j) = 0;
    bool asUndirected();
    int find(Array<int>&p, int v);
    SharedPointer<Array<Edge<E>>> getUndirectedEdges();
public:
    virtual V getVertex(int i) = 0;
    virtual bool getVertex(int i, V& value) = 0;
    virtual bool setVertex(int i, const V& value) = 0;
    virtual SharedPointer<Array<int>> getAdjacent(int i) = 0;
    virtual E getEdge(int i, int j) = 0;
    virtual bool getEdge(int i, int j, E& value) = 0;
    virtual bool setEdge(int i, int j, const E& value) = 0;
    virtual bool removeEdge(int i, int j) = 0;
    virtual int vCount() = 0;
    virtual int eCount() = 0;
    virtual int OD(int i) = 0;
    virtual int ID(int i) = 0;

    virtual int TD(int i);

    SharedPointer<Array<int>> BFS(int i);
    SharedPointer<Array<int>> DFS(int i);

    // 76课
    SharedPointer<Array<Edge<E>>> prim(const E& LIMIT, bool isMin = true);
    SharedPointer<Array<Edge<E>>> kruskal(bool isMin = true);
    SharedPointer<Array<int>> dijkstra(int i, int j, const E& LIMIT);
    SharedPointer<Array<int>> floyd(int x, int y, const E& LIMIT);

};

template<typename V, typename E>
int Graph<V,E>::TD(int i) {
    return OD(i) + ID(i);
}

template<typename V, typename E>
template<typename T>
DynamicArray<T>* Graph<V,E>::toArray(LinkQueue<T>& queue) {
    DynamicArray<T>* ret = new DynamicArray<T>(queue.length());

    if ( ret != nullptr ) {
        for ( int i = 0; i < ret->length(); i++, queue.remove() ) {
            //ret->set(i, queue.front());   // 消除警告
            T v = queue.front();
            ret->set(i, v);
        }
    }
    else {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create ret obj...");
    }

    return ret;
}


template<typename V, typename E>
SharedPointer<Array<int>> Graph<V,E>::BFS(int i) {
    DynamicArray<int>* ret = nullptr;

    if ( (0 <= i) && (i < vCount()) ) {
        LinkQueue<int> q;
        LinkQueue<int> r;
        DynamicArray<bool> visited(vCount());

        for ( int i = 0; i < visited.length(); i++ ) {
            visited[i] = false;
        }
        q.add(i);

        while ( q.length() > 0 ) {
            int v = q.front();

            q.remove();
            if ( !visited[v] ) {
                SharedPointer<Array<int>> aj = getAdjacent(v);
                for ( int j = 0; j < aj->length(); j++ ) {
                    q.add((*aj)[j]);
                }
                r.add(v);
                visited[v] = true;
            }
        }
        ret = toArray(r);
    }
    else {
        THROW_EXCEPTION(InvalidParameterException, "Index i is invalid");
    }

    return ret;
}

template<typename V, typename E>
SharedPointer<Array<int>> Graph<V,E>::DFS(int i) {
    DynamicArray<int>* ret = nullptr;

    if ( (0 <= i) && (i < vCount()) ) {
        LinkStack<int> s;
        LinkQueue<int> r;
        DynamicArray<bool> visited(vCount());

        for ( int i = 0; i < visited.length(); i++ ) {
            visited[i] = false;
        }

        s.push(i);
        while ( s.size() > 0 ) {
            int v = s.top();
            s.pop();
            if ( !visited[v] ) {
                SharedPointer<Array<int>> aj = getAdjacent(v);
                for ( int j = aj->length()-1; j >= 0; j-- ) {
                    s.push((*aj)[j]);
                }
                r.add(v);
                visited[v] = true;
            }
        }
        ret = toArray(r);
    }
    else {
        THROW_EXCEPTION(InvalidParameterException, "Invalid parameter i...");

    }

    return ret;
}

template<typename V, typename E>
bool Graph<V,E>::asUndirected() {
    bool ret = true;

    for ( int i = 0; i < vCount(); i++ ) {
        for ( int j = 0; j < vCount(); j++ ) {
            if ( isAdjacent(i, j) ) {
                ret = ret && isAdjacent(j, i) &&
                      getEdge(i, j) == getEdge(j, i);
            }
        }
    }

    return ret;
}

// prim最小生成树原理:
// 1)
// 从顶点开始,把目前正在生长的树看做是一个磁铁,每加入了一个顶点,
// 那么这个新顶点就融入这个大磁铁中,同时新节点也带有磁性,
// 这颗磁铁树不断吸住最靠近磁铁的顶点(权值最小者),每次吸一个顶点
// 如此反复,知道所有顶点被吸住.
// 注意: 没有连通线的不被吸引
// 2)
// 关于软件具体实现中的权值最小的记录处理.
// 正在成长的树每发生一次变化,那么还没有被吸入这棵树的节点中,
// 只要是存在和这颗树有连接线的节点,都要重新计算节点到这棵树的
// 最小权值,注意: 是到这颗树的所有连通节点的权值的最小值,
// 那么我们没必要每次都兴师动众全部计算一遍,比如节点A, 它还没有
// 加入到这棵树中,我们记录到本次A到树的最小权值为10,那么树如果
// 添加了一个新节点B,我们只需要比较AB之间是否连通且权值小于10,
// 如果<10,就更新权值,并且记录下A和树中连通最小权值的点为"B",
// 这样就不必要将A和树中所有节点再来比较一遍.浪费光阴
template<typename V, typename E>
SharedPointer<Array<Edge<E>>> Graph<V,E>::prim(const E& LIMIT, bool isMin ) {
    LinkQueue<Edge<E>> ret;

    if ( asUndirected() ) {
        DynamicArray<int> adjVex(vCount());
        DynamicArray<bool> mark(vCount());
        DynamicArray<E> cost(vCount());
        SharedPointer<Array<int>> aj = nullptr;
        bool end = false;
        int v = 0;                  // 从0号节点开始建立树

        for ( int i = 0; i < vCount(); i++ ) {
            adjVex[i] = -1;
            mark[i] = false;
            cost[i] = LIMIT;
        }

        mark[v] = true;
        aj = getAdjacent(v);

        for ( int j = 0; j < aj->length(); j++ ) {
            int z = (*aj)[j];

            cost[z] = getEdge(v, z);
            adjVex[z] = v;
        }

        for ( int i = 1; (i < vCount()) && !end; i++) {
            E m = LIMIT;
            int k = -1;

            // 扫描节点中的"无业游民",找出和"树"最小权值的节点
            for (int j = 0; j < vCount(); j++ ) {
                if ( !mark[j] && (isMin ? (cost[j] < m) : (cost[j] > m)) ) {    // 备注: 这里用三目运算符,一定要把它整体括起来
                    m = cost[j];
                    k = j;              // k就是即将被"挑"出来的节点
                }
            }

            end = (k == -1);
            if ( !end ) {
                ret.add(Edge<E>(adjVex[k], k, getEdge(adjVex[k], k)));  // k节点加入树中,且记录下来
                mark[k] = true;

                aj = getAdjacent(k);

                // 现在k节点新加入了树中,那么所有和k节点相连且还没有加入树中的节点,更新一下和"树"之间的权值
                // 如果因为k的加入树,造成权值有变化,那么就要将相关信息更新
                for (int j = 0; j < aj->length(); j++ ) {
                    int z = (*aj)[j];           // 取出和k相连的一个节点

                    if ( !mark[z] &&
                         (isMin ? (getEdge(k, z) < cost[z]) : (getEdge(k, z) > cost[z])) ) {

                        cost[z] = getEdge(k, z);
                        adjVex[z] = k;              // 指向k
                    }
                }
            }
        }
    }
    else {
        THROW_EXCEPTION(InvalidOperationException, "Prim operation is for undieection graph only ... ");
    }

    if ( ret.length() != (vCount()-1) ) {
        THROW_EXCEPTION(InvalidOperationException, "No enough edge for Prim operation ...");
    }


    return toArray(ret);
}

template<typename V, typename E>
int Graph<V,E>::find(Array<int>&p, int v) {
    while ( p[v] != -1 ) {
        v = p[v];
    }

    return v;
}

template<typename V, typename E>
SharedPointer<Array<Edge<E>>> Graph<V,E>::getUndirectedEdges() {
    DynamicArray<Edge<E>>* ret = nullptr;

    if ( asUndirected() ) {
        LinkQueue<Edge<E>> queue;

        for ( int i = 0; i < vCount(); i++ ) {
            for ( int j = i; j < vCount(); j++ ) {  // 注意: 这里要从"i"开始,否则里面会有重复边
                if ( isAdjacent(i, j)) {
                    queue.add(Edge<E>(i, j, getEdge(i, j)));
                }
            }
        }
        ret = toArray(queue);
    }
    else {
        THROW_EXCEPTION(InvalidOperationException, "This function is for undirected graph only ...");
    }

    return ret;
}

// kruskal算法描述:
// A)
//  将树棍的长度(权值)从小到大排序后,每次从剩下的棍子中挑出一根最短者
//  棍子有两个顶点,此时分情况:
//      1) 两个顶点不属于任何链条, 此时这两个顶点暂时自己形成一个独立的链条
//      2) 有一个顶点属于某个链条，另一个不属于任何链条,那么这个空闲节点就会挂到链条中
//         此时链条的头部变成了"谁"?要分两种情况,看新加入的节点是b节点还是e节点,且与下面的程序代码
//         p[e] = b; 有关, 其实: 代码也可以改成: p[b] = e;
//         区别就在于是: 新加入的节点 "作为链条的头部" 还是 "指向目前的头部"
//         把它想象成一个钥匙串,这个头部就是那个钥匙环
//         比如, b节点属于一个链条,e节点是一个空闲节点,
//         因为: p[e] = b, 那显然,e加入了这个链条,且e位置指向了链条的头部
//         注意,链条的头部可不一定是b的实际值,因为find()中经过了多次跳转,最终获得的是链条的头部节点序号
//         简而言之,如果某个节点k在链条中,只要调用find(k),就会找到这个链条的头部节点序号
//         这个头部节点是我们程序员自己特意安排的,实际上链条中的任何一个节点都被设计成头部节点
//         比如刚才说的把代码p[e]=b改为p[b]=e, 那么新加入的节点就会成为头部
//         find()的功能就是返回“节点所属的链条”的头部节点序号
//      3) 两个顶点分属两个链条,此时两根链条就会合并成一个整体
//      4) 两个顶点已经属于一根相同的链条,此根棍棒被丢弃，因为有回环
// B)
//  在程序运行过程中,可能同时存在几个链条在逐渐成长壮大+融合的现象
//
template<typename V, typename E>
SharedPointer<Array<Edge<E>>> Graph<V,E>::kruskal(bool isMin) {
    LinkQueue<Edge<E>> ret;
    SharedPointer<Array<Edge<E>>> edges = getUndirectedEdges();
    DynamicArray<int> p(vCount());

    for ( int i = 0; i <p.length(); i++ ) {
        p[i] = -1;
    }

    Sort::Shell(*edges, isMin);

    for ( int i = 0; (i < edges->length()) && (ret.length() < (vCount()-1)); i++ ) {
        int b = find(p, (*edges)[i].b);
        int e = find(p, (*edges)[i].e);

        if ( b != e ) {
            p[e] = b;
            ret.add((*edges)[i]);
        }
    }

    if ( ret.length() != (vCount() -1)) {
        THROW_EXCEPTION(InvalidOperationException, "No enough edges for Kruskai operation ...");
    }

    return toArray(ret);
}

template<typename V, typename E>
SharedPointer<Array<int>> Graph<V,E>::dijkstra(int i, int j, const E& LIMIT) {
    LinkQueue<int> ret;

    if ( (0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()) ) {
        DynamicArray<E>    dist(vCount());
        DynamicArray<int>  path(vCount());
        DynamicArray<bool> mark(vCount());

        for ( int k = 0; k < vCount(); k++ ) {
            mark[k] = false;
            path[k] = -1;
            dist[k] = isAdjacent(i, k) ? (path[k]=i, getEdge(i,k)) : LIMIT;
        }
        mark[i] = true;

        for ( int k = 0; k < vCount(); k++ ) {
            E m = LIMIT;
            int u = -1;

            for ( int w = 0; w < vCount(); w++ ) {
                if ( !mark[w] && (dist[w] < m) ) {
                    m = dist[w];
                    u = w;
                }
            }

            if ( u == -1 ) {
                break;
            }
            mark[u] = true;

            for ( int w = 0; w < vCount(); w++ ) {
                if ( !mark[w] && isAdjacent(u, w) && (dist[u]+getEdge(u, w)) < dist[w] ) {
                    dist[w] = dist[u] + getEdge(u, w);
                    path[w] = u;
                }
            }
        }
        LinkStack<int> s;
        s.push(j);
        for ( int k = path[j]; k != -1; k = path[k] ) {
            s.push(k);
        }
        while ( s.size() > 0 ) {
            ret.add(s.top());
            s.pop();
        }
    }
    else {
        THROW_EXCEPTION(InvalidParameterException, "Index <i,j> is invalid ...");
    }

    if ( ret.length() < 2 ) {
        THROW_EXCEPTION(ArithmeticException, "There is no path from i to j ...");
    }

    return toArray(ret);
}

template<typename V, typename E>
SharedPointer<Array<int>> Graph<V,E>::floyd(int x, int y, const E& LIMIT) {
    LinkQueue<int> ret;

    if ( (0 <= x) && (x < vCount()) && (0 <= y) && (y < vCount()) ) {
        DynamicArray<DynamicArray<E>> dist(vCount());
        DynamicArray<DynamicArray<int>> path(vCount());

        for ( int k = 0; k < vCount(); k++ ) {
            dist[k].resize(vCount());
            path[k].resize(vCount());
        }

        for ( int i = 0; i < vCount(); i++ ) {
            for ( int j = 0; j < vCount(); j++ ) {
                path[i][j] = -1;
                dist[i][j] = isAdjacent(i, j) ? (path[i][j] = j, getEdge(i, j)) : LIMIT;
            }
        }

        for ( int k = 0; k < vCount(); k++ ) {
            for ( int i = 0; i < vCount(); i++ ) {
                for ( int j = 0; j < vCount(); j++ ) {
                    if ( (dist[i][k] + dist[k][j]) < dist[i][j] ) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        path[i][j] = path[i][k];
                    }
                }
            }
        }

        while ( (x != -1) && (x != y) ) {
            ret.add(x);
            x = path[x][y];
        }

        if ( x != -1 ) {
            ret.add(x);
        }
    }
    else {
        THROW_EXCEPTION(InvalidParameterException, "index<x,y> is invalid...");
    }

    if ( ret.length() < 2 ) {
        THROW_EXCEPTION(ArithmeticException, "There is no path from x to y...");
    }

    return toArray(ret);
}



}



#endif // GRAPH_H
