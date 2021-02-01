#ifndef INFRA_ASSERT_INCLUDED
#define INFRA_ASSERT_INCLUDED

#define Assert_ASSERT(e, filename, line) \
((void)((e) ? ((void)0) : Assert_assert(#e, filename, line, __func__)))

// TODO move this comment to README
// Not recommended and might be modified
extern void Assert_assert(const char *e, const char *file, int line, const char *func);

#endif
