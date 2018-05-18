#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>

/** Exchanges values nodes */
int swap_nodes(ListNode *node1, ListNode *node2)
{
    check(node1, "Node 1 can't be null");
    check(node2, "Node 2 can't be null");
    
    void * tvalue = node1->value;
    node1->value = node2->value;
    node2->value = tvalue;
    
    return 1;

error:
    return 0;
}

/** Return the node located at index */
ListNode * getAt(List *list, int index)
{
    check(index >= 0 && index <= (List_count(list) - 1), "Invalid index for list, received");
    
    int aux_index = 0;
    LIST_FOREACH(list, first, next, cur) {
        if(aux_index == index) {
            return cur;
        }
        aux_index++;
    }
    
    return NULL;

error:
    log_err("Was not possible to find an element located at index %d", index);
    return NULL;
}

// pseudo code for bubble sort
/*
procedure bubbleSort( A : list of sortable items )
    n = length(A)
    repeat
        swapped = false
        for i = 1 to n-1 inclusive do
            // if this pair is out of order
            if A[i-1] > A[i] then
                // swap them and remember something changed
                swap( A[i-1], A[i] )
                swapped = true
            end if
        end for
    until not swapped
end procedure
*/

// retorn 0 on sucess 1 on fail for sort the list
int List_bubble_sort(List *list, List_compare cp)
{
    int n = List_count(list);
    int swapped = 0;
    int index = 1;
    do {
        swapped = 0;
        for(index=1; index<n; index++) {
            // need take the value from index on linkedlist
            ListNode *ele1 = getAt(list, index - 1);
            check(ele1 != NULL, "Element at index %d was not found", (index-1));
            ListNode *ele2 = getAt(list, index);
            check(ele2 != NULL, "Element at index %d was not found", (index));
            if( cp( ele1->value, ele2->value ) > 0 ) {
                swap_nodes(ele1, ele2);
                swapped = 1;
            }
        }
    
    } while(swapped != 0);
    
    return 0;

error:
    return 1;
}



