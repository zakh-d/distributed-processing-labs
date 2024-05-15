#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "double_linked_list.h"


void show_menu() 
{
	char* MENU_TEXT = "a - Add element\nr - Remove element\ns - Show list\nq - Exit\n";
	printf("%s", MENU_TEXT);
}


int comparator(void* v1, void* v2) {
	char* s1 = (char*)v1;
	char* s2 = (char*)v2;
	return strcmp(s2, s1);
} 


void add_element(element* dummy)
{
	printf("Enter string: \n");
	char *buffer = NULL;
	size_t len;

	if (getline(&buffer, &len, stdin) != -1) {
	    /* insert buffer into list */
	    dummy->next = insert(dummy, buffer, comparator);
    }


}

void remove_element(element* dummy)
{
	printf("Enter index of string to remove: ");
	int index;
	scanf("%d", &index); 
	getchar(); /* consume new line character */

	/* remove element from list */
	char* data = (char*)remove_from_list(dummy, index);


	if (data != NULL) {
		/* releasing memory taken by string */
		printf("Removed: %s\n", data);
		free(data);
	}
	else {
		printf("Invalid index\n");
	}
}

void show_list(element* dummy)
{
	/* print list */
	int i = 0;
	for (element* ptr = dummy->next; ptr != NULL; ptr = ptr->next) {
		printf("%d: %s\n", i, (char*)ptr->data);
		i++;
	}
}


int main(int argc, char **argv) 
{

	int running = 1;

	element* dummy = (element* )malloc(sizeof(element));
	dummy->next = NULL;
	dummy->data = NULL;
	dummy->previous = NULL;

	while (running) {
		/* read line from console*/
		show_menu();
		char option;
		scanf("%c", &option);
		getchar(); /* consume newline */
		switch (option) {
			case 'a':
				add_element(dummy);
				break;
			case 'r':
				remove_element(dummy);
				break;
			case 's':
				show_list(dummy);
				break;
			case 'q':
				running = 0;
				break;
			default:
				printf("Invalid option\n");
		}
	}

	/* TODO: free memory*/

	for (element* ptr = dummy->next; ptr != NULL; ptr = ptr->next) {
		/* free memory taken by strings */
		if (ptr->data != NULL)
		{
			free(ptr->data);
		}
	}

	free_list(dummy);

	return 0;
}
