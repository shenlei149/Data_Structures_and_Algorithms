#include <stdio.h>
#include <stdlib.h>

#include "infra_assert.h"

void InfraAssert_assert(const char *e, const char *file, int line, const char *func)
{
    ((void)printf("%s:%d(%s): failed assertion '%s'\n", file, line, func, e), abort());
}
