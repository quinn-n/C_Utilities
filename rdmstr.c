/*
 * rdmstr.c
 * Prints a random string of ascii characters
 * Written by Quinn Neufeld
 * May 30th 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <math.h>
#include <string.h>

void print_help();

int main(int argc, char** argv) {
    if (argc < 2 || !strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
        print_help();
        return 1;
    }
    srand(time(NULL));
    for (long i = atol(argv[1]); i > 0; i--) {
        printf("%c", rand() % (127 - 32) + 32);
    }
    printf("\n");
}

/*
 * Prints out help message
 */
void print_help() {
    printf("Usage: rdmstr <n>\n");
    printf("-h / --help - prints this message and exits.\n");
    printf("Prints out a given number of randomly selected characters.\n");
}
