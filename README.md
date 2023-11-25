<!-- $Id: README.md $ -->
# ArgWizard (wArgLib)

A simplistic C library for argument parsing using memory pointers.

## How to use

To use ArgWizard, you can simply copy the wArgLib directory into your program's
`lib` directory, or the source directory. And you are able to include it in your
program. You may have to link against the ArgWizard source files, however.

## Building

You are able to build ArgWizard on any platform with a C compiler, since
ArgWizard uses no non-standard features (except for wCompilerExampleInGetopt),
you are able to build and run this library on any platform such as macOS,
Windows (primarily with Cygwin), and Linux with gcc, clang, or any other C compiler.

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

## Why not `getopt`?

The reason I decided not to use `getopt` is because I just couldn't understand
it. There's really no other reason because it is definitely very powerful and
stable, however, this gave me something to work on as well as a way to implement
better argument parsing into my C programs.

And bonus, ArgWizard is 20-50 milliseconds faster than `getopt`. Try comparing
the compiler example in getopt to the compiler example using ArgWizard, with the
same options passed into it. Now, while getopt uses less memory than ArgWizard,
ArgWizard DOES support more options and is able to be scaled for
smaller-resource environments.

## Dynamic Type System

ArgWizard has a dynamic typing system (not really, but I like to call it that),
because it was designed from the ground up to be very forgiving when it comes to
types of arguments. ArgWizard allows the caller to handle any sort of bad input
for any types of arguments, as it returns an error code when a bad argument is
encountered.

## Default Values

ArgWizard supports default values. If an argument is NOT specified, then there
will be no changes in the flag's value.

With this update also changes the `wOptionsAddFlag` function to return the flag
once it adds it to the parser's options, this greatly improves readability and
decreases overhead, as well as making it more compatible with future versions of
ArgWizard.

```c
wArgParser *parser = wArgParserCreate ();

wFlag *_test = wOptionsAddFlag (wArgParserOptions (parser), 't', "test",
                                  "Test flag with a default value", WString);

wFlagDefaultValue (_test, "test"); // if -t abc is specified, -t will be "abc", if not, it will be "test"
```

## Hexadecimal

ArgWizard allows flags which have hexidecimal values. Arguments such as
`--flag=0x123` will be stored as `0x123` in the flag's value, which will later
be converted to an integer after evaluation.

```c
wFlag *_hexFlag = wOptionsAddFlag (wArgParserOptions (parser), 'z', "hex",
                                  "A hex value", WHex);
...

printf ("hex: %d\n", wValueNumber (V));
```

```
$ ./hex_test --hex=0x41
hex: 65
```

## Flexibility

ArgWizard's simple parsing makes it easy for future contributors *and/or* users
to add their own features, it comes with support for `gcc`-style flags such as
`-Wall` and `-Werror`, supports long flags out of the box, and allows for short
flags on top of that.

```
./program -Wall -I./include
```

## Straggling arguments

Stragglies are arguments that don't start with a dash, arguments like "a.out" or
"/usr/bin/" are "stragglies", which is just a stupid name for anything that you
see in regular command line apps that doesnt have a dash, meaning that they are
most likely supplying a program or a subcommand.

## Key=Value

ArgWizard allows you to specify a flag that is of a string type with a value
attached to it in this format: `--flag=value`, for example:

```
./prog --flag=hello
```

since `flag` is `WString` assumingly, then it's value will be `hello`.

No changes to existing code will be required, since this feature is built into
the default string type out of the box.

## Argument Lists

ArgWizard allows you to specify a flag as a list of different parameters,
essentially, the list class will be an array of strings, unlike other types,
this array has a size and can be changed at runtime as needed when new arguments
are passed.

The simple containerized nature of this type allows it to be very powerful and
memory-efficient, especially when you have a large number of arguments to parse,
not relying on any sort of limit so you can genuinely put as much force into it as
you can.

```c
// $Id: wListTest.c

#include "wArgParser.h"

main (int argc, char **argv)
{
  wArgParser *parser = wArgParserCreate ();

  wOptionsAddFlag (wArgParserOptions (parser), 'a', "arg",
                   "PASS AS MANY ARGUMENTS AS YOU WISH!", WList);


  wParseArgs (parser, argv, argc);

  if (wArgParserError (parser))
    {
      return -1;
    }

  if (wArgParserHelpWanted (parser))
    {
      wArgParserPrintHelp (parser, argv[0], "-[fz]");
      return 0;
    }
    
  wValue *flags = wFlagValue (wOptionsFindFlag (wArgParserOptions (parser), 'a'));

  for (int i = 0; i < wValueListSize (flags); i++) {
    printf ("%s\n", wValueListAt (flags, i));
  }

  wArgParserDestroy (parser);
  return 0;
}
```

```
$ ./list_test -a./ -a../
./
../
```

## Memory Pooling

ArgWizard's memory pooling system is very efficient in keeping a constrained
flow of memory as well as being able to be customized for certain low overhead
environments.

With ArgWizard's simplistic memory usage, you will *never* need to worry about
memory handling using ArgWizard, because where's the fun in managing memory for
a command line library? you don't do that with `getopt`!

The default memory pool increment, being 1024, can take up much memory just off
of simple arguments alone. Changing this value can greatly reduce the overhead
of a command line program, and will have the exact same speed as `getopt`.

Without optimizations (Increment set to 1024)

```
==11980== HEAP SUMMARY:
==11980==     in use at exit: 0 bytes in 0 blocks
==11980==   total heap usage: 14 allocs, 14 frees, 25,920 bytes allocated
```

With optimizations: (Increment set to 50)
```
==11772== HEAP SUMMARY:
==11772==     in use at exit: 0 bytes in 0 blocks
==11772==   total heap usage: 14 allocs, 14 frees, 1,944 bytes allocated
```

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

## Acknowledgements

This library is inspired by the amazing `argparse` library, as well as taking
some design inspiration directly from `getopt` and `getopt_long`.

## License

This library is licensed under the MIT license. See the LICENSE file for more
information.
