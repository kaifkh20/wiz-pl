#ifndef wiz_mem_h
#define wiz_mem_h

#include "common.h"
#include "stdlib.h"

void* reallocate(void* pointer,size_t oldSize,size_t newSize);

#define GROW_CAPACITY(capacity) \
        ((capacity)<8?8:capacity*2)

#define GROW_ARRAY(type,pointer,oldCount,newCount)\
        (type*)reallocate(pointer,sizeof(type)*oldCount,sizeof(type)*newCount)

#define FREE_ARRAY(type,pointer,oldCount)\
        reallocate(pointer,sizeof(type)*oldCount,0)
#endif 