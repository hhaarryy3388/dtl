#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "Graph.h"
#include "Exception.h"
#include "DynamicArray.h"

namespace DTLib {

template<int N, typename V, typename E>
class MatrixGraph : public Graph<V,E>
{
protected:
    V* m_vertexes[N];
    E* m_edges[N][N];
    int m_eCount;
public:
    MatrixGraph();
    ~MatrixGraph();

    V getVertex(int i);
    bool getVertex(int i, V& value);
    bool setVertex(int i, const V& value);
    SharedPointer<Array<int>> getAdjacent(int i);
    E getEdge(int i, int j);
    bool getEdge(int i, int j, E& value);
    bool setEdge(int i, int j, const E& value);
    bool removeEdge(int i, int j);
    int vCount();
    int eCount();
    int OD(int i);
    int ID(int i);

    bool isAdjacent(int i, int j);
};

template<int N, typename V, typename E>
MatrixGraph<N,V,E>::MatrixGraph() {
    for (int i = 0; i < N; i++ ) {
        m_vertexes[i] = nullptr;

        for ( int j = 0; j < N; j++ ) {
            m_edges[i][j] = nullptr;
        }
    }

    m_eCount = 0;
}

template<int N, typename V, typename E>
MatrixGraph<N,V,E>::~MatrixGraph() {
    for (int i = 0; i < N; i++ ) {
        for ( int j = 0; j < N; j++ ) {
            delete m_edges[i][j];
        }

        delete m_vertexes[i];
    }
}

template<int N, typename V, typename E>
V MatrixGraph<N,V,E>::getVertex(int i) {
    V  ret;

    if ( !getVertex(i, ret) ) {
        THROW_EXCEPTION(InvalidParameterException, "Invalid parameter for getVertex");
    }

    return ret;
}

template<int N, typename V, typename E>
bool MatrixGraph<N,V,E>::getVertex(int i, V& value) {
    bool ret = (0 <= i) && (i < vCount());

    if ( ret ) {
        if ( m_vertexes[i] != nullptr ) {
            value = *(m_vertexes[i]);
        }
        else {
            THROW_EXCEPTION(InvalidOperationException, "No value assign on the vertex");
        }
    }

    return ret;
}

template<int N, typename V, typename E>
bool MatrixGraph<N,V,E>::setVertex(int i, const V& value) {
    bool ret = ( 0 <= i && i < vCount() );

    if ( ret ) {
        V* data = m_vertexes[i];

        if ( data == nullptr ) {
            data = new V();
        }

        if ( data != nullptr ) {
            *data = value;
            m_vertexes[i] = data;
        }
        else {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to store new vertex value... ");
        }
    }

    return ret;
}

template<int N, typename V, typename E>
SharedPointer<Array<int>> MatrixGraph<N,V,E>::getAdjacent(int i) {
    DynamicArray<int>* ret;

    if ( ( 0 <= i && i < vCount() ) ) {
        int n = 0;
        for ( int j = 0; j < vCount(); j++ ) {
            if ( m_edges[i][j] != nullptr ) {
                n++;
            }
        }
        ret = new DynamicArray<int>(n);
        if ( ret != nullptr ) {
            for ( int j = 0, k = 0; j < vCount(); j++ ) {
                if ( m_edges[i][j] != nullptr ) {
                    ret->set(k++, j);
                }
            }
        }
        else {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create ret obj...");
        }
    }
    else {
        THROW_EXCEPTION(InvalidParameterException, "Index i is invalid...");
    }

    return ret;
}

template<int N, typename V, typename E>
E MatrixGraph<N,V,E>::getEdge(int i, int j) {
    E  ret;

    if ( !getEdge(i, j, ret) ) {
        THROW_EXCEPTION(InvalidParameterException, "Edge<i,j> is invalid...");
    }

    return ret;
}

template<int N, typename V, typename E>
bool MatrixGraph<N,V,E>::getEdge(int i, int j, E& value) {
    bool ret = ( 0 <= i && i < vCount() &&
                 0 <= j && j < vCount());

    if ( ret ) {
        if ( m_edges[i][j] != nullptr ) {
            value = *(m_edges[i][j]);
        }
        else {
            THROW_EXCEPTION(InvalidOperationException, "No value be assigned to vertex... ");
        }
    }

    return ret;

}

template<int N, typename V, typename E>
bool MatrixGraph<N,V,E>::setEdge(int i, int j, const E& value) {
    bool ret = ( 0 <= i && i < vCount() &&
                 0 <= j && j < vCount());

    if ( ret ) {
        E* ne = m_edges[i][j];

        if ( ne == nullptr ) {
            ne = new E();

            if ( ne != nullptr ) {
                *ne = value;
                m_edges[i][j] = ne;
                m_eCount++;
            }
            else {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to store Edge value...");
            }
        }
        else {
            *ne = value;
        }
    }

    return ret;
}

template<int N, typename V, typename E>
bool MatrixGraph<N,V,E>::removeEdge(int i, int j) {
    bool ret = ( 0 <= i && i < vCount() &&
                 0 <= j && j < vCount());

    if ( ret ) {
        E* toDel = m_edges[i][j];
        m_edges[i][j] = nullptr;

        if ( toDel != nullptr ) {
            m_eCount--;
            delete toDel;
        }
    }

    return ret;
}

template<int N, typename V, typename E>
int MatrixGraph<N,V,E>::vCount() {
    return N;
}

template<int N, typename V, typename E>
int MatrixGraph<N,V,E>::eCount() {
    return m_eCount;
}

template<int N, typename V, typename E>
int MatrixGraph<N,V,E>::OD(int i) {
    int ret = 0;

    if ( (0 <= i) && (i < vCount()) ) {
        for ( int j = 0; j < vCount(); j++ ) {
            if ( m_edges[i][j] != nullptr ) {
                ret++;
            }

        }
    }
    else {
        THROW_EXCEPTION(InvalidParameterException, "Index i is invalid...");
    }

    return ret;
}

template<int N, typename V, typename E>
int MatrixGraph<N,V,E>::ID(int i) {
    int ret = 0;

    if ( (0 <= i) && (i < vCount()) ) {
        for ( int j = 0; j < vCount(); j++ ) {
            if ( m_edges[j][i] != nullptr ) {
                ret++;
            }

        }
    }
    else {
        THROW_EXCEPTION(InvalidParameterException, "Index i is invalid...");
    }

    return ret;

}

template<int N, typename V, typename E>
bool MatrixGraph<N,V,E>::isAdjacent(int i, int j) {
    return (0 <= i) && (i < vCount() ) &&
           (0 <= j) && (j < vCount() ) &&
           m_edges[i][j] != nullptr;
}







}


#endif // MATRIXGRAPH_H
