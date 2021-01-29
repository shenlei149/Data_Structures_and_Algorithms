#ifndef ELEMENTARY_SINGLYLINKEDLIST_INCLUDED
#define ELEMENTARY_SINGLYLINKEDLIST_INCLUDED

#define TList ElementarySinglyLinkedList_T
#define TNode ElementarySinglyLinkedNode_T
typedef struct TList *TList;
typedef struct TNode *TNode;

extern TList ElementarySLL_New();
extern void ElementarySLL_Free(TList *list);

// last one should be NULL
extern void ElementarySLL_Add(TList list, void *item, ...);
extern void ElementarySLL_Reverse(TList list);
extern int ElementarySLL_Length(TList list);

extern void ElementarySLL_AddFirst(TList list, void *item);
extern void ElementarySLL_RemoveFirst(TList list);
extern void *ElementarySLL_GetFirst(TList list);
extern TNode ElementarySLL_GetFirstNode(TList list);

extern void ElementarySLL_AddLast(TList list, void *item);
extern void *ElementarySLL_GetLast(TList list);
extern TNode ElementarySLL_GetLastNode(TList list);

extern void ElementarySLL_AddAfter(TList list, TNode node, void *item);
extern void ElementarySLL_RemoveAfter(TList list, TNode node);

extern TNode ElementarySLL_NextNode(TNode node);
extern void *ElementarySLL_GetValue(TNode node);

#undef TList
#undef TNode

#endif
