#ifndef INFRA_ARENA_INCLUDED
#define INFRA_ARENA_INCLUDED

#define T InfraArena_T
typedef struct T *T;

#define InfraArena_ALLOC(arena, nbytes) InfraArena_alloc((arena), (nbytes), __FILE__, __LINE__)
#define InfraArena_CALLOC(arena, count, nbytes) InfraArena_calloc((arena), (count), (nbytes), __FILE__, __LINE__)

extern T InfraArena_New(void);
extern void InfraArena_Dispose(T *ap);

extern void *InfraArena_alloc(T arena, long nbytes, const char *file, int line);
extern void *InfraArena_calloc(T arena, long count, long nbytes, const char *file, int line);
extern void InfraArena_Free(T arena);

#undef T
#endif
