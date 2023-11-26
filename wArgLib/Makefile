# $Id: Makefile
FILES_N_STUFF=wMem.c wOptions.c wStraggly.c wFlag.c wName.c wArgParser.c wValue.c -Wno-implicit-int -g

all:
	gcc wTest.c -o test $(FILES_N_STUFF)
	gcc wParserTest.c -o parser_test $(FILES_N_STUFF)
	gcc wCompilerExample.c -o compiler_example $(FILES_N_STUFF)
	gcc wListTest.c -o list_test $(FILES_N_STUFF)
	gcc wDefaultsExample.c -o defaults_example $(FILES_N_STUFF)
	gcc wHexTest.c -o hex_test $(FILES_N_STUFF)
	gcc wArgPWizExample.c -o argp_univ $(FILES_N_STUFF)
	gcc wArgPGNUExample3.c -o argp_unix $(FILES_N_STUFF)
	gcc wArgWExample.c -o argw_example $(FILES_N_STUFF)
	gcc wArgPInArgWExample.c -o argp_in_argw_example $(FILES_N_STUFF)

lib:
	gcc $(FILES_N_STUFF) -shared -o libwArgLib.so
	mv libwArgLib.so /usr/local/lib/
	mkdir -p /usr/include/argw
	cp $(wildcard *.h) /usr/include/argw
