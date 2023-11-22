// $Id: wName.h
// Contains functions for handling argument names

#ifndef AWIZ_WNAME_H
#define AWIZ_WNAME_H

typedef enum _wNameType {
  WStraggly, // example: a.out, file.name
  WFlagSingular, // example: -f, -a
  WFlagLong, // example: --flag, --output
} wNameType;

// Returns the type of the name
wNameType wNameTypeFromName (char *name);
char* wNameCreateFrom(char* name);

#endif // AWIZ_WNAME_H
