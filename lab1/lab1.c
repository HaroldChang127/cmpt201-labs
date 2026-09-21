#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char *lineptr = NULL;
  size_t len = 0;
  size_t nread;

  while (1) {

    printf("Please enter some text: ");
    nread = getline(&lineptr, &len, stdin);
    if (nread == -1) {
      perror("getline failed");
      exit(EXIT_FAILURE);
    }

    printf("Tokens:\n");
    char *saveptr;
    char *ret = strtok_r(lineptr, " ", &saveptr);
    if (ret == NULL) {
      perror("first strtok_r failed");
      exit(EXIT_FAILURE);
    }
    while (ret != NULL) {
      printf("%s\n", ret);
      ret = strtok_r(NULL, " ", &saveptr);
    }
  }
  free(lineptr);
}
