#include "elementary_stack.h"
#include "elementary_singlylinkedlist.h"
#include "../infra/infra_memory.h"
#include "../infra/infra_assert.h"

#define T Stack_T

struct T
{
    SinglyLinkedList_T list;
};

T Stack_New(void)
{
    T stack;
    Memory_NEW0(stack);

    stack->list = SinglyLinkedList_New();

    return stack;
}

bool Stack_Empty(T stack)
{
    Assert_ASSERT(stack, __FILE__, __LINE__);
    return SinglyLinkedList_Length(stack->list) == 0;
}

void Stack_Push(T stack, void *item)
{
    Assert_ASSERT(stack, __FILE__, __LINE__);
    SinglyLinkedList_AddFirst(stack->list, item);
}

void *Stack_Peek(T stack)
{
    Assert_ASSERT(stack, __FILE__, __LINE__);
    Assert_ASSERT(!Stack_Empty(stack), __FILE__, __LINE__);
    return SinglyLinkedList_GetFirst(stack->list);
}

void *Stack_Pop(T stack)
{
    Assert_ASSERT(stack, __FILE__, __LINE__);
    Assert_ASSERT(!Stack_Empty(stack), __FILE__, __LINE__);
    void *result = SinglyLinkedList_GetFirst(stack->list);
    SinglyLinkedList_RemoveFirst(stack->list);

    return result;
}

void Stack_Free(T *stack)
{
    Assert_ASSERT(stack && *stack, __FILE__, __LINE__);
    SinglyLinkedList_Free(&(*stack)->list);
    Memory_FREE(*stack);
}
