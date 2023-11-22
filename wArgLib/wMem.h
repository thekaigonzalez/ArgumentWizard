// $Id: wMem.h
// Implements memory pooling

#ifndef AWIZ_WMEM_H
#define AWIZ_WMEM_H

#include <stdlib.h>

struct wMemPool;
typedef struct wMemPool wMemPool;

// initializes the memory pool
wMemPool *wMemPoolCreate ();

// allocates memory on the memory pool and returns it, this is a simple way to
// keep track of all allocated memory and reduces the risk of memory leaks or
// fragmentation
void *wMemAlloc (wMemPool *self, size_t size);
void *wMemRealloc(wMemPool *self, void* ptr, size_t size);
void wMemPoolDestroy (wMemPool *self);

#endif // AWIZ_WMEM_H
