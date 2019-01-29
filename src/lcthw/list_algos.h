#ifndef lcthw_List_algos_h
#define lcthw_List_algos_h

#include <lcthw/list.h>

/** function pointer to compare two values */
typedef int (*List_compare)(void *value1, void *value2);
/** Bubble sort - retorn 0 on sucess 1 on fail for sort the list */
int List_bubble_sort(List *list, List_compare cb);
/** Exchanges values nodes */
int swap_nodes(ListNode *node1, ListNode *node2);
/** Return the node located at index */
ListNode * getAt(List *list, int index);
/** Merge sort - return the sorted list */
List * List_merge_sort(List *list, List_compare cb);
/** parte of Merge sorte - join to list using */
List * merge(List *listLeft, List *listRight, List_compare cb);
/** Print each element of the list */
void List_print(List *list);

#endif
