#include <stdlib.h>

#include "infra_memory.h"
#include "infra_assert.h"

void *Memory_alloc(long nbytes, const char *file, int line)
{
    Assert_ASSERT(nbytes > 0, file, line);
    void *ptr = malloc(nbytes);
    Assert_ASSERT(ptr, file, line);
    return ptr;
}

void *Memory_calloc(long count, long nbytes, const char *file, int line)
{
    Assert_ASSERT(count > 0, file, line);
    Assert_ASSERT(nbytes > 0, file, line);
    void *ptr = calloc(count, nbytes);
    Assert_ASSERT(ptr, file, line);
    return ptr;
}

extern void *Memory_resize(void *ptr, long nbytes, const char *file, int line)
{
    Assert_ASSERT(ptr, file, line);
    Assert_ASSERT(nbytes > 0, file, line);
    ptr = realloc(ptr, nbytes);
    Assert_ASSERT(ptr, file, line);
    return ptr;
}

extern void Memory_free(void *ptr)
{
    if (ptr)
    {
        free(ptr);
    }
}
