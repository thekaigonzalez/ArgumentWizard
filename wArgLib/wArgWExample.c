#include "argw.h"
#include <stdlib.h>

main (int argc, char **argv)
{
  argw_init()

  argw_flag('v', "verbose", "Produce verbose output", WBoolean);
  argw_flag('q', "quiet", "Don't produce any output", WBoolean);
  argw_flag('s', "silent", "Don't produce any output", WBoolean);
  argw_flag('o', "output", "Output to FILE instead of standard output", WString);


  argw_parse(argc, argv);

  char* OUTPUT = argw_str('o');
  char* program = argw_positional(0);

  if (argw_bool('v')) {
    printf("verbose\n");
  }

  printf("output: %s\n", OUTPUT);
  printf("program: %s\n", program);

  argw_exit(0)
  return 0;
}
