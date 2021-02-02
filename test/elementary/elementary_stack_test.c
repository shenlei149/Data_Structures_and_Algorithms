#include <criterion/criterion.h>

#include "../../src/elementary/elementary_stack.h"

TestSuite(elementary_stack);

Test(elementary_stack, all)
{
    Stack_T stack = Stack_New();

    cr_assert(Stack_Empty(stack));

    int items[] = {1, 2, 3, 4, 5};

    Stack_Push(stack, &items[0]);

    cr_assert_not(Stack_Empty(stack));

    cr_assert_eq(*(int *)Stack_Peek(stack), 1);

    Stack_Push(stack, &items[1]);
    Stack_Push(stack, &items[2]);
    Stack_Push(stack, &items[3]);

    cr_assert_eq(*(int *)Stack_Peek(stack), 4);
    cr_assert_eq(*(int *)Stack_Pop(stack), 4);
    cr_assert_eq(*(int *)Stack_Peek(stack), 3);

    Stack_Push(stack, &items[4]);
    cr_assert_eq(*(int *)Stack_Pop(stack), 5);
    cr_assert_eq(*(int *)Stack_Pop(stack), 3);
    cr_assert_eq(*(int *)Stack_Pop(stack), 2);
    cr_assert_eq(*(int *)Stack_Pop(stack), 1);
    cr_assert(Stack_Empty(stack));

    Stack_Free(&stack);
    cr_assert_null(stack);
}
