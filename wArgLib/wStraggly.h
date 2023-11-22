// $Id: wStraggly.h
// Defines a list of Straggly arguments
// These are arguments without a `-' prefix

#ifndef AWIZ_WSTRAGGLY_H
#define AWIZ_WSTRAGGLY_H

#include <stdlib.h>

#include "wMem.h"

// contains arguments that do not start with a `-`
struct wStraggly;
typedef struct wStraggly wStraggly;

wStraggly *wStragglyCreate (wMemPool *options);
int wStragglySize (wStraggly *self);
char **wStragglies (wStraggly *self);
char* wStragglyAt (wStraggly *self, int index);
void wStragglyAppend (wMemPool * p, wStraggly *self, char *str);

#endif // AWIZ_WSTRAGGLY_H
