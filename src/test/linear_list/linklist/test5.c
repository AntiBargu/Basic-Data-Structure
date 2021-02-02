#include <stdio.h>
#include <stdlib.h>

#include "linklist.h"
#include "generic_type.h"


int main(int argc, char *argv[])
{
	/* For generic type conversion */
	int elem_size = TYPE_SIZE;
	void (*get_elem)(void *) = TYPE_FUNC(get_rand_elem);
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	linklist list;

	printf("[linklist - Test 5] Reverse Print List:\n");

	linklist_init(&list);

	linklist_head_create(list, 10, elem_size, get_elem);
	linklist_traverse(list->next, show_elem);

	linklist_reverse_traverse(list->next, show_elem);
	printf("\n");

	linklist_destroy(&list);
	
	return EXIT_SUCCESS;
}
