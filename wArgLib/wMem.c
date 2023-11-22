// $Id: wMem.c
// Implements memory pooling

#include "wMem.h"
#include "wDef.h"
#include "wError.h"

struct wMemPool
{
  void **ptr;
  int size;
  int capacity;
};

wMemPool *
wMemPoolCreate ()
{
  wMemPool *self = malloc (sizeof (wMemPool));

  if (!self)
    {
      wErrorDisplay ("wMemPoolCreate: out of memory");
      return NULL;
    }

  self->ptr = malloc (sizeof (void *) * WARGLIB_DEFAULT_POOL_INCREMENT);
  self->size = 0;
  self->capacity = WARGLIB_DEFAULT_POOL_INCREMENT;

  return self;
}

void *
wMemAlloc (wMemPool *self, size_t size)
{
  if (!self || size < 0 || !self->ptr)
    {
      wErrorDisplay ("wMemAlloc: self is null?");
      return NULL;
    }

  if (self->size >= self->capacity)
    {
      self->ptr = realloc (
          self->ptr,
          sizeof (void *) * (self->capacity + WARGLIB_DEFAULT_POOL_INCREMENT));
      self->capacity += WARGLIB_DEFAULT_POOL_INCREMENT;
    }

  void *ptr = calloc (size, 1);

  if (!ptr)
    {
      wErrorDisplay ("wMemAlloc: out of memory");
      return NULL;
    }

  self->ptr[self->size]
      = ptr;    // allocate the memory then store it to free it later
  self->size++; // increment the size

  return ptr;
}

void *
wMemRealloc (wMemPool *self, void *ptr, size_t size)
{
  // reallocate memory into a new location
  void* p2 = realloc (ptr, size);

  if (!p2) {
    wErrorDisplay ("wMemRealloc: out of memory");
    return NULL;
  }

  if (self->size >= self->capacity)
  {
    self->ptr = realloc (
        self->ptr,
        sizeof (void *) * (self->capacity + WARGLIB_DEFAULT_POOL_INCREMENT));
    self->capacity += WARGLIB_DEFAULT_POOL_INCREMENT;
  }

  self->ptr[self->size] = p2;
  self->size++;

  return p2;
}

void
wMemPoolDestroy (wMemPool *self)
{
  if (!self)
    {
      wErrorDisplay ("wMemPoolDestroy: self is null?");
      return;
    }

  if (!self->ptr)
    {
      wErrorDisplay ("wMemPoolDestroy: self->ptr is null?");
      return;
    }

  if (self->size < 0)
    {
      wErrorDisplay ("wMemPoolDestroy: self->size can not be less than 0");
    }

  for (int i = 0; i < self->size; i++)
    {
      free (self->ptr[i]);
    }

  free (self->ptr);
  free (self);
}
