#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argz, char *argv[]) {
  char *lineptr = NULL;
  size_t len = 0;
  size_t nread;

  while (1) {

    printf("Enter programs to run.\n");
    nread = getline(&lineptr, &len, stdin);
    if (nread == -1) {
      perror("getLine failed");
      exit(EXIT_FAILURE);
    }

    char *saveptr;
    char *ret = strtok_r(lineptr, " \n", &saveptr);
    if (ret == NULL) {
      perror("first strtok_r failed");
      exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == 0) {

      execlp(ret, ret, (char *)NULL);

      perror("execlp did not terminate process");
      exit(EXIT_FAILURE);
    } else {
      waitpid(pid, NULL, 0);
    }
  }
  free(lineptr);
}
