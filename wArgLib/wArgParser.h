// $Id: wArgParser.h
// Implements argument parsing

#ifndef AWIZ_WARGPARSER_H
#define AWIZ_WARGPARSER_H

#include <stdlib.h>
#include <stdio.h>

#include "wMem.h"
#include "wStraggly.h"
#include "wOptions.h"
#include "wName.h"

struct wArgParser;
typedef struct wArgParser wArgParser;

typedef enum {
  STATE_INIT, // none yet
  STATE_LONG_SHORT_PARAMETER, // -f { ... } | --long { ... }
} wArgParserState;

wArgParser *wArgParserCreate ();
void wParseArgs(wArgParser *self, char** argv, int argc);
void wArgParserAddOptions(wArgParser *self, wOptions *options);
void wArgParserDestroy (wArgParser *self);
int wArgParserStragglyCount(wArgParser *self);
void wArgParserPrintHelp(wArgParser *self, char* __progname, char* usage);
wStraggly *wArgParserStraggly(wArgParser *self, int index);
wOptions* wArgParserOptions(wArgParser *self);
wStraggly *wArgParserStragglies(wArgParser *self);
_Bool wArgParserError(wArgParser *self);
_Bool wArgParserHelpWanted(wArgParser *self);

#endif // AWIZ_WARGPARSER_H
