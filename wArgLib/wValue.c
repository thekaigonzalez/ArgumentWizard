// $Id: wValue.c
#include "wValue.h"
#include "wError.h"

#include <ctype.h>
#include <string.h>

struct wValue
{
  union
  {
    char *str;
    int number;
    _Bool boolean;
  };

  wType type;
};

wValue *
wValueCreate (wMemPool *opt)
{
  wValue *self = (wValue *)wMemAlloc (opt, sizeof (wValue));
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
