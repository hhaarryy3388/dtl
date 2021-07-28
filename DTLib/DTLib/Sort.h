#ifndef SORT_H
#define SORT_H

#include "Object.h"
#include "Array.h"

namespace DTLib {

class Sort : public Object
{
private:
    Sort();
    Sort(const Sort&);
    Sort& operator = (const Sort&);

    template<typename T>
    static void Swap(T& a, T& b)
    {
        T c(a);
        a = b;
        b = c;
    }

    template<typename T>
    static void Merge(T src[], T helper[], int begin, int mid, int end, bool minSort );
    template<typename T>
    static void Merge(T src[], T helper[], int begin, int end, bool minSort );

    template<typename T>
    static int Partition(T array[], int begin, int end, bool minSort = true);
    template<typename T>
    static void Quick(T array[], int begin, int end, bool minSort);
public:
    template<typename T>
    static void Select(T array[], int len, bool minSort = true);

    template<typename T>
    static void Insert(T array[], int len, bool minSort = true);

    template<typename T>
    static void Bubble(T array[], int len, bool minSort = true);

    template<typename T>
    static void Shell(T array[], int len, bool minSort = true);

    template<typename T>
    static void Merge(T array[], int len, bool minSort = true);

    template<typename T>
    static void Quick(T array[], int len, bool minSort = true);
    //------------------------------------------------------------
    template<typename T>
    static void Select(Array<T> &array, bool minSort = true);
    template<typename T>
    static void Insert(Array<T> &array, bool minSort = true);

    template<typename T>
    static void Bubble(Array<T> &array, bool minSort = true);

    template<typename T>
    static void Shell(Array<T> &array, bool minSort = true);

    template<typename T>
    static void Merge(Array<T> &array, bool minSort = true);

    template<typename T>
    static void Quick(Array<T> &array, bool minSort = true);
};

template<typename T>
void Sort::Select(T array[], int len, bool minSort) {
    for ( int i = 0; i < len; i++ ) {
        int k = i;
        for ( int j = i + 1; j < len; j++ ) {
            if ( minSort ? (array[j] < array[k]) : (array[j] > array[k]) ) {
                k = j;
            }
        }

        if ( i != k ) {
            Swap(array[i], array[k]);
        }
    }
}

template<typename T>
void Sort::Insert(T array[], int len, bool minSort) {
    for ( int i = 1; i < len; i++ ) {
        int k = i;
        T e = array[i];     // 先保存,因为本元素的位置有可能会因为移位被占据

        for ( int j = i-1; (j >= 0) && (minSort ? (e < array[j]) : (array[j] > e)); j-- ) {
            array[j+1] = array[j];
            k = j;
        }

        if ( i != k ) {
            array[k] = e;
        }
    }
}

template<typename T>
void Sort::Bubble(T array[], int len, bool minSort) {
    bool exchange = true;

    for ( int i = 0; (i<len) && exchange; i++) {
        exchange = false;
        for ( int j = len-1; j > i; j-- ) {
            if ( minSort ? (array[j] < array[j-1]) : (array[j] > array[j-1]) ) {
                Swap(array[j], array[j-1]);
                exchange = true;
            }
        }
    }
}

template<typename T>
void Sort::Shell(T array[], int len, bool minSort) {
    int d = len;

    do {
        d = d / 3 + 1;

        for ( int i = d; i < len; i+=d ) {
            int k = i;
            T e = array[i];     // 先保存,因为本元素的位置有可能会因为移位被占据

            for ( int j = i-d; (j >= 0) && (minSort ? (e < array[j]) : (e > array[j])); j-=d ) {
                array[j+d] = array[j];
                k = j;
            }

            if ( i != k ) {
                array[k] = e;
            }
        }

    } while ( d > 1 );
}

// 归并排序
template<typename T>
void Sort::Merge(T src[], T helper[], int begin, int mid, int end, bool minSort ) {
    int i = begin;
    int j = mid + 1;
    int k = begin;

    while ( (i <= mid) && (j <= end) ) {
        if ( minSort ? (src[i] < src[j]) : (src[i] > src[j]) ) {
            helper[k++] = src[i++];
        }
        else {
            helper[k++] = src[j++];
        }
    }

    while ( i <= mid ) {
        helper[k++] = src[i++];
    }
    while ( j <= end ) {
        helper[k++] = src[j++];
    }
    for ( i = begin; i <= end; i++ ) {
        src[i] = helper[i];
    }
}

template<typename T>
void Sort::Merge(T src[], T helper[], int begin, int end, bool minSort ) {
    if ( begin < end ) {
        int mid = (begin + end ) / 2;

        Merge(src, helper, begin, mid, minSort);
        Merge(src, helper, mid + 1, end, minSort);
        Merge(src, helper, begin, mid, end, minSort);
    }
}

template<typename T>
void Sort::Merge(T array[], int len, bool minSort) {
    T* helper = new T[len];

    if ( helper != nullptr ) {
        Merge(array, helper, 0, len-1, minSort);
    }

    delete[] helper;
}

template<typename T>
int Sort::Partition(T array[], int begin, int end, bool minSort) {
    T pv = array[begin];

    while ( begin < end ) {
        while ( (begin < end) && (minSort ? (array[end] > pv) : (array[end] < pv)) ) {
            end--;
        }
        Swap( array[begin], array[end] );

        while ( (begin < end) && (minSort ? (array[begin] <= pv) : (array[begin] >= pv) ) ) {
            begin++;
        }
        Swap( array[begin], array[end] );
    }
    array[begin] = pv;

    return begin;
}

template<typename T>
void Sort::Quick(T array[], int begin, int end, bool minSort) {
    if ( begin < end ) {
        int pivot = Partition(array, begin, end, minSort);
        Quick(array, begin, pivot-1, minSort);
        Quick(array, pivot+1, end, minSort);
    }
}

template<typename T>
void Sort::Quick(T array[], int len, bool minSort) {
    Quick(array, 0, len-1, minSort);
}



template<typename T>
void Sort::Select(Array<T>& array, bool minSort ) {
    Select(array.array(), array.length(), minSort);
}

template<typename T>
void Sort::Insert(Array<T>& array, bool minSort ) {
    Insert(array.array(), array.length(), minSort);
}

template<typename T>
void Sort::Bubble(Array<T>& array, bool minSort ) {
    Bubble(array.array(), array.length(), minSort);
}

template<typename T>
void Sort::Shell(Array<T>& array, bool minSort ) {
    Shell(array.array(), array.length(), minSort);
}

template<typename T>
void Sort::Merge(Array<T>& array, bool minSort ) {
    Merge(array.array(), array.length(), minSort);
}

template<typename T>
void Sort::Quick(Array<T>& array, bool minSort ) {
    Quick(array.array(), array.length(), minSort);
}






}   // namespace



#endif // SORT_H
