#include <stdio.h>
#include <stdlib.h>

#include "infra_assert.h"
#include "infra_color.h"

void Assert_assert(const char *e, const char *file, int line, const char *func)
{
    printf(ANSI_COLOR_YELLOW "%s:%d" ANSI_COLOR_RESET, file, line);
    printf(ANSI_COLOR_RED "(%s)" ANSI_COLOR_RESET, func);
    printf(ANSI_COLOR_MAGENTA " failed assertion '%s'\n" ANSI_COLOR_RESET, e);
    abort();
}
