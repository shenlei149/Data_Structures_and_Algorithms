#include <criterion/criterion.h>

#include "../../src/elementary/elementary_singlylinkedlist.h"

static ElementarySinglyLinkedList_T list;

static void createList()
{
    list = ElementarySLL_New();
}

static void freeList()
{
    cr_assert_not_null(list);

    ElementarySLL_Free(&list);

    cr_assert_null(list);
}

TestSuite(elementary_singlylinkedlist,
          .init = createList,
          .fini = freeList);

Test(elementary_singlylinkedlist, empty)
{
    cr_assert_not_null(list);
    cr_assert_eq(ElementarySLL_Length(list), 0);
}

Test(elementary_singlylinkedlist, first_methods)
{
    cr_assert_null(ElementarySLL_GetFirst(list));
    cr_assert_null(ElementarySLL_GetFirstNode(list));

    ElementarySLL_RemoveFirst(list);

    int items[] = {1, 2, 3, 4, 5};

    ElementarySLL_AddFirst(list, &items[0]);
    cr_assert_eq(ElementarySLL_Length(list), 1);
    cr_assert_eq(ElementarySLL_GetValue(ElementarySLL_GetFirstNode(list)), &items[0]);
    cr_assert_eq(*(int *)ElementarySLL_GetValue(ElementarySLL_GetFirstNode(list)), 1);
    cr_assert_eq(ElementarySLL_GetFirst(list), &items[0]);
    cr_assert_eq(*(int *)ElementarySLL_GetFirst(list), 1);

    ElementarySLL_AddFirst(list, &items[1]);
    ElementarySLL_AddFirst(list, &items[2]);
    cr_assert_eq(ElementarySLL_Length(list), 3);
    ElementarySinglyLinkedNode_T first = ElementarySLL_GetFirstNode(list);
    cr_assert_eq(ElementarySLL_GetValue(first), &items[2]);
    cr_assert_eq(ElementarySLL_GetFirst(list), &items[2]);
    ElementarySinglyLinkedNode_T second = ElementarySLL_NextNode(first);
    cr_assert_eq(ElementarySLL_GetValue(second), &items[1]);
    ElementarySinglyLinkedNode_T third = ElementarySLL_NextNode(second);
    cr_assert_eq(ElementarySLL_GetValue(third), &items[0]);

    ElementarySLL_RemoveFirst(list);
    cr_assert_eq(ElementarySLL_Length(list), 2);
    first = ElementarySLL_GetFirstNode(list);
    cr_assert_eq(ElementarySLL_GetValue(first), &items[1]);

    ElementarySLL_AddFirst(list, &items[3]);
    ElementarySLL_AddFirst(list, &items[4]);
    cr_assert_eq(ElementarySLL_Length(list), 4);
    first = ElementarySLL_GetFirstNode(list);
    cr_assert_eq(ElementarySLL_GetValue(first), &items[4]);

    ElementarySLL_RemoveFirst(list);
    cr_assert_eq(ElementarySLL_Length(list), 3);
    first = ElementarySLL_GetFirstNode(list);
    cr_assert_eq(ElementarySLL_GetValue(first), &items[3]);

    ElementarySLL_RemoveFirst(list);
    cr_assert_eq(ElementarySLL_Length(list), 2);
    first = ElementarySLL_GetFirstNode(list);
    cr_assert_eq(ElementarySLL_GetValue(first), &items[1]);

    ElementarySLL_RemoveFirst(list);
    ElementarySLL_RemoveFirst(list);
    cr_assert_eq(ElementarySLL_Length(list), 0);
    cr_assert_null(ElementarySLL_GetFirst(list));
    cr_assert_null(ElementarySLL_GetFirstNode(list));
}

Test(elementary_singlylinkedlist, last_methods)
{
    cr_assert_null(ElementarySLL_GetLast(list));
    cr_assert_null(ElementarySLL_GetLastNode(list));

    int items[] = {1, 2, 3, 4, 5};

    ElementarySLL_AddLast(list, &items[0]);
    cr_assert_eq(ElementarySLL_Length(list), 1);
    cr_assert_eq(ElementarySLL_GetValue(ElementarySLL_GetLastNode(list)), &items[0]);
    cr_assert_eq(*(int *)ElementarySLL_GetValue(ElementarySLL_GetLastNode(list)), 1);
    cr_assert_eq(ElementarySLL_GetLast(list), &items[0]);
    cr_assert_eq(*(int *)ElementarySLL_GetLast(list), 1);

    ElementarySLL_AddLast(list, &items[1]);
    ElementarySLL_AddLast(list, &items[2]);
    cr_assert_eq(ElementarySLL_Length(list), 3);
    ElementarySinglyLinkedNode_T last = ElementarySLL_GetLastNode(list);
    cr_assert_eq(ElementarySLL_GetValue(last), &items[2]);
    cr_assert_eq(ElementarySLL_GetLast(list), &items[2]);
    ElementarySinglyLinkedNode_T null = ElementarySLL_NextNode(last);
    cr_assert_null(null);

    ElementarySLL_AddLast(list, &items[3]);
    ElementarySLL_AddLast(list, &items[4]);
    cr_assert_eq(ElementarySLL_Length(list), 5);
    last = ElementarySLL_GetLastNode(list);
    cr_assert_eq(ElementarySLL_GetValue(last), &items[4]);
}

Test(elementary_singlylinkedlist, after_methods)
{
    int items[] = {1, 2, 3, 4, 5};

    ElementarySLL_AddFirst(list, &items[0]);
    cr_assert_eq(ElementarySLL_Length(list), 1);

    ElementarySLL_RemoveAfter(list, ElementarySLL_GetFirstNode(list));
    cr_assert_eq(ElementarySLL_Length(list), 1);
    cr_assert_eq(ElementarySLL_GetFirst(list), ElementarySLL_GetLast(list));

    ElementarySLL_AddAfter(list, ElementarySLL_GetFirstNode(list), &items[1]);
    cr_assert_eq(ElementarySLL_GetValue(ElementarySLL_GetLastNode(list)), &items[1]);

    ElementarySLL_AddAfter(list, ElementarySLL_GetFirstNode(list), &items[2]);
    cr_assert_eq(ElementarySLL_GetValue(ElementarySLL_GetLastNode(list)), &items[1]);

    ElementarySinglyLinkedNode_T first = ElementarySLL_GetFirstNode(list);
    ElementarySinglyLinkedNode_T second = ElementarySLL_NextNode(first);
    ElementarySLL_AddAfter(list, second, &items[3]);
    ElementarySLL_AddFirst(list, &items[4]);
    cr_assert_eq(ElementarySLL_Length(list), 5);

    first = ElementarySLL_GetFirstNode(list);
    second = ElementarySLL_NextNode(first);
    ElementarySinglyLinkedNode_T third = ElementarySLL_NextNode(second);
    ElementarySLL_RemoveAfter(list, third);
    ElementarySinglyLinkedNode_T five = ElementarySLL_NextNode(third);
    cr_assert_eq(five, ElementarySLL_GetLastNode(list));

    ElementarySLL_RemoveAfter(list, third);
    cr_assert_eq(ElementarySLL_Length(list), 3);
    cr_assert_eq(third, ElementarySLL_GetLastNode(list));
}

Test(elementary_singlylinkedlist, add)
{
    int items[] = {1, 2, 3, 4, 5};

    ElementarySLL_Add(list, &items[0], &items[1], NULL);
    cr_assert_eq(ElementarySLL_Length(list), 2);
    cr_assert_eq(ElementarySLL_GetLast(list), &items[1]);
    cr_assert_eq(ElementarySLL_GetFirst(list), &items[0]);

    ElementarySLL_Add(list, &items[2], &items[3], &items[4], NULL);
    cr_assert_eq(ElementarySLL_Length(list), 5);
    cr_assert_eq(ElementarySLL_GetLast(list), &items[4]);
}

Test(elementary_singlylinkedlist, reverse)
{
    int items[] = {1, 2, 3, 4, 5};

    ElementarySLL_Reverse(list);
    cr_assert_not_null(list);
    cr_assert_eq(ElementarySLL_Length(list), 0);

    ElementarySLL_AddFirst(list, &items[0]);
    ElementarySLL_Reverse(list);
    cr_assert_eq(ElementarySLL_Length(list), 1);
    cr_assert_eq(ElementarySLL_GetFirst(list), &items[0]);
    cr_assert_eq(ElementarySLL_GetLast(list), &items[0]);

    ElementarySLL_AddLast(list, &items[1]);
    ElementarySLL_Reverse(list);
    cr_assert_eq(ElementarySLL_Length(list), 2);
    cr_assert_eq(ElementarySLL_GetFirst(list), &items[1]);
    cr_assert_eq(ElementarySLL_GetLast(list), &items[0]);

    ElementarySLL_AddFirst(list, &items[2]);
    ElementarySLL_Reverse(list);
    cr_assert_eq(ElementarySLL_Length(list), 3);
    cr_assert_eq(ElementarySLL_GetFirst(list), &items[0]);
    cr_assert_eq(ElementarySLL_GetLast(list), &items[2]);

    ElementarySLL_Add(list, &items[3], &items[4], NULL);
    ElementarySLL_Reverse(list);
    cr_assert_eq(ElementarySLL_Length(list), 5);
    ElementarySinglyLinkedNode_T first = ElementarySLL_GetFirstNode(list);
    cr_assert_eq(*(int *)ElementarySLL_GetValue(first), 5);
    ElementarySinglyLinkedNode_T next = ElementarySLL_NextNode(first);
    cr_assert_eq(*(int *)ElementarySLL_GetValue(next), 4);
    next = ElementarySLL_NextNode(next);
    cr_assert_eq(*(int *)ElementarySLL_GetValue(next), 3);
    next = ElementarySLL_NextNode(next);
    cr_assert_eq(*(int *)ElementarySLL_GetValue(next), 2);
    next = ElementarySLL_NextNode(next);
    cr_assert_eq(*(int *)ElementarySLL_GetValue(next), 1);

    next = ElementarySLL_NextNode(next);
    cr_assert_null(next);
}
