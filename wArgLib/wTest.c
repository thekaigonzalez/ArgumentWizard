// $Id: wTest.c
// tests

#include "wError.h"
#include "wMem.h"
#include "wOptions.h"
#include "wStraggly.h"
#include "wFlag.h"
#include "wArgParser.h"


#define pass() printf("test %s passed\n", __func__)
#define fail() printf("test %s failed\n", __func__)

test_memory_pool(void) {
  wMemPool * pool = wMemPoolCreate();

  char* str = (char*)wMemAlloc(pool, 11);
  str [0] = 'a';
  str [1] = 'b';
  str [2] = 'c';
  str [3] = 'd';
  str [4] = 'e';
  str [5] = 'f';
  str [6] = 'g';
  str [7] = 'h';
  str [8] = 'i';
  str [9] = 'j';
  str [10] = '\0';
  printf("%s\n", str);
  char* str2 = (char*)wMemAlloc(pool, 11);
  str2 [0] = 'a';
  str2 [1] = 'b';
  str2 [2] = 'c';
  str2 [3] = 'd';
  str2 [4] = 'e';
  str2 [5] = 'f';
  str2 [6] = 'g';
  str2 [7] = 'h';
  str2 [8] = 'i';
  str2 [9] = 'j';
  str2 [10] = '\0';
  printf("%s\n", str);

  wMemPoolDestroy(pool);

  pass();
}

test_options(void) {
  wOptions *options = wOptionsCreate();
  wStraggly *straggly = wStragglyCreate(wOptionsGetPool (options));

  wStragglyAppend(wOptionsGetPool(options), straggly, "a.out");

  for (int i = 0; i < wStragglySize(straggly); i++) {
    printf("%s\n", wStragglies(straggly)[i]);
  }

  wOptionsDestroy(options);
  pass();
}

test_flag(void) {
  wMemPool *p = wMemPoolCreate();

  wFlag *flag = wFlagCreate(p);
  wFlagSet(flag, 'f', "flag", "This flag does this.", WBoolean);

  wFlag *flag2 = wFlagCreate(p);
  wFlagSet(flag2, 'b', "flag2", "This flag also does this.", WBoolean);

  printf("flag info: -%c --%s\n", wFlagShort(flag), wFlagLong(flag));
  printf("\t%s\n", wFlagHelp(flag));
  printf("flag2 info: -%c --%s\n", wFlagShort(flag2), wFlagLong(flag2));
  printf("\t%s\n", wFlagHelp(flag2));


  wMemPoolDestroy(p);
  pass();
}

test_options_and_their_flags(void) {
  wOptions *options = wOptionsCreate();

  wOptionsAddFlag(options, 'f', "flag", "This flag does this.", WBoolean);
  wOptionsAddFlag(options, 'b', "flag2", "This flag also does this.", WBoolean);

  for (int i = 0; i < wOptionsFlagsCount(options); i++) {
    wFlag *flag = wOptionsGetFlag(options, i);
    printf("flag info: -%c --%s\n", wFlagShort(flag), wFlagLong(flag));
    printf("\t%s\n", wFlagHelp(flag));
  }


  wOptionsDestroy(options);
  pass();
}

test_arg_parser(void) {
  wArgParser *parser = wArgParserCreate();

  wOptions *options = wArgParserOptions(parser);

  wOptionsAddFlag(options, 'f', "flag", "This flag does this.", WBoolean);
  wOptionsAddFlag(options, 'b', "flag2", "This flag also does this.", WBoolean);

  _Bool bf = wValueBoolean(wFlagValue(wOptionsFindFlag(options, 'f')));

  printf("flag is switched: %d\n", bf);

  wArgParserDestroy(parser);

  pass();
}

main(void) {
  test_memory_pool();
  test_options();
  test_flag();
  test_options_and_their_flags();
  test_arg_parser();
}
