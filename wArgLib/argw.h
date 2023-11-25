// $Id: argw.h

#ifndef _ARGW_H
#define _ARGW_H

// GNU-style interface for Argument Wizard

#include "wArgParser.h"

#define argw_init() wArgParser *parser = wArgParserCreate ();
#define argw_flag(short, long, help, type)                                    \
  wOptionsAddFlag (wArgParserOptions (parser), short, long, help, type)
#define argw_parse(argc, argv) wParseArgs (parser, argv, argc)

#define argw_str(flag)                                                        \
  wValueStr (wFlagValue (wOptionsFindFlag (wArgParserOptions (parser), flag)))
#define argw_bool(flag)                                                       \
  wValueBoolean (                                                             \
      wFlagValue (wOptionsFindFlag (wArgParserOptions (parser), flag)))
#define argw_num(flag)                                                        \
  wValueNumber (                                                              \
      wFlagValue (wOptionsFindFlag (wArgParserOptions (parser), flag)))
#define argw_list(flag)                                                       \
  wValueList (wFlagValue (wOptionsFindFlag (wArgParserOptions (parser), flag)))

#define argw_default(flag, value)                                             \
  wFlagDefaultValue (wOptionsFindFlag (wArgParserOptions (parser), flag),     \
                     value)

#define argw_usage(usage) wArgParserPrintHelp (parser, argv[0], usage)

#define argw_positional(pos) (pos >= wArgParserStragglyCount (parser)) ? NULL \
  : wOptionsGetStraggly (wArgParserOptions (parser), pos)

#define argw_exit(code)                                                       \
  wArgParserDestroy (parser);                                                 \
  exit (code);

#endif
