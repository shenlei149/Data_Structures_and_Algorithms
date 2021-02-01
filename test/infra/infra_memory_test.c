#include <criterion/criterion.h>

#include "../../src/infra/infra_memory.h"

TestSuite(infra_memory);

Test(infra_memory, mem)
{
    void *ptr = Memory_ALLOC(100);
    Memory_CALLOC(4, 100);
    Memory_RESIZE(ptr, 200);
    Memory_FREE(ptr);
    cr_assert_null(ptr);
}
