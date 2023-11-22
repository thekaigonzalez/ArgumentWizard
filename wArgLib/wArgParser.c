// $Id: wArgParser.c
#include "wArgParser.h"
#include "wError.h"

#include <string.h>

struct wArgParser
{
  wOptions *options;
  wArgParserState state;
  int help_needed;
  int error;
};

wArgParser *
wArgParserCreate ()
{
  wOptions *options = wOptionsCreate ();
  wArgParser *self = (wArgParser *)wMemAlloc ((wOptionsGetPool (options)),
                                              sizeof (wArgParser));
  self->options = options;
  self->state = STATE_INIT;
  return self;
}

void
wParseArgs (wArgParser *self, char **argv, int argc)
{
  if (!self)
    {
      wErrorDisplay ("wParseArgs: self is null");
      return;
    }

  if (argc == 1)
    {
      return;
    }

  wFlag *f = NULL;

  for (int i = 1; i < argc; i++)
    {
      wNameType type = wNameTypeFromName (argv[i]);
      char *name = wNameCreateFrom (argv[i]);

      switch (type)
        {
        case WStraggly:
          {
            if (self->state == STATE_INIT)
              {
                wOptionsAddStraggly (self->options, name);
              }
            else if (self->state == STATE_LONG_SHORT_PARAMETER)
              {
                if (f != NULL)
                  {
                    wValue *v = wValueFromString (
                        wOptionsGetPool (self->options), name);
                    wFlagSetValue (f, v);

                    self->state = STATE_INIT;
                  }
              }
          }
          break;
        case WFlagSingular:
          {
            for (int j = 0; j < strlen (name); j++)
              {
                f = wOptionsFindFlag (self->options, name[j]);

                if (!f)
                  {
                    self->error = 1;
                    break;
                  }

                if (self->state == STATE_INIT && wFlagType (f) != WBoolean)
                  {
                    self->state = STATE_LONG_SHORT_PARAMETER;
                  }
                else
                  {
                    if (wFlagType (f) == WBoolean)
                      {
                        wFlagSetValue (
                            f, wValueFromString (
                                   wOptionsGetPool (self->options), "true"));
                      }
                  }
              }
          }
          break;
        case WFlagLong:
          {
            f = wOptionsFindFlagLong (self->options, name);
            if (!f)
              {
                self->error = 1;
                break;
              }

            if (self->state == STATE_INIT && wFlagType (f) != WBoolean)
                  {
                    self->state = STATE_LONG_SHORT_PARAMETER;
                  }
                else
                  {
                    if (wFlagType (f) == WBoolean)
                      {
                        wFlagSetValue (
                            f, wValueFromString (
                                   wOptionsGetPool (self->options), "true"));
                        self->state = STATE_INIT;
                      }
                  }
          }
          break;
        }
    }
}

void
wArgParserAddOptions (wArgParser *self, wOptions *options)
{
  wOptionsAddOptions (self->options, options);
}

void
wArgParserDestroy (wArgParser *self)
{
  wOptionsDestroy (self->options);
}

int
wArgParserStragglyCount (wArgParser *self)
{
  return wOptionsStragglyCount (self->options);
}

wStraggly *
wArgParserStraggly (wArgParser *self, int index)
{
  return wOptionsGetStragglys (self->options);
}

wOptions *
wArgParserOptions (wArgParser *self)
{
  if (self)
    return self->options;
}

wStraggly *
wArgParserStragglies (wArgParser *self)
{
  return wOptionsGetStragglys (self->options);
}

_Bool
wArgParserHelpWanted (wArgParser *self)
{
  return self->help_needed;
}

_Bool
wArgParserError (wArgParser *self)
{
  return self->error;
}
