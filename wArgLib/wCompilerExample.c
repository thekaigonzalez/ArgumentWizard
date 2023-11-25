// $Id: wCompilerExample.c

#include "wArgParser.h"

main (int argc, char **argv)
{
  wArgParser *parser = wArgParserCreate ();

  wOptionsAddFlag (wArgParserOptions (parser), 'o', "out",
                   "The output file", WString);

  wOptionsAddFlag (wArgParserOptions (parser), 'I', "include", "The directory to include.",
                   WString);
  wOptionsAddFlag (wArgParserOptions (parser), 'g', "debug", "Enable debug information.",
                   WBoolean);
  wOptionsAddFlag (wArgParserOptions (parser), 'W', "warnings", "Enable all warnings.",
                   WString);
  wOptionsAddFlag (wArgParserOptions (parser), 'O', "optimize", "Enable optimization.",
                   WBoolean);



  wParseArgs (parser, argv, argc);

  if (wArgParserError (parser))
    {
      return -1;
    }

  if (wArgParserHelpWanted (parser))
    {
      wArgParserPrintHelp (parser, argv[0], "-[oIgWO]");
      return 0;
    }
    
  wValue *_output_file = wFlagValue (wOptionsFindFlag (wArgParserOptions (parser), 'o'));
  wValue *_include = wFlagValue (wOptionsFindFlag (wArgParserOptions (parser), 'I'));
  wValue *_debug = wFlagValue (wOptionsFindFlag (wArgParserOptions (parser), 'g'));
  wValue *_warnings = wFlagValue (wOptionsFindFlag (wArgParserOptions (parser), 'W'));
  wValue *_optimize = wFlagValue (wOptionsFindFlag (wArgParserOptions (parser), 'O'));

  char* output_dir = (wValueStr (_output_file) != NULL) ? wValueStr (_output_file) : "(none specified)";

  printf("information:\n");
  printf("optimizations? %d\n", wValueBoolean (_optimize));
  printf("debug? %d\n", wValueBoolean (_debug));
  printf("warnings? %s\n", wValueStr (_warnings));
  printf("output file: %s\n", output_dir);
  printf("include dir: %s\n", wValueStr (_include));

  for (int i = 0; i < wArgParserStragglyCount (parser); i++)
    {
      printf ("file: %s\n",
              wStragglyAt (wArgParserStragglies (parser), i));
    }

  wArgParserDestroy (parser);
  return 0;
}
