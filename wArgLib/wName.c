#include "wName.h"

#include <stddef.h>

wNameType
wNameTypeFromName (char *name)
{
  if (name[0] == '-')
    {
      if (name[1] == '-')
        {
          return WFlagLong;
        }
      return WFlagSingular;
    }
  return WStraggly;
}

char *
wNameCreateFrom (char *name)
{
  wNameType t = wNameTypeFromName (name);

  switch (t) {
    case WStraggly:
      return name;
    case WFlagSingular:
      return name + 1;
    case WFlagLong:
      return name + 2;
  }

  return NULL;
}
