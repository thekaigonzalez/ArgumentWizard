// $Id: wFlag.h
// Implements flags

#ifndef AWIZ_WFLAG_H
#define AWIZ_WFLAG_H

#include "wMem.h"
#include "wValue.h"

struct wFlag;
typedef struct wFlag wFlag;

typedef enum _FlagType {
  WBoolean,
  WString,
  WNumber,
  WList,
  WHex,
} FlagType;

wFlag* wFlagCreate(wMemPool *opt);
void wFlagSet(wFlag* self, char opt_short, char* opt_long, char* help, FlagType type);
void wFlagSetType(wFlag* self, FlagType type);

FlagType wFlagType(wFlag* self);
char wFlagShort(wFlag* self);
char* wFlagLong(wFlag* self);
char* wFlagHelp(wFlag* self);

void wFlagDefaultValue(wFlag* self, char* value);
void wFlagToggle(wFlag* self);

wValue * wFlagValue(wFlag * self);
void wFlagSetValue(wFlag* self, wValue* value);


#endif // AWIZ_WFLAG_H
