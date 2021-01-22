#include <criterion/criterion.h>

#include "../../src/infra/infra_arena.h"

TestSuite(infra_arena);

Test(infra_arena, find_fit_chunk_base)
{
    InfraArena_T arena = InfraArena_New();
    InfraArena_ALLOC(arena, 6 * 1024);
    void *second = InfraArena_ALLOC(arena, 12 * 1024);
    void *second2 = InfraArena_ALLOC(arena, 6 * 1024);

    ptrdiff_t diff = (char *)second2 - (char *)second;
    cr_assert_eq(labs(diff), 12 * 1024);
}

Test(infra_arena, find_fit_chunk_advance)
{
    InfraArena_T arena = InfraArena_New();
    void *first = InfraArena_ALLOC(arena, 6 * 1024);
    InfraArena_ALLOC(arena, 12 * 1024);
    void *second = InfraArena_ALLOC(arena, 6 * 1024);
    void *first2 = InfraArena_ALLOC(arena, 6 * 1024);

    ptrdiff_t diff = (char *)first2 - (char *)first;
    cr_assert_eq(labs(diff), 6 * 1024);

    InfraArena_ALLOC(arena, 6 * 1024);
    InfraArena_ALLOC(arena, 8 * 1024);
    void *second2 = InfraArena_ALLOC(arena, 4 * 1024);

    diff = (char *)second2 - (char *)second;
    cr_assert_eq(labs(diff), 6 * 1024);
}

Test(infra_arena, use_freechunk_base)
{
    InfraArena_T arena = InfraArena_New();
    InfraArena_ALLOC(arena, 70 * 1024);
    void *free5 = InfraArena_ALLOC(arena, 50 * 1024);
    void *free1 = InfraArena_ALLOC(arena, 200 * 1024);
    void *free3 = InfraArena_ALLOC(arena, 90 * 1024);
    InfraArena_ALLOC(arena, 100 * 1024);

    InfraArena_Free(arena);

    void *newChunk1 = InfraArena_ALLOC(arena, 200 * 1024);
    cr_assert_eq(newChunk1, free1);

    InfraArena_ALLOC(arena, 100 * 1024);

    void *newChunk3 = InfraArena_ALLOC(arena, 90 * 1024);
    cr_assert_eq(newChunk3, free3);

    InfraArena_ALLOC(arena, 50 * 1024);

    void *newChunk5 = InfraArena_ALLOC(arena, 50 * 1024);
    cr_assert_eq(newChunk5, free5);
}
