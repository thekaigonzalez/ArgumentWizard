// $Id: wOptions.c
// Defines options shared across wArgLib

#include "wOptions.h"
#include "wDef.h"
#include "wError.h"
#include "wFlag.h"
#include "wMem.h"
#include "wStraggly.h"

#include <string.h>

struct wOptions
{
  wMemPool *__pool;
  wStraggly *straggly;
  wFlag **flags;

  // flags
  int flags_count;
  int flags_capacity;
};

wOptions *
wOptionsCreate ()
{
  wOptions *self = (wOptions *)malloc (sizeof (wOptions));

  if (!self)
    {
      wErrorDisplay ("wOptionsCreate: out of memory");
      return NULL;
    }

  self->__pool = wMemPoolCreate ();

  self->flags = wMemAlloc (self->__pool,
                           sizeof (wFlag *) * WARGLIB_DEFAULT_POOL_INCREMENT);
  self->flags_count = 0;
  self->flags_capacity = WARGLIB_DEFAULT_POOL_INCREMENT;

  self->straggly = wMemAlloc (
      self->__pool, sizeof (wStraggly *) * WARGLIB_DEFAULT_POOL_INCREMENT);

  if (!self->__pool)
    {
      wErrorDisplay ("wOptionsCreate: out of memory");
      return NULL;
    }

  return self;
}

wMemPool *
wOptionsGetPool (wOptions *self)
{
  if (!self)
    {
      wErrorDisplay ("wOptionsGetPool: self is null");
      return NULL;
    }

  if (!self->__pool)
    {
      wErrorDisplay ("wOptionsGetPool: self->__pool is null");
      return NULL;
    }

  return self->__pool;
}

void
wOptionsAddFlag (wOptions *self, char opt_short, char *opt_long, char *help,
                 FlagType type)
{
  if (!self)
    {
      wErrorDisplay ("wOptionsAddFlag: self is null");
      return;
    }

  if (!self->__pool)
    {
      wErrorDisplay ("wOptionsAddFlag: self->__pool is null");
      return;
    }

  if (self->flags_count >= self->flags_capacity)
    {
      self->flags_capacity += WARGLIB_DEFAULT_POOL_INCREMENT;
      self->flags
          = realloc (self->flags, sizeof (wFlag *) * self->flags_capacity);
    }

  wFlag *flag = wFlagCreate (self->__pool);
  wFlagSet (flag, opt_short, opt_long, help, type);

  self->flags[self->flags_count] = flag;
  self->flags_count++;
}

void
wOptionsDestroy (wOptions *self)
{
  if (!self)
    {
      wErrorDisplay ("wOptionsDestroy: self is null");
      return;
    }

  if (!self->__pool)
    {
      wErrorDisplay ("wOptionsDestroy: self->__pool is null");
      return;
    }

  wMemPoolDestroy (self->__pool);

  free (self);
}

wFlag **
wOptionsFlags (wOptions *self)
{
  if (!self)
    {
      wErrorDisplay ("wOptionsFlags: self is null");
    }
  return self->flags;
}

int
wOptionsFlagsCount (wOptions *self)
{
  return self->flags_count;
}

void
wOptionsAddOptions (wOptions *src, wOptions *dest)
{
  if (!src || !dest)
    {
      wErrorDisplay ("wOptionsAddOptions: malformed");
      return;
    }

  for (int i = 0; i < src->flags_count; i++)
    {
      wFlag *flag = src->flags[i];

      wOptionsAddFlag (dest, wFlagShort (flag), wFlagLong (flag),
                       wFlagHelp (flag), wFlagType (flag));
    }
}

int
wOptionsStragglyCount (wOptions *self)
{
  return wStragglySize (self->straggly);
}

char *
wOptionsGetStraggly (wOptions *self, int index)
{
  if (!self)
    {
      wErrorDisplay ("wOptionsGetStraggly: self is null");
      return NULL;
    }
  return wStragglyAt (self->straggly, index);
}

wStraggly *
wOptionsGetStragglys (wOptions *self)
{
  return self->straggly;
}

void
wOptionsAddStraggly (wOptions *self, char *src)
{
  if (!self)
    {
      wErrorDisplay ("wOptionsAddStraggly: self is null");
      return;
    }

  if (!self->__pool)
    {
      wErrorDisplay ("wOptionsAddStraggly: self->__pool is null");
      return;
    }

  wStragglyAppend (self->__pool, self->straggly, src);
}

wFlag *
wOptionsGetFlag (wOptions *self, int index)
{
  if (!self)
    {
      wErrorDisplay ("wOptionsFlagShort: self is null");
      return NULL;
    }

  if (!self->__pool)
    {
      wErrorDisplay ("wOptionsFlagShort: self->__pool is null");
      return NULL;
    }

  if (index < 0 || index >= self->flags_count)
    {
      wErrorDisplay ("wOptionsFlagShort: index is out of bounds");
      return NULL;
    }

  return self->flags[index];
}

wFlag *
wOptionsFindFlag (wOptions *self, char opt_short)
{
  if (!self || !self->__pool)
    {
      wErrorDisplay ("wOptionsFindFlag: malformed");
      return NULL;
    }

  for (int i = 0; i < self->flags_count; i++)
    {
      wFlag *current = wOptionsGetFlag (self, i);

      if (wFlagShort (current) == opt_short)
        {
          return current;
        }
    }

  return NULL;
}

wFlag *
wOptionsFindFlagBoth (wOptions *self, char opt_short, char *opt_long)
{
  if (!self || !self->__pool)
    {
      wErrorDisplay ("wOptionsFindFlag: malformed");
      return NULL;
    }

  for (int i = 0; i < self->flags_count; i++)
    {
      wFlag *current = wOptionsGetFlag (self, i);

      if (wFlagShort (current) == opt_short
          || strcmp (wFlagLong (current), opt_long) == 0)
        {
          return current;
        }
    }
}

wFlag *
wOptionsFindFlagLong (wOptions *self, char *opt_long)
{
  if (!self || !self->__pool) {
    wErrorDisplay ("wOptionsFindFlag: options are broken");
    return NULL;
  }
  for (int i = 0; i < self->flags_count; i++) {
    wFlag *current = wOptionsGetFlag (self, i);
    if (strcmp (wFlagLong (current), opt_long) == 0) {
      return current;
    }
  }
  return NULL;

}
