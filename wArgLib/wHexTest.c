// $Id: wHexTest.c

#include "wArgParser.h"

main (int argc, char **argv)
{
  wArgParser *parser = wArgParserCreate ();

  wFlag *_hexFlag = wOptionsAddFlag (wArgParserOptions (parser), 'z', "hex",
                                  "A hex value", WHex);

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

  wValue *V = wFlagValue (_hexFlag);

  printf ("hex: %d\n", wValueNumber (V));

  wArgParserDestroy (parser);

  return 0;
}
