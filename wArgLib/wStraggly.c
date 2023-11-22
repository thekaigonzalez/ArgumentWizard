// $Id: wStraggly.c
// Defines a list of Straggly arguments
// These are arguments without a `-' prefix

#include "wStraggly.h"
#include "wDef.h"
#include "wMem.h"

struct wStraggly
{
  char **ptr;
  int size;
  int capacity;
};

wStraggly *
wStragglyCreate (wMemPool *options)
{
  wStraggly *self = (wStraggly *)wMemAlloc ((options), sizeof (wStraggly));

  self->ptr = (char **)wMemAlloc (
      (options), sizeof (char *) * WARGLIB_DEFAULT_POOL_INCREMENT);

  self->size = 0;
  self->capacity = WARGLIB_DEFAULT_POOL_INCREMENT;

  return self;
}

int
wStragglySize (wStraggly *self)
{
  if (!self)
    {
      return -1;
    }
  return self->size;
}

char **
wStragglies (wStraggly *self)
{
  if (!self)
    {
      return NULL;
    }
  return self->ptr;
}

char *
wStragglyAt (wStraggly *self, int index)
{
  return self->ptr[index];
}

char *
wStragglyName (wStraggly *self, int index)
{
  return self->ptr[index];
}

void
wStragglyAppend (wMemPool *p, wStraggly *self, char *str)
{
  if (self->size >= self->capacity)
    {
      self->capacity += WARGLIB_DEFAULT_POOL_INCREMENT;
      self->ptr
          = (char **)wMemRealloc (p, self->ptr, self->capacity * sizeof (char *));
    }

  self->ptr[self->size] = str;
  self->size++;

  return;
}
