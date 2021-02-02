#include <stdio.h>
#include <stdlib.h>

#include "duclinklist.h"
#include "generic_type.h"

status duclinklist_is_Palinder(duclinklist list, 
			status (*equal)(void *, void *))
{
	duclinklist head, tail;

	for(head = list->next, tail = list->prev; 
			head != tail && tail->next != head;
			head = head->next, tail = tail->prev)	{
		if(equal(head->data, tail->data))
			return ERROR;
	}

	return OK;
}

int main(int argc, char *argv[])
{
	/* For generic type conversion */
	int elem_size = TYPE_SIZE;
	void (*get_elem)(void *) = TYPE_FUNC(get_stdin_elem);
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	status (*equal)(void *, void *) = TYPE_FUNC(equal);

	int len;
	duclinklist list;

	printf("[linklist - Test 17] Double-Circular-Linklist Balanced :\n");

	duclinklist_init(&list);

	printf("Please insert the length of Linklist :\n");
	scanf("%d", &len);

	printf("Please insert the info of Linklist :\n");
	duclinklist_tail_create(list, len, elem_size, get_elem);
	duclinklist_traverse(list, show_elem);
	
	printf("This %s a balanced Double-Circular-Linklist.\n",
			 duclinklist_is_Palinder(list, equal) ? "is" : "isn't");
	
	duclinklist_destroy(&list);

	return EXIT_SUCCESS;
}
