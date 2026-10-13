#define _DEFAULT_SOURCE
#define BUF_SIZE 256
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct header {
  uint64_t size;
  struct header *next;
};

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);

  if (len < 0) {
    write(STDERR_FILENO, "snprintf", strlen("snprintf"));
  }

  write(STDOUT_FILENO, buf, len);
}

int main() {
  void *newHeap = sbrk(256);

  struct header *firstBlock = (struct header *)newHeap;
  struct header *secondBlock = (struct header *)((char *)newHeap + 128);

  firstBlock->size = 128;
  firstBlock->next = NULL;

  secondBlock->size = 128;
  secondBlock->next = firstBlock;

  memset((char *)firstBlock + sizeof(struct header), 0, 128 - sizeof(struct header));
  memset((char *)secondBlock + sizeof(struct header), 1, 128 - sizeof(struct header));

  print_out("first block %p\n", (void *)firstBlock, sizeof((void *)firstBlock));
  print_out("second block %p\n", (void *)secondBlock, sizeof((void *)secondBlock));
  return 0;
}
