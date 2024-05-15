#include <stdio.h>
#include <stdlib.h>

void bad_fn()
{
    int* arr = (int*) malloc(10 * sizeof(int));
    arr[10] = 0;
}

int main() 
{

    bad_fn();
    return 0;
}
