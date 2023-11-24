// $Id: wValue.h
// Implements values

#ifndef AWIZ_WVALUE_H
#define AWIZ_WVALUE_H

#include "wMem.h"

#include <stdbool.h>

struct wValue;
typedef struct wValue wValue;

wValue* wValueCreate (wMemPool *opt);
void wValueSetStr (wValue* self, char* str);
void wValueSetNumber (wValue* self, int number);
void wValueSetBoolean (wValue* self, _Bool boolean);
void wValueSetList (wValue* self);
void wValueAppendList (wValue* self, char* str);
char** wValueList (wValue* self);
int wValueListSize (wValue* self);
char* wValueListAt (wValue* self, int index);
char* wValueStr (wValue* self);
int wValueNumber (wValue* self);
_Bool wValueBoolean (wValue* self);

wValue *wValueFromString (wMemPool * opt, char* str);

typedef enum {
  WTYPE_STRING,
  WTYPE_NUMBER,
  WTYPE_BOOLEAN,
  WTYPE_LIST
} wType;

#endif // AWIZ_WVALUE_H
