// $Id: wValue.c
#include "wValue.h"
#include "wError.h"
#include "wDef.h"

#include <ctype.h>
#include <string.h>

struct wValue
{
  wMemPool *_pool; // memory pool
  int size; // strictly for lists
  int capacity;
  union
  {
    char *str;
    int number;
    _Bool boolean;
    char** lstrs;
  };

  wType type;
};

wValue *
wValueCreate (wMemPool *opt)
{
  wValue *self = (wValue *)wMemAlloc (opt, sizeof (wValue));
  self->_pool = opt;
  self->lstrs = (char **)wMemAlloc (opt, sizeof (char *) * WARGLIB_DEFAULT_POOL_INCREMENT);
  self->capacity = WARGLIB_DEFAULT_POOL_INCREMENT;
  self->size = 0;

  if (!self) { 
    wErrorDisplay ("wValueCreate: out of memory");
    return NULL;
  }

  return self;
}

void
wValueSetStr (wValue *self, char *str)
{
  self->type = WTYPE_STRING;
  self->str = str;
}

void
wValueSetNumber (wValue *self, int number)
{
  self->type = WTYPE_NUMBER;
  self->number = number;
}

void
wValueSetBoolean (wValue *self, _Bool boolean)
{
  self->type = WTYPE_BOOLEAN;
  self->boolean = boolean;
}

void
wValueSetList (wValue *self)
{
  if (!self) {
    wErrorDisplay("wValueSetList: self is null?\n");
    return;
  }
  self->type = WTYPE_LIST;
  self->size = 0;
}

void
wValueAppendList (wValue *self, char *str)
{
  if (self->size >= self->capacity) {
    self->lstrs = realloc (
        self->lstrs,
        sizeof (char *) * (self->capacity + WARGLIB_DEFAULT_POOL_INCREMENT)
    );
  }
  self->lstrs[self->size] = str;
  self->size++;
}

char **
wValueList (wValue *self)
{
  return self->lstrs;
}

int
wValueListSize (wValue *self)
{
  if (!self || !self->size) {
    return -1;
  }
  return self->size;
}

char *
wValueListAt (wValue *self, int index)
{
  if (index < 0 || index >= self->size) {
    return NULL;
  }
  return self->lstrs[index];
}

char *
wValueStr (wValue *self)
{
  if (self && self->type == WTYPE_STRING) {
    return self->str;
  }
  
  return NULL;
}

int
wValueNumber (wValue *self)
{
  if (self->type == WTYPE_NUMBER) {
    return self->number;
  }
  return -1;
}

_Bool
wValueBoolean (wValue *self)
{
  if (!self || !self->type) {
    return false;
  }

  if (self->type == WTYPE_BOOLEAN) {
    return self->boolean;
  }
  return false;
}

wValue *
wValueFromString (wMemPool *opt, char *str)
{
  wValue *value = wValueCreate(opt);

  for (int i = 0; i < strlen(str); i++) {
    if (str[i] == '=') {
      value->str = str + i + 1;
      value->type = WTYPE_STRING;
      return value;
    }
  }

  if (isdigit(str[0])) {
    value->number = strtoul(str, NULL, 10);
    value->type = WTYPE_NUMBER;
  }

  else if (strcmp(str, "true") == 0 || strcmp(str, "false") == 0) {
    value->boolean = (strcmp(str, "true") == 0) ? true : false;
    value->type = WTYPE_BOOLEAN;
  }

  else {
    value->str = str;
    value->type = WTYPE_STRING;
  }

  return value;
}

wType
wValueType (wValue *self)
{
  if (!self || !self->type) {
    return WTYPE_UNKNOWN;
  }

  return self->type;
}
