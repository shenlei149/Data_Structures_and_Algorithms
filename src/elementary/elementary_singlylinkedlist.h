#ifndef ELEMENTARY_SINGLYLINKEDLIST_INCLUDED
#define ELEMENTARY_SINGLYLINKEDLIST_INCLUDED

#define TList SinglyLinkedList_T
#define TNode SinglyLinkedNode_T
typedef struct TList *TList;
typedef struct TNode *TNode;

extern TList SinglyLinkedList_New();
extern void SinglyLinkedList_Free(TList *list);

// last one should be NULL
extern void SinglyLinkedList_Add(TList list, void *item, ...);
extern void SinglyLinkedList_Reverse(TList list);
extern int SinglyLinkedList_Length(TList list);

extern void SinglyLinkedList_AddFirst(TList list, void *item);
extern void SinglyLinkedList_RemoveFirst(TList list);
extern void *SinglyLinkedList_GetFirst(TList list);
extern TNode SinglyLinkedList_GetFirstNode(TList list);

extern void SinglyLinkedList_AddLast(TList list, void *item);
extern void *SinglyLinkedList_GetLast(TList list);
extern TNode SinglyLinkedList_GetLastNode(TList list);

extern void SinglyLinkedList_AddAfter(TList list, TNode node, void *item);
extern void SinglyLinkedList_RemoveAfter(TList list, TNode node);

extern TNode SinglyLinkedList_NextNode(TNode node);
extern void *SinglyLinkedList_GetValue(TNode node);

#undef TList
#undef TNode

#endif
