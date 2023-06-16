#include <stdio.h> // TODO: remove

void *realloc(void *ptr, size_t size) {
  printf("realloc: %p %zu\n", ptr, size);
  return NULL;
}
