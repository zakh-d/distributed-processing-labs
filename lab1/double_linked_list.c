#include <stdlib.h>

#include "double_linked_list.h"


element* insert(element *ptr, void* data, int (*comparator)(void*, void*))
{
    /* 
        function should be called like that head->next = insert(head, data, comparator)
    */

    element * p;
    p = ptr->next; 
    if ( p != NULL ) /* is the end of the list */
    {
        if (comparator(data, p->data) > 0)
        {
            p->next = insert(p, data, comparator);
        }
        else
        {
            /* create new element */
            p->previous = (element *) malloc (sizeof(element));
            p = p->previous;
            p->data = data;
            p->next = ptr->next;
            p->previous = ptr;
        }
    }
    else /* end of the list */
    {
        p = ( struct element *) malloc ( sizeof (element ) );
     
        p->data = data;
        p->next = NULL;
        p->previous = ptr;
    }
    return p;
}

void* remove_from_list(element * ptr, int index) {
    /* 
        removes element by index and returns its data 
        ptr - pointer to the dummy element
    */
    element * p = ptr;
    while (index >= 0 && p != NULL) {
        p = p->next;
        index--;
    }



    if (p == NULL) {
        return NULL;
    }

    void* data = p->data;
    p->previous->next = p->next;
    if (p->next != NULL) {
        p->next->previous = p->previous;
    }
    free(p);

    return data;
}

void free_list(element *head) {
    while (head != NULL){
        element* next = head->next;
        free(head);
        head = next;
    }
}