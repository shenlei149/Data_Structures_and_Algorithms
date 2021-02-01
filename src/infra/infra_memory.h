#ifndef INFRA_MEMORY_INCLUDED
#define INFRA_MEMORY_INCLUDED

#include <stdlib.h>

#define Memory_ALLOC(nbytes) Memory_alloc((nbytes), __FILE__, __LINE__)
#define Memory_CALLOC(count, nbytes) Memory_calloc((count), (nbytes), __FILE__, __LINE__)
#define Memory_RESIZE(ptr, nbytes) ((ptr) = Memory_resize((ptr), (nbytes), __FILE__, __LINE__))
#define Memory_FREE(ptr) ((void)(Memory_free((ptr)), (ptr) = NULL))

// allocates an uninitialized block to hold *p and sets p to theaddress of that block.
#define Memory_NEW(p) ((p) = Memory_ALLOC((long)sizeof *(p)))

// same as NEW(p), but also clears the block.
#define Memory_NEW0(p) ((p) = Memory_CALLOC(1, (long)sizeof *(p)))

extern void *Memory_alloc(long nbytes, const char *file, int line);
extern void *Memory_calloc(long count, long nbytes, const char *file, int line);
extern void *Memory_resize(void *ptr, long nbytes, const char *file, int line);
extern void Memory_free(void *ptr);

#endif
