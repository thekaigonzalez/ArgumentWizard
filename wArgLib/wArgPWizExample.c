// $Id: wArgPWizExample.c

#include "wArgParser.h"
#include <stdlib.h>

const char *argp_program_version = "argw-ex1 1.0";
const char *argp_program_bug_address = "<bug-argw-example@argw.org>";

/* Program documentation. */
static char doc[] = "Argw example #1 -- a program with options";

main (int argc, char **argv)
{
  wArgParser *parser = wArgParserCreate ();

  wFlag *verbose = wOptionsAddFlag (wArgParserOptions (parser), 'v', "verbose",
                                    "Produce verbose output", WBoolean);

  wFlag *quiet = wOptionsAddFlag (wArgParserOptions (parser), 'q', "quiet",
                                  "Don't produce any output", WBoolean);

  wFlag *silent = wOptionsAddFlag (wArgParserOptions (parser), 's', "silent",
                                   "Alias for -q", WBoolean);

  wFlag *output
      = wOptionsAddFlag (wArgParserOptions (parser), 'o', "output",
                         "Output to FILE instead of standard output", WString);

  wFlagDefaultValue (verbose, "false");
  wFlagDefaultValue (quiet, "false");
  wFlagDefaultValue (silent, "false");
  // wFlagDefaultValue (output, "-");

  wParseArgs (parser, argv, argc);

  if (wArgParserError (parser))
    {
      return -1;
    }

  if (wArgParserHelpWanted (parser))
    {
      wArgParserPrintHelp (parser, argv[0], "-[vqs]");
      return 0;
    }

  wValue *v = wFlagValue (verbose);
  wValue *q = wFlagValue (quiet);
  wValue *s = wFlagValue (silent);
  wValue *o = wFlagValue (output);

  char *_ARG1 = NULL;
  char *_ARG2 = NULL;

  for (int i = 0; i < wArgParserStragglyCount (parser); i++)
    {
      if (_ARG1 == NULL)
        {
          _ARG1 = wStragglyAt (wArgParserStragglies (parser), i);
        }
      else if (_ARG2 == NULL)
        {
          _ARG2 = wStragglyAt (wArgParserStragglies (parser), i);
        }

      if (i > 2)
        {
          break;
        }
    }

  printf (
      "ARG1 = %s\nARG2 = %s\nOUTPUT_FILE = %s\nVERBOSE = %s\nSILENT = %s\n",
      _ARG1, _ARG2, wValueStr (o), wValueBoolean (v) ? "yes" : "no",
      wValueBoolean (s) ? "yes" : "no");

  wArgParserDestroy (parser);
}
