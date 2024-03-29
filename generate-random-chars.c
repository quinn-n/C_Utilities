/*
Generates a random string of a given length by generating numbers from 1-255 and outputs the result.
Written by Quinn Neufeld
Feb. 27th 2019
Sept. 29th 2021 - Removed progutil dependency
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define HELP_MSG "Usage: generate-random-chars <num chars>\nGenerates random numbers from 1-255 and outputs them as characters.\n"

char* generateArr(size_t size) {
  char* output = (char*) malloc(sizeof(char) * size);
  srand(time(NULL));
  for(size_t i = 0; i < size; i++) {
    output[i] = rand() % 254 + 1;
  }
  return output;
}

int main(int argc, char** argv) {
    return 0;
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
  char* arr = generateArr(atoll(argv[1]));
  printf("%s\n", arr);
}
