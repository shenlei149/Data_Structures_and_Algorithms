#ifndef ELEMENTARY_STACK_INCLUDED
#define ELEMENTARY_STACK_INCLUDED

#include <stdbool.h>

#define T Stack_T
typedef struct T *T;

extern T Stack_New(void);
extern bool Stack_Empty(T stack);
extern void Stack_Push(T stack, void *item);
extern void *Stack_Peek(T stack);
extern void *Stack_Pop(T stack);
extern void Stack_Free(T *stack);

#undef T

#endif
