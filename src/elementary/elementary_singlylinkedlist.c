#include <stdio.h>
#include <stdarg.h>

#include "elementary_singlylinkedlist.h"
#include "../infra/infra_memory.h"
#include "../infra/infra_assert.h"

#define TList ElementarySinglyLinkedList_T
#define TNode ElementarySinglyLinkedNode_T

struct TList
{
    TNode header;
    TNode tail;
    int length;
};

struct TNode
{
    TNode next;
    void *item;
};

TList ElementarySLL_New()
{
    TList list;
    InfraMemory_NEW0(list);
    return list;
}

void ElementarySLL_Free(TList *list)
{
    InfraAssert_ASSERT(list && *list, __FILE__, __LINE__);

    TNode cur = (*list)->header;
    while (cur != (*list)->tail)
    {
        TNode next = cur->next;
        InfraMemory_FREE(cur);
        cur = next;
    }

    InfraMemory_FREE(cur);
    InfraMemory_FREE(*list);
}

void ElementarySLL_Add(TList list, void *item, ...)
{
    InfraAssert_ASSERT(list, __FILE__, __LINE__);

    va_list ap;
    va_start(ap, item);

    for (; item; item = va_arg(ap, void *))
    {
        ElementarySLL_AddLast(list, item);
    }

    va_end(ap);
}

void ElementarySLL_Reverse(TList list)
{
    InfraAssert_ASSERT(list, __FILE__, __LINE__);

    if (list->length != 0 && list->length != 1)
    {
        TNode first = list->header;
        TNode second = first->next;
        while (first != list->tail)
        {
            TNode next = second->next;
            second->next = first;
            first = second;
            second = next;
        }

        TNode tmp = list->header;
        list->header = list->tail;
        list->tail = tmp;

        list->tail->next = NULL;
    }
}

int ElementarySLL_Length(TList list)
{
    InfraAssert_ASSERT(list, __FILE__, __LINE__);

    return list->length;
}

static TNode newNode(void *item)
{
    TNode newNode;
    InfraMemory_NEW0(newNode);
    newNode->item = item;
    return newNode;
}

void ElementarySLL_AddFirst(TList list, void *item)
{
    InfraAssert_ASSERT(list, __FILE__, __LINE__);

    TNode new = newNode(item);
    new->next = list->header;
    list->header = new;

    if (list->length == 0)
    {
        list->tail = new;
    }

    list->length++;
}

void ElementarySLL_RemoveFirst(TList list)
{
    InfraAssert_ASSERT(list, __FILE__, __LINE__);

    if (list->header != NULL)
    {
        TNode first = list->header;
        list->header = first->next;
        if (list->header == NULL)
        {
            list->tail = NULL;
        }

        InfraMemory_FREE(first);

        list->length--;
    }
}

void *ElementarySLL_GetFirst(TList list)
{
    InfraAssert_ASSERT(list, __FILE__, __LINE__);

    if (list->header == NULL)
    {
        return NULL;
    }

    return list->header->item;
}

TNode ElementarySLL_GetFirstNode(TList list)
{
    InfraAssert_ASSERT(list, __FILE__, __LINE__);

    return list->header;
}

void ElementarySLL_AddLast(TList list, void *item)
{
    InfraAssert_ASSERT(list, __FILE__, __LINE__);

    TNode new = newNode(item);
    if (list->length == 0)
    {
        list->header = new;
    }
    else
    {
        list->tail->next = new;
    }

    list->tail = new;

    list->length++;
}

void *ElementarySLL_GetLast(TList list)
{
    InfraAssert_ASSERT(list, __FILE__, __LINE__);

    if (list->tail == NULL)
    {
        return NULL;
    }

    return list->tail->item;
}

TNode ElementarySLL_GetLastNode(TList list)
{
    InfraAssert_ASSERT(list, __FILE__, __LINE__);

    return list->tail;
}

void ElementarySLL_AddAfter(TList list, TNode node, void *item)
{
    InfraAssert_ASSERT(list, __FILE__, __LINE__);
    InfraAssert_ASSERT(node, __FILE__, __LINE__);
    if (list->tail == node)
    {
        ElementarySLL_AddLast(list, item);
    }
    else
    {
        TNode new = newNode(item);
        TNode next = node->next;
        node->next = new;
        new->next = next;
        list->length++;
    }
}

void ElementarySLL_RemoveAfter(TList list, TNode node)
{
    InfraAssert_ASSERT(list, __FILE__, __LINE__);
    InfraAssert_ASSERT(node, __FILE__, __LINE__);

    if (list->tail != node)
    {
        TNode next = node->next;
        node->next = next->next;

        if (next == list->tail)
        {
            list->tail = node;
        }

        InfraMemory_FREE(next);

        list->length--;
    }
}

TNode ElementarySLL_NextNode(TNode node)
{
    if (node != NULL)
    {
        return node->next;
    }

    return NULL;
}

void *ElementarySLL_GetValue(TNode node)
{
    InfraAssert_ASSERT(node, __FILE__, __LINE__);

    return node->item;
}
