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
            if (strcmp (name, "h") == 0)
              {
                self->help_needed = 1;
                break;
              }

            if (strcmp (name, "help") == 0)
              {
                printf ("-help is ambiguous, use either -h or --help\n");
              }
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
                    if (*(name + 1) == '\0')
                      self->state = STATE_LONG_SHORT_PARAMETER;
                    else
                      {
                        if (wFlagType (f) != WList)
                          {
                            wFlagSetValue (f,
                                           wValueFromString (
                                               wOptionsGetPool (self->options),
                                               name + 1));
                          }
                        else
                          {
                            wFlagSetValue (f,
                                           wValueFromString (
                                               wOptionsGetPool (self->options),
                                               name + 1));
                          }
                        break;
                      }
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
            if (strcmp (name, "help") == 0)
              {
                self->help_needed = 1;
                break;
              }

            char *value = NULL;
            _Bool found = 0;

            for (int j = 0; j < strlen (name); j++)
              {
                if (name[j] == '=')
                  {
                    name[j] = '\0';
                    value = name + j + 1;
                    found = true;
                    break;
                  }
              }

            printf ("%s\n", name);
            printf ("%s\n", value);

            f = wOptionsFindFlagLong (self->options, name);

            if (!f)
              {
                self->error = 1;
                break;
              }

            if (self->state == STATE_INIT && wFlagType (f) != WBoolean
                && !found)
              {
                self->state = STATE_LONG_SHORT_PARAMETER;
              }
            else
              {
                if (found)
                  {
                    wFlagSetValue (
                        f, wValueFromString (wOptionsGetPool (self->options),
                                             value));
                  }
                else if (wFlagType (f) == WBoolean)
                  {
                    wFlagSetValue (
                        f, wValueFromString (wOptionsGetPool (self->options),
                                             "true"));
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

void
wArgParserPrintHelp (wArgParser *self, char *__progname, char *usage)
{
  wOptionsPrintHelp (self->options, __progname, usage);
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
