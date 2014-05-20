#include <new>
#include <stdio.h>
#include <cstring>
#include <stdlib.h>


#define GC_MPS 1

#define TESTING
#define THROW(x) throw(x);
#define THROW_OUT_OF_MEMORY() THROW("Out of memory")

#define LOG(x) printf("...");printf x;


#define GC_SCAN_ARGS_PROTOTYPE int
#define GC_RESULT int
#define GC_RES_OK 0


#ifndef GC_MPS

#define GC_VECTOR_ALLOCATE(_T_,_C_,_ADDR_) {                            \
        size_t newBytes = vec::MutableVector<value_type>::_sizeof(_C_); \
        myAddress = (vec::MutableVector<value_type>*)malloc(newBytes);  \
        if (!myAddress) THROW_OUT_OF_MEMORY();                          \
        LOG(("malloc@%p %lu bytes\n",myAddress,newBytes));              \
    }




#define GC_RESERVE_MUTABLE_VECTOR_RESIZE(_T_,_OLD_,_NEW_SIZE_,_NEW_) { \
        GC_RESERVE_MUTABLE_VECTOR_ALLOCATE(_T_,_NEW_SIZE_,_NEW_);       \
        for ( size_t zi(0); zi<_OLD_->_End; ++zi ) {                   \
            _NEW_->operator[](zi) = _OLD_->operator[](zi);             \
        };                                                             \
        _NEW_->_End = _OLD_->_End;                                     \
    }
#define GC_RESERVE_MUTABLE_VECTOR_FREE(/*_T_,*/_ADDR_) free(_ADDR_);


#include "vectorCore.h"


class X {
public:
    int x;
    X(int a) : x(a) {};
    X() : x(0) {};
    void dump() {
        printf("%d  ", x);
    };
};

template <typename X>
void dump(vec::MutableVector<X>*& mv )
{
    printf("vec@%p _C[%lu] _E[%lu] ", mv, mv->capacity(), mv->size() );
    for ( int i(0); i<(*mv).capacity(); ++i ) {
        if (i == (*mv).size()) printf("| ");
        (*mv)[i].dump();
    }
    printf("\n");
}    

int main(int argc, const char* argv[])
{
    int N = 4;
    printf("Creating vec(4)\n");
    vec::MutableVector<X>* v = vec::MutableVector<X>::create(4);
    dump(v);
    printf("About to Push_back X(2)\n");
    Push_back(v,X(2));
    dump(v);
    printf("About to Push_back %d times X(i)\n", N);
    for ( int i(0); i<N; ++i ) {Push_back(v,X(i));}
    dump(v); 
    for (int j(0); j<20; ++j ) {
    printf("About to Push_back %d times X(i)\n", N);
    for ( int i(0); i<N; ++i ) {Push_back(v,X(i));}
    dump(v);
    }
   printf("\n");

}


