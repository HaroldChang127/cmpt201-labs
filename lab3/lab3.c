#define _GNU_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  char *lineptr = NULL;
  char *storedInput[5] = {NULL};
  size_t len = 0;
  size_t i = 0;
  size_t nread;

  while (1) {

    if (i == 5) {
      i = 0;
    }

    printf("Enter input: ");
    nread = getline(&lineptr, &len, stdin);
    if (nread == -1) {
      perror("getline failed");
      exit(EXIT_FAILURE);
    }

    storedInput[i] = strdup(lineptr);

    i++;

    if (strcmp(lineptr, "print\n") == 0) {
      for (size_t j = 0; j < i; j++) {
        printf("%s", storedInput[j]);
      }
      i = 0;
    }
  }

  for (size_t j = 0; j < 5; j++) {
    free(storedInput[j]);
  }
  free(lineptr);
  return 0;
}
