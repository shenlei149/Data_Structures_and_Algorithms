#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "infra_assert.h"
#include "infra_memory.h"
#include "infra_arena.h"

#define THRESHOLD 10

#define T InfraArena_T

struct T
{
    T prev;
    char *avail;
    char *limit;
};

union align
{
    int i;
    long l;
    long *lp;
    void *p;
    void (*fp)(void);
    float f;
    double d;
    long double ld;
};

union header
{
    struct T b;
    union align a;
};

static T freechunks;
static int nfree;

T InfraArena_New(void)
{
    T arena;
    InfraMemory_NEW0(arena);
    return arena;
}

void InfraArena_Dispose(T *ap)
{
    InfraAssert_ASSERT(ap && *ap, __FILE__, __LINE__);
    InfraArena_Free(*ap);
    InfraMemory_FREE(*ap);
}

static T findFitChunk(T chunkPtr, long nbytes)
{
    T result = chunkPtr;
    while (result != NULL && nbytes > result->limit - result->avail)
    {
        result = result->prev;
    }

    return result;
}

void *InfraArena_alloc(T arena, long nbytes, const char *file, int line)
{
    InfraAssert_ASSERT(arena, file, line);
    InfraAssert_ASSERT(nbytes > 0, file, line);

    // round nbytes up to an alignment boundary
    nbytes = ((nbytes + sizeof(union align) - 1) / (sizeof(union align))) * (sizeof(union align));

    T chunkPtr = findFitChunk(arena, nbytes);
    if (chunkPtr == NULL)
    {
        if (nbytes > arena->limit - arena->avail)
        {
            // get a new chunk
            T ptr;
            char *limit;
            if ((ptr = freechunks) != NULL &&
                ptr->limit - ptr->avail >= nbytes)
            {
                freechunks = freechunks->prev;
                nfree--;
                limit = ptr->limit;
            }
            else
            {
                long m = sizeof(union header) + nbytes + 10 * 1024;
                ptr = InfraMemory_ALLOC(m);
                limit = (char *)ptr + m;
            }

            *ptr = *arena;
            arena->avail = (char *)((union header *)ptr + 1);
            arena->limit = limit;
            arena->prev = ptr;
        }

        chunkPtr = arena;
    }

    chunkPtr->avail += nbytes;
    return chunkPtr->avail - nbytes;
}

void *InfraArena_calloc(T arena, long count, long nbytes, const char *file, int line)
{
    InfraAssert_ASSERT(count > 0, file, line);

    void *ptr = InfraArena_alloc(arena, count * nbytes, file, line);
    memset(ptr, '\0', count * nbytes);
    return ptr;
}

static void insertFreeChunk(T chunk)
{
    if (freechunks == NULL)
    {
        freechunks = chunk;
    }
    else
    {
        if (chunk->limit - chunk->avail > freechunks->limit - freechunks->avail)
        {
            chunk->prev = freechunks;
            freechunks = chunk;
        }
        else
        {
            T cur = freechunks;
            T prev = cur->prev;
            while (prev != NULL && chunk->limit - chunk->avail < prev->limit - prev->avail)
            {
                cur = prev;
                prev = prev->prev;
            }

            chunk->prev = prev;
            cur->prev = chunk;
        }
    }
}

void InfraArena_Free(T arena)
{
    InfraAssert_ASSERT(arena, __FILE__, __LINE__);

    while (arena->prev)
    {
        struct T tmp = *arena->prev;
        if (nfree < THRESHOLD)
        {
            T cur = NULL;
            arena->prev->prev = cur;
            cur = arena->prev;
            nfree++;
            cur->avail = (char *)((union header *)cur + 1);
            cur->limit = arena->limit;
            insertFreeChunk(cur);
        }
        else
        {
            InfraMemory_FREE(arena->prev);
        }

        *arena = tmp;
    }

    InfraAssert_ASSERT(arena->prev == NULL, __FILE__, __LINE__);
    InfraAssert_ASSERT(arena->avail == NULL, __FILE__, __LINE__);
    InfraAssert_ASSERT(arena->limit == NULL, __FILE__, __LINE__);
}
