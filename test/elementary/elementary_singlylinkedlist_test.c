#include <criterion/criterion.h>

#include "../../src/elementary/elementary_singlylinkedlist.h"

static SinglyLinkedList_T list;

static void createList()
{
    list = SinglyLinkedList_New();
}

static void freeList()
{
    cr_assert_not_null(list);

    SinglyLinkedList_Free(&list);

    cr_assert_null(list);
}

TestSuite(elementary_singlylinkedlist,
          .init = createList,
          .fini = freeList);

Test(elementary_singlylinkedlist, empty)
{
    cr_assert_not_null(list);
    cr_assert_eq(SinglyLinkedList_Length(list), 0);
}

Test(elementary_singlylinkedlist, first_methods)
{
    cr_assert_null(SinglyLinkedList_GetFirst(list));
    cr_assert_null(SinglyLinkedList_GetFirstNode(list));

    SinglyLinkedList_RemoveFirst(list);

    int items[] = {1, 2, 3, 4, 5};

    SinglyLinkedList_AddFirst(list, &items[0]);
    cr_assert_eq(SinglyLinkedList_Length(list), 1);
    cr_assert_eq(SinglyLinkedList_GetValue(SinglyLinkedList_GetFirstNode(list)), &items[0]);
    cr_assert_eq(*(int *)SinglyLinkedList_GetValue(SinglyLinkedList_GetFirstNode(list)), 1);
    cr_assert_eq(SinglyLinkedList_GetFirst(list), &items[0]);
    cr_assert_eq(*(int *)SinglyLinkedList_GetFirst(list), 1);

    SinglyLinkedList_AddFirst(list, &items[1]);
    SinglyLinkedList_AddFirst(list, &items[2]);
    cr_assert_eq(SinglyLinkedList_Length(list), 3);
    SinglyLinkedNode_T first = SinglyLinkedList_GetFirstNode(list);
    cr_assert_eq(SinglyLinkedList_GetValue(first), &items[2]);
    cr_assert_eq(SinglyLinkedList_GetFirst(list), &items[2]);
    SinglyLinkedNode_T second = SinglyLinkedList_NextNode(first);
    cr_assert_eq(SinglyLinkedList_GetValue(second), &items[1]);
    SinglyLinkedNode_T third = SinglyLinkedList_NextNode(second);
    cr_assert_eq(SinglyLinkedList_GetValue(third), &items[0]);

    SinglyLinkedList_RemoveFirst(list);
    cr_assert_eq(SinglyLinkedList_Length(list), 2);
    first = SinglyLinkedList_GetFirstNode(list);
    cr_assert_eq(SinglyLinkedList_GetValue(first), &items[1]);

    SinglyLinkedList_AddFirst(list, &items[3]);
    SinglyLinkedList_AddFirst(list, &items[4]);
    cr_assert_eq(SinglyLinkedList_Length(list), 4);
    first = SinglyLinkedList_GetFirstNode(list);
    cr_assert_eq(SinglyLinkedList_GetValue(first), &items[4]);

    SinglyLinkedList_RemoveFirst(list);
    cr_assert_eq(SinglyLinkedList_Length(list), 3);
    first = SinglyLinkedList_GetFirstNode(list);
    cr_assert_eq(SinglyLinkedList_GetValue(first), &items[3]);

    SinglyLinkedList_RemoveFirst(list);
    cr_assert_eq(SinglyLinkedList_Length(list), 2);
    first = SinglyLinkedList_GetFirstNode(list);
    cr_assert_eq(SinglyLinkedList_GetValue(first), &items[1]);

    SinglyLinkedList_RemoveFirst(list);
    SinglyLinkedList_RemoveFirst(list);
    cr_assert_eq(SinglyLinkedList_Length(list), 0);
    cr_assert_null(SinglyLinkedList_GetFirst(list));
    cr_assert_null(SinglyLinkedList_GetFirstNode(list));
}

Test(elementary_singlylinkedlist, last_methods)
{
    cr_assert_null(SinglyLinkedList_GetLast(list));
    cr_assert_null(SinglyLinkedList_GetLastNode(list));

    int items[] = {1, 2, 3, 4, 5};

    SinglyLinkedList_AddLast(list, &items[0]);
    cr_assert_eq(SinglyLinkedList_Length(list), 1);
    cr_assert_eq(SinglyLinkedList_GetValue(SinglyLinkedList_GetLastNode(list)), &items[0]);
    cr_assert_eq(*(int *)SinglyLinkedList_GetValue(SinglyLinkedList_GetLastNode(list)), 1);
    cr_assert_eq(SinglyLinkedList_GetLast(list), &items[0]);
    cr_assert_eq(*(int *)SinglyLinkedList_GetLast(list), 1);

    SinglyLinkedList_AddLast(list, &items[1]);
    SinglyLinkedList_AddLast(list, &items[2]);
    cr_assert_eq(SinglyLinkedList_Length(list), 3);
    SinglyLinkedNode_T last = SinglyLinkedList_GetLastNode(list);
    cr_assert_eq(SinglyLinkedList_GetValue(last), &items[2]);
    cr_assert_eq(SinglyLinkedList_GetLast(list), &items[2]);
    SinglyLinkedNode_T null = SinglyLinkedList_NextNode(last);
    cr_assert_null(null);

    SinglyLinkedList_AddLast(list, &items[3]);
    SinglyLinkedList_AddLast(list, &items[4]);
    cr_assert_eq(SinglyLinkedList_Length(list), 5);
    last = SinglyLinkedList_GetLastNode(list);
    cr_assert_eq(SinglyLinkedList_GetValue(last), &items[4]);
}

Test(elementary_singlylinkedlist, after_methods)
{
    int items[] = {1, 2, 3, 4, 5};

    SinglyLinkedList_AddFirst(list, &items[0]);
    cr_assert_eq(SinglyLinkedList_Length(list), 1);

    SinglyLinkedList_RemoveAfter(list, SinglyLinkedList_GetFirstNode(list));
    cr_assert_eq(SinglyLinkedList_Length(list), 1);
    cr_assert_eq(SinglyLinkedList_GetFirst(list), SinglyLinkedList_GetLast(list));

    SinglyLinkedList_AddAfter(list, SinglyLinkedList_GetFirstNode(list), &items[1]);
    cr_assert_eq(SinglyLinkedList_GetValue(SinglyLinkedList_GetLastNode(list)), &items[1]);

    SinglyLinkedList_AddAfter(list, SinglyLinkedList_GetFirstNode(list), &items[2]);
    cr_assert_eq(SinglyLinkedList_GetValue(SinglyLinkedList_GetLastNode(list)), &items[1]);

    SinglyLinkedNode_T first = SinglyLinkedList_GetFirstNode(list);
    SinglyLinkedNode_T second = SinglyLinkedList_NextNode(first);
    SinglyLinkedList_AddAfter(list, second, &items[3]);
    SinglyLinkedList_AddFirst(list, &items[4]);
    cr_assert_eq(SinglyLinkedList_Length(list), 5);

    first = SinglyLinkedList_GetFirstNode(list);
    second = SinglyLinkedList_NextNode(first);
    SinglyLinkedNode_T third = SinglyLinkedList_NextNode(second);
    SinglyLinkedList_RemoveAfter(list, third);
    SinglyLinkedNode_T five = SinglyLinkedList_NextNode(third);
    cr_assert_eq(five, SinglyLinkedList_GetLastNode(list));

    SinglyLinkedList_RemoveAfter(list, third);
    cr_assert_eq(SinglyLinkedList_Length(list), 3);
    cr_assert_eq(third, SinglyLinkedList_GetLastNode(list));
}

Test(elementary_singlylinkedlist, add)
{
    int items[] = {1, 2, 3, 4, 5};

    SinglyLinkedList_Add(list, &items[0], &items[1], NULL);
    cr_assert_eq(SinglyLinkedList_Length(list), 2);
    cr_assert_eq(SinglyLinkedList_GetLast(list), &items[1]);
    cr_assert_eq(SinglyLinkedList_GetFirst(list), &items[0]);

    SinglyLinkedList_Add(list, &items[2], &items[3], &items[4], NULL);
    cr_assert_eq(SinglyLinkedList_Length(list), 5);
    cr_assert_eq(SinglyLinkedList_GetLast(list), &items[4]);
}

Test(elementary_singlylinkedlist, reverse)
{
    int items[] = {1, 2, 3, 4, 5};

    SinglyLinkedList_Reverse(list);
    cr_assert_not_null(list);
    cr_assert_eq(SinglyLinkedList_Length(list), 0);

    SinglyLinkedList_AddFirst(list, &items[0]);
    SinglyLinkedList_Reverse(list);
    cr_assert_eq(SinglyLinkedList_Length(list), 1);
    cr_assert_eq(SinglyLinkedList_GetFirst(list), &items[0]);
    cr_assert_eq(SinglyLinkedList_GetLast(list), &items[0]);

    SinglyLinkedList_AddLast(list, &items[1]);
    SinglyLinkedList_Reverse(list);
    cr_assert_eq(SinglyLinkedList_Length(list), 2);
    cr_assert_eq(SinglyLinkedList_GetFirst(list), &items[1]);
    cr_assert_eq(SinglyLinkedList_GetLast(list), &items[0]);

    SinglyLinkedList_AddFirst(list, &items[2]);
    SinglyLinkedList_Reverse(list);
    cr_assert_eq(SinglyLinkedList_Length(list), 3);
    cr_assert_eq(SinglyLinkedList_GetFirst(list), &items[0]);
    cr_assert_eq(SinglyLinkedList_GetLast(list), &items[2]);

    SinglyLinkedList_Add(list, &items[3], &items[4], NULL);
    SinglyLinkedList_Reverse(list);
    cr_assert_eq(SinglyLinkedList_Length(list), 5);
    SinglyLinkedNode_T first = SinglyLinkedList_GetFirstNode(list);
    cr_assert_eq(*(int *)SinglyLinkedList_GetValue(first), 5);
    SinglyLinkedNode_T next = SinglyLinkedList_NextNode(first);
    cr_assert_eq(*(int *)SinglyLinkedList_GetValue(next), 4);
    next = SinglyLinkedList_NextNode(next);
    cr_assert_eq(*(int *)SinglyLinkedList_GetValue(next), 3);
    next = SinglyLinkedList_NextNode(next);
    cr_assert_eq(*(int *)SinglyLinkedList_GetValue(next), 2);
    next = SinglyLinkedList_NextNode(next);
    cr_assert_eq(*(int *)SinglyLinkedList_GetValue(next), 1);

    next = SinglyLinkedList_NextNode(next);
    cr_assert_null(next);
}
