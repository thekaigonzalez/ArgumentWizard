// $Id: wDefaultsExample.c

#include "wArgParser.h"

main (int argc, char **argv)
{
  wArgParser *parser = wArgParserCreate ();

  wFlag *_test = wOptionsAddFlag (wArgParserOptions (parser), 't', "test",
                                  "Test flag with a default value", WString);

  wFlagDefaultValue (_test, "test");

  wParseArgs (parser, argv, argc);

  if (wArgParserError (parser))
    {
      return -1;
    }

  if (wArgParserHelpWanted (parser))
    {
      wArgParserPrintHelp (parser, argv[0], "-[t]");
      return 0;
    }
  wValue *V = wFlagValue (_test);
  printf ("test: %s\n", wValueStr (V));

  for (int i = 0; i < wArgParserStragglyCount (parser); i++)
    {
      printf ("extra: %s\n", wStragglyAt (wArgParserStragglies (parser), i));
    }

  wArgParserDestroy (parser);
  return 0;
}
