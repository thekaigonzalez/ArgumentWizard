// $Id: getoptExample.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char *optarg;
extern int optind, opterr, optopt;

int main(int argc, char **argv) {
    char *output_file = NULL;
    char *include_dir = NULL;
    int debug = 0;
    char *warnings = NULL;
    int optimize = 0;

    int opt;
    while ((opt = getopt(argc, argv, "o:I:gW:O")) != -1) {
        switch (opt) {
            case 'o':
                output_file = optarg;
                break;
            case 'I':
                include_dir = optarg;
                break;
            case 'g':
                debug = 1;
                break;
            case 'W':
                warnings = optarg;
                break;
            case 'O':
                optimize = 1;
                break;
            case '?':
                // Handle unknown options or missing arguments
                return -1;
        }
    }

    printf("information:\n");
    printf("optimizations? %d\n", optimize);
    printf("debug? %d\n", debug);
    printf("warnings? %s\n", warnings != NULL ? warnings : "(none specified)");
    printf("output file: %s\n", output_file != NULL ? output_file : "(none specified)");
    printf("include dir: %s\n", include_dir != NULL ? include_dir : "(none specified)");

    // Process non-option arguments (straggly arguments)
    for (int i = optind; i < argc; i++) {
        printf("file: %s\n", argv[i]);
    }

    return 0;
}
