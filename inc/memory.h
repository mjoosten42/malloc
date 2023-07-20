#include <stdalign.h> // alignof
#include <stddef.h>	  // size_t, max_align_t
#include <unistd.h>	  // getpagesize

#define ALIGNMENT alignof(max_align_t)

/* Aligment
 * The pointers return by *alloc must be aligned to fit any type.
 * This is achieved by aligning all pointers to the max alignment (alignment of
 * max_align_t, thanks C11). All returned pointers are aligned by aligning all
 * data chunks, meaning zone_t's, chunk_t's and returned memory. Hence the
 * align(x, ALIGNMENT) in *alloc(). Zones and chunks are aligned by including
 * max_align_t as a FAM in chunk_t, and including chunk_t as FAM in zone_t.
 */

void *allocate(size_t size);
void  deallocate(void *ptr, size_t size);

size_t align(size_t size, int alignment);
