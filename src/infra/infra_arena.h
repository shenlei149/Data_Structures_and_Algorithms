#ifndef INFRA_ARENA_INCLUDED
#define INFRA_ARENA_INCLUDED

#define T Arena_T
typedef struct T *T;

#define Arena_ALLOC(arena, nbytes) Arena_alloc((arena), (nbytes), __FILE__, __LINE__)
#define Arena_CALLOC(arena, count, nbytes) Arena_calloc((arena), (count), (nbytes), __FILE__, __LINE__)

extern T Arena_New(void);
extern void Arena_Dispose(T *ap);

extern void *Arena_alloc(T arena, long nbytes, const char *file, int line);
extern void *Arena_calloc(T arena, long count, long nbytes, const char *file, int line);
extern void Arena_Free(T arena);

#undef T
#endif
