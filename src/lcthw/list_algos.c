#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>

/** Print each element of the list */
void List_print(List *list) {
    if (list) {
        LIST_FOREACH(list, first, next, cur) {
            printf("%s ", (char *) cur->value);
        }
        printf("\n");
    } else {
        printf("NULL");
    }
}

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
ListNode *getAt(List *list, int index)
{
    check(index >= 0 && index <= (List_count(list) - 1), "Invalid index for list, received");
    
    int aux_index = 0;
    LIST_FOREACH(list, first, next, cur) {
        if (aux_index == index) {
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

/** Bubble sort - retorn 0 on sucess 1 on fail for sort the list */
int List_bubble_sort(List *list, List_compare cp)
{
    int n = List_count(list);
    int swapped = 0;
    int index = 1;
    do {
        swapped = 0;
        for (index = 1; index < n; index++) {
            // need take the value from index on linkedlist
            ListNode *ele1 = getAt(list, index - 1);
            check(ele1 != NULL, "Element at index %d was not found", (index-1));
            ListNode *ele2 = getAt(list, index);
            check(ele2 != NULL, "Element at index %d was not found", (index));
            if (cp(ele1->value, ele2->value) > 0) {
                swap_nodes(ele1, ele2);
                swapped = 1;
            }
        }
    
    } while (swapped != 0);
    
    return 0;

error:
    return 1;
}

// pseudo code
/*
function merge_sort(list m)
    // Base case. A list of zero or one elements is sorted, by definition.
    if length of m ≤ 1 then
        return m

    // Recursive case. First, divide the list into equal-sized sublists
    // consisting of the first half and second half of the list.
    // This assumes lists start at index 0.
    var left := empty list
    var right := empty list
    for each x with index i in m do
        if i < (length of m)/2 then
            add x to left
        else
            add x to right

    // Recursively sort both sublists.
    left := merge_sort(left)
    right := merge_sort(right)

    // Then merge the now-sorted sublists.
    return merge(left, right)


function merge(left, right)
    var result := empty list

    while left is not empty and right is not empty do
        if first(left) ≤ first(right) then
            append first(left) to result
            # rest(left) -> return the list without the first element
            left := rest(left)
        else
            append first(right) to result
            right := rest(right)

    // Either left or right may have elements left; consume them.
    // (Only one of the following loops will actually be entered.)
    while left is not empty do
        append first(left) to result
        left := rest(left)
    while right is not empty do
        append first(right) to result
        right := rest(right)
    return result

*/


List *List_merge_sort(List *list, List_compare cb) {
    check(list != NULL, "The given list is null");
    int list_size = List_count(list);
    if (list_size <= 1) {
        return list;
    }
    ListNode *element = NULL;
    List *left = List_create();
    List *right = List_create();
    // split the list in left and right sublists
    int i = 0;
    for (i = 0; i < list_size; i++) {
        element = getAt(list, i);
        check(element != NULL, "Value at index %d was not found", i);
        if (i < (list_size / 2)) {
            List_push(left, element->value);
        } else {
            List_push(right, element->value);
        }
    }
    // recursively sort the sublists
    left = List_merge_sort(left, cb);
    right = List_merge_sort(right, cb);
    // join the two sorted sublists
    return merge(left, right, cb);

error:
    log_err("merge_sort fail");
    List_destroy(left);
    List_destroy(right);
    return NULL;
}

List *merge(List *listLeft, List *listRight, List_compare cb) {
    List *result = List_create();
    
    check(List_count(listLeft) >= 1, "Left list is null");
    check(List_count(listRight) >= 1, "Right list is null");
    
    // continues take the first element of each list and add to result
    while (List_count(listLeft) > 0 && List_count(listRight) > 0) {
        if (cb(listLeft->first->value, listRight->first->value)  <= 0) {
            List_push(result, List_shift(listLeft));
        } else {
            List_push(result, List_shift(listRight));
        }
    }
    // add remainder elements to result
    while (List_count(listLeft) > 0) {
        List_push(result, List_shift(listLeft));
    }
    while (List_count(listRight) > 0) {
        List_push(result, List_shift(listRight));
    }
    
    return result;

error:
    log_err("merge fail");
    List_destroy(result);
    return NULL;
}

 
