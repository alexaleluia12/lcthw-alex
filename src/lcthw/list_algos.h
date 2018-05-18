#ifndef lcthw_List_algos_h
#define lcthw_List_algos_h

#include <lcthw/list.h>

typedef int (*List_compare)(void *value1, void *value2);

int List_bubble_sort(List *list, List_compare cb);

int swap_nodes(ListNode *node1, ListNode *node2);

ListNode * getAt(List *list, int index);

#endif