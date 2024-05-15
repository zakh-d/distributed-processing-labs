#pragma once

typedef struct element element;

struct element
{
    element * previous ;
    void* data;
    element * next ;
};

element* insert(element *ptr, void* data, int (*comparator)(void*, void*));
void free_list(element *head);
void* remove_from_list(element * ptr, int index);
