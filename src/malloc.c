#include "malloc.h"

void *malloc(size_t size) {
  (void)size;
  return (void *)0x42;
}
