# $Id: Makefile
FILES_N_STUFF=wMem.c wOptions.c wStraggly.c wFlag.c wName.c wArgParser.c wValue.c -Wno-implicit-int -g

all:
	gcc wTest.c -o test $(FILES_N_STUFF)
	gcc wParserTest.c -o parser_test $(FILES_N_STUFF)
	gcc wCompilerExample.c -o compiler_example $(FILES_N_STUFF)
