/*
Converts a given character to it's unicode value.
If a multi-character string is provided, outputs each value individually.
Written by Quinn Neufeld
Feb. 21 2019
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HELP_MSG "Usage: convert-char <char(s)> converts character(s) to a unicode number, then outputs the result.\n"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf(HELP_MSG);
    return 1;
  }
  for (int i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
      printf(HELP_MSG);
      return 1;
    }
  }
  size_t numChars = strlen(argv[1]);
  char* chars = argv[1];
  for(size_t i = 0; i < numChars; i++) {
    printf("%i\n", (int) chars[i]);
  }
}
