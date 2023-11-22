<!-- $Id: README.md $ -->
# ArgWizard (wArgLib)

A simplistic C library for argument parsing using memory pointers.

## Why?

Because I felt like parsing arguments myself for EVERY program was a pain in the
ass. Therefore I decided to try my hand at my own memory safe argument parser.

## How?

This library essentially just wraps around the `char** argv` and `int argc` 
arguments in C, except contains a bit more flexibility as to which arguments are
flags and which are just stragglies, or, arguments without a dash.

## Multi-character singular flags (-abc)

Singular flags can have multiple characters if each option is applicable.

For example, if you have flags `-a` and `-b`, with `-b` being a STRING and `-a`
being a boolean, then you are able to do something like:

```
$ ./program -ab "hello"
```

and both `-a` will be true, and `-b` will be "hello".

## Example

```c
#include "wArgParser.h"

main (int argc, char **argv)
{
  // create an argument parser
  wArgParser *parser = wArgParserCreate ();

  // wOptionsAddFlag will add a flag based on an ArgumentParser's 
  // Options member, therefore you must get it from the struct 
  // itself using wArgParserOptions
  wOptionsAddFlag (wArgParserOptions (parser), 'f', "flag",
                   "This flag does this.", WString);

  // multiple kinds of types are allowed, and in future 
  // releases you will be able to use equations like --flag=1.
  wOptionsAddFlag (wArgParserOptions (parser), 'z', "zip", "This flag zips.",
                   WBoolean);

  // Parse the arguments (memory safe, therefore it's easy to 
  // use this without worrying about memory handling because 
  // everything is handled by the library)
  wParseArgs (parser, argv, argc);

  // If there was an error then simply return -1
  if (wArgParserError (parser))
    {
      return -1;
    }

  // Once parsed, you are able to access the values of each flag, 
  // which are "Variants" meaning that you can use the corresponding 
  // function to get the equivalent C type.
  wValue *v = wFlagValue (wOptionsFindFlag (wArgParserOptions (parser), 'f'));
  wValue *z = wFlagValue (wOptionsFindFlag (wArgParserOptions (parser), 'z'));

  // An example here - you can check if a flag was 
  // added (if it was a WBoolean type)
  if (wValueBoolean (z))
    {
      printf ("-f was added\n");
    }

  // You can also get string values of flags
  if (!wValueStr (v))
    {
      printf ("error: you need a string for (-f)!\n");
      return 1;
    }

  // Print the string values of flags
  printf ("%s\n", wValueStr (v));

  // Straggly - stragglies are essentially the funny looking names for 
  // arguments that don't start with a dash, arguments like "a.out" or 
  // "/usr/bin/", just anything that you see in regular command line apps, 
  // that doesnt have a dash, are stragglies in this argument parser.
  for (int i = 0; i < wArgParserStragglyCount (parser); i++)
    {
      printf ("straggly: %s\n",
              wStragglyAt (wArgParserStragglies (parser), i));
    }

  // Only one free function needs to be called because of the memory pooling system
  wArgParserDestroy (parser);
  return 0;
}
```

```
$ ./program a.out -f gcc gd
gcc
straggly: a.out
straggly: gd

$ ./program a.out -zf
error: you need a string for (-f)!

$ ./program a.out -zf gcc
-z was added
gcc
straggly: a.out
```
