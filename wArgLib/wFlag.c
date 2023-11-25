// $Id: wFlag.c
// Implements flags

#include "wFlag.h"
#include "wError.h"
#include "wValue.h"

#include <string.h>

struct wFlag
{
  char flag_short; // option short (-f)
  char *flag_long; // option name (--flag)
  char *help;      // option description (This flag does this.)
  FlagType type;   // option type (Boolean, String, Number)

  wValue *value;
  wMemPool *_pool;
};

wFlag *
wFlagCreate (wMemPool *opt)
{
  wFlag *self = (wFlag *)wMemAlloc (opt, sizeof (wFlag));
  self->_pool = opt;

  if (!self)
    {
      wErrorDisplay ("wFlagCreate: out of memory");
      return NULL;
    }

  return self;
}

void
wFlagSet (wFlag *self, char opt_short, char *opt_long, char *help,
          FlagType type)
{
  self->flag_short = opt_short;
  self->flag_long = opt_long;
  self->help = help;
  self->type = type;
}

void
wFlagSetType (wFlag *self, FlagType type)
{
  self->type = type;
}

FlagType
wFlagType (wFlag *self)
{
  if (!self || !self->type) {
    return WBoolean;
  }
  return self->type;
}

char
wFlagShort (wFlag *self)
{
  return self->flag_short;
}

char *
wFlagLong (wFlag *self)
{
  return self->flag_long;
}

char *
wFlagHelp (wFlag *self)
{
  return self->help;
}

void
wFlagDefaultValue (wFlag *self, char *value)
{
  if (!self || !value) {
    return;
  }

  if (self->type != WList) { // you can't set a default value for a list, that makes no sense
    self->value = wValueFromString (self->_pool, value);
  }
}

void
wFlagToggle (wFlag *self)
{
  if (!self || !(self->type == WBoolean)) {
    return;
  }

  if (self->value) {
    char* __dec = (strcmp (wValueStr (self->value), "true") == 0) ? "false" : "true";

    self->value = wValueFromString (self->_pool, __dec);
  }
}

wValue *
wFlagValue (wFlag *self)
{
  return self->value;
}

void
wFlagSetValue (wFlag *self, wValue *value)
{
  if (self->type != WList)
    self->value = value;
  else
    {
      if (!self->value) {
        self->value = wValueCreate (self->_pool);
        wValueSetList (self->value);
      }
      
      wValueAppendList (self->value, wValueStr (value));
    }
}
