#include "wArgParser.h"

main (int argc, char **argv)
{
  wArgParser *parser = wArgParserCreate ();

  wOptionsAddFlag (wArgParserOptions (parser), 'f', "flag",
                   "Example flag 1 -> Requires a string to be passed", WString);
  wOptionsAddFlag (wArgParserOptions (parser), 'z', "zip", "A boolean flag to check zipping.",
                   WBoolean);

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
    
  wValue *v = wFlagValue (wOptionsFindFlag (wArgParserOptions (parser), 'f'));
  wValue *z = wFlagValue (wOptionsFindFlag (wArgParserOptions (parser), 'z'));

  if (wValueBoolean (z))
    {
      printf ("-z was added\n");
    }

  if (!wValueStr (v))
    {
      printf ("error: you need a string for (-f)!\n");
      return 1;
    }
  printf ("%s\n", wValueStr (v));
  for (int i = 0; i < wArgParserStragglyCount (parser); i++)
    {
      printf ("straggly: %s\n",
              wStragglyAt (wArgParserStragglies (parser), i));
    }

  wArgParserDestroy (parser);
  return 0;
}
