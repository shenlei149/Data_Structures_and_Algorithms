#include <stdio.h>
#include <stdarg.h>

#include "elementary_singlylinkedlist.h"
#include "../infra/infra_memory.h"
#include "../infra/infra_assert.h"

#define TList SinglyLinkedList_T
#define TNode SinglyLinkedNode_T

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

TList SinglyLinkedList_New()
{
    TList list;
    Memory_NEW0(list);
    return list;
}

void SinglyLinkedList_Free(TList *list)
{
    Assert_ASSERT(list && *list, __FILE__, __LINE__);

    TNode cur = (*list)->header;
    while (cur != (*list)->tail)
    {
        TNode next = cur->next;
        Memory_FREE(cur);
        cur = next;
    }

    Memory_FREE(cur);
    Memory_FREE(*list);
}

void SinglyLinkedList_Add(TList list, void *item, ...)
{
    Assert_ASSERT(list, __FILE__, __LINE__);

    va_list ap;
    va_start(ap, item);

    for (; item; item = va_arg(ap, void *))
    {
        SinglyLinkedList_AddLast(list, item);
    }

    va_end(ap);
}

void SinglyLinkedList_Reverse(TList list)
{
    Assert_ASSERT(list, __FILE__, __LINE__);

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

int SinglyLinkedList_Length(TList list)
{
    Assert_ASSERT(list, __FILE__, __LINE__);

    return list->length;
}

static TNode newNode(void *item)
{
    TNode newNode;
    Memory_NEW0(newNode);
    newNode->item = item;
    return newNode;
}

void SinglyLinkedList_AddFirst(TList list, void *item)
{
    Assert_ASSERT(list, __FILE__, __LINE__);

    TNode new = newNode(item);
    new->next = list->header;
    list->header = new;

    if (list->length == 0)
    {
        list->tail = new;
    }

    list->length++;
}

void SinglyLinkedList_RemoveFirst(TList list)
{
    Assert_ASSERT(list, __FILE__, __LINE__);

    if (list->header != NULL)
    {
        TNode first = list->header;
        list->header = first->next;
        if (list->header == NULL)
        {
            list->tail = NULL;
        }

        Memory_FREE(first);

        list->length--;
    }
}

void *SinglyLinkedList_GetFirst(TList list)
{
    Assert_ASSERT(list, __FILE__, __LINE__);

    if (list->header == NULL)
    {
        return NULL;
    }

    return list->header->item;
}

TNode SinglyLinkedList_GetFirstNode(TList list)
{
    Assert_ASSERT(list, __FILE__, __LINE__);

    return list->header;
}

void SinglyLinkedList_AddLast(TList list, void *item)
{
    Assert_ASSERT(list, __FILE__, __LINE__);

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

void *SinglyLinkedList_GetLast(TList list)
{
    Assert_ASSERT(list, __FILE__, __LINE__);

    if (list->tail == NULL)
    {
        return NULL;
    }

    return list->tail->item;
}

TNode SinglyLinkedList_GetLastNode(TList list)
{
    Assert_ASSERT(list, __FILE__, __LINE__);

    return list->tail;
}

void SinglyLinkedList_AddAfter(TList list, TNode node, void *item)
{
    Assert_ASSERT(list, __FILE__, __LINE__);
    Assert_ASSERT(node, __FILE__, __LINE__);
    if (list->tail == node)
    {
        SinglyLinkedList_AddLast(list, item);
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

void SinglyLinkedList_RemoveAfter(TList list, TNode node)
{
    Assert_ASSERT(list, __FILE__, __LINE__);
    Assert_ASSERT(node, __FILE__, __LINE__);

    if (list->tail != node)
    {
        TNode next = node->next;
        node->next = next->next;

        if (next == list->tail)
        {
            list->tail = node;
        }

        Memory_FREE(next);

        list->length--;
    }
}

TNode SinglyLinkedList_NextNode(TNode node)
{
    if (node != NULL)
    {
        return node->next;
    }

    return NULL;
}

void *SinglyLinkedList_GetValue(TNode node)
{
    Assert_ASSERT(node, __FILE__, __LINE__);

    return node->item;
}
