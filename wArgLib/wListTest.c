// $Id: wListTest.c

#include "wArgParser.h"

main (int argc, char **argv)
{
  wArgParser *parser = wArgParserCreate ();

  wOptionsAddFlag (wArgParserOptions (parser), 'a', "arg",
                   "PASS AS MANY ARGUMENTS AS YOU WISH!", WList);


  wParseArgs (parser, argv, argc);

  if (wArgParserError (parser))
    {
      return -1;
    }

  if (wArgParserHelpWanted (parser))
    {
      wArgParserPrintHelp (parser, argv[0], "-[fz]");
      return 0;
    }
    
  wValue *flags = wFlagValue (wOptionsFindFlag (wArgParserOptions (parser), 'a'));

  for (int i = 0; i < wValueListSize (flags); i++) {
    printf ("%s\n", wValueListAt (flags, i));
  }

  for (int i = 0; i < wArgParserStragglyCount (parser); i++)
    {
      printf ("straggly: %s\n",
              wStragglyAt (wArgParserStragglies (parser), i));
    }

  wArgParserDestroy (parser);
  return 0;
}
