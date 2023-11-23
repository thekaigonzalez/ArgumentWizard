// $Id: wOptions.h
// defines options shared across wArgLib

#ifndef AWIZ_WOPTIONS_H
#define AWIZ_WOPTIONS_H

#include "wFlag.h"
#include "wStraggly.h"
#include "wMem.h"

struct wOptions;
typedef struct wOptions wOptions;

// Creates an Options struct, which has a global memory pool as well as other
// things i forgot about lol
wOptions *wOptionsCreate ();
wMemPool *wOptionsGetPool (wOptions *self);
void wOptionsAddFlag (wOptions *self, char opt_short, char *opt_long,
                      char *help, FlagType type);
void wOptionsDestroy (wOptions *self);
wFlag** wOptionsFlags (wOptions *self);
int wOptionsFlagsCount (wOptions *self);
void wOptionsAddOptions(wOptions *src, wOptions *dest);
int wOptionsStragglyCount(wOptions *self);
char* wOptionsGetStraggly (wOptions *self, int index);
wStraggly *wOptionsGetStragglys (wOptions *self);

void wOptionsPrintHelp(wOptions *self, char* __progname, char* usage);

void wOptionsAddStraggly(wOptions *self, char* src);

wFlag *wOptionsGetFlag (wOptions *self, int index);
wFlag *wOptionsFindFlag (wOptions *self, char opt_short);
wFlag* wOptionsFindFlagBoth (wOptions *self, char opt_short, char* opt_long); // just in case we need both or neither
wFlag *wOptionsFindFlagLong (wOptions *self, char *opt_long);
#endif // AWIZ_WOPTIONS_H
