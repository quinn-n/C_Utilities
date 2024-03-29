/*
Removes whitespace after files.
Written by Quinn Neufeld
Sept. 29 2021 - Removed progutil dependency
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define HELP_MSG "Usage: remove-whitespace <file>\nRemoves extra whitespace after a text file.\n"
#define BUFF_SIZE 4096

char* readFile(FILE* fi) {
  char* outstr = NULL;
  char* buff = (char*) malloc(sizeof(char) * BUFF_SIZE);
  size_t bufflen;
  size_t outlen = 0;
  //Load file, up to buffer size, and add to outstr. Repeat while necessary.
  while(!feof(fi)) {
    fscanf(fi, "%c4096", buff);
    bufflen = strlen(buff);
    outlen += bufflen;
    outstr = realloc(outstr, outlen);
    strcat(outstr, buff);
  }
  free(buff);
  return outstr;
}

char* removeEndWhitespaces(char* str) {
  size_t lastpos = strlen(str) - 1;
  char lastchar = str[lastpos];
  while(isspace(lastchar)) {
    lastpos--;
    lastchar = str[lastpos];
  }
  size_t size = lastpos + 1;
  char* newStr = (char*) malloc(sizeof(char) * size);
  memcpy(newStr, str, sizeof(char) * size);
  return newStr;
}

int main(int argc, char** argv) {
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
  char* fpath = argv[1];
  FILE* fi = fopen(fpath, "r");
  char* filestr = readFile(fi);
  fclose(fi);
  char* formattedStr = removeEndWhitespaces(filestr);
  free(filestr);
  fi = fopen(fpath, "w");
  size_t filesize = strlen(formattedStr);
  for(size_t i = 0; i < filesize; i++) {
    fprintf(fi, "%c", formattedStr[i]);
  }
  fclose(fi);
}
