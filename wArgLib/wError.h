// $Id: wError.h
// Implements error handling

#ifndef AWIZ_WERROR_H
#define AWIZ_WERROR_H

#include <stdlib.h>
#include <stdio.h>

// a definition which frees any objects that are passed, as well as displays a
// fancy error message
#define wErrorDisplay(msg, ...) \
  { \
    printf("\x1b[31merror:\x1b[0m %s\n", msg); \
  }

// a definitition which is basically the same as the first one, i was just too
// lazy to interchange the comments
#define wErrorFreeAndDisplay(msg, obj) \
  { \
    wErrorDisplay(msg); \
    free(obj); \
  }

#endif // AWIZ_WERROR_H
