// $Id: wArgPInArgWExample.c
#include "argw.h"
#include <stdlib.h>

main (int argc, char **argv)
{
  argw_init ();

  argw_flag ('v', "verbose", "Produce verbose output", WBoolean);
  argw_flag ('q', "quiet", "Don't produce any output", WBoolean);
  argw_flag ('s', "silent", "Alias for -q", WBoolean);
  argw_flag ('o', "output", "Output to FILE instead of standard output",
             WString);

  argw_parse (argc, argv);

  char *OUTPUT = argw_str ('o');
  char *_ARG1 = argw_positional (0);
  char *_ARG2 = argw_positional (1);

  printf (
      "ARG1 = %s\nARG2 = %s\nOUTPUT_FILE = %s\nVERBOSE = %s\nSILENT = %s\n",
      _ARG1, _ARG2, OUTPUT, argw_bool ('v') ? "yes" : "no",
      argw_bool ('s') ? "yes" : "no");

  argw_exit (0)
}
