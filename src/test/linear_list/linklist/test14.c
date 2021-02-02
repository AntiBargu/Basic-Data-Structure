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

	status (*compar_rule)(void *, void *) = TYPE_FUNC(less_than);
	status (*equal)(void *, void *) = TYPE_FUNC(equal);

	linklist list;

	printf("[linklist - Test 14] Linklist Delete Repeating Elements:\n");

	linklist_init(&list);

	linklist_head_create(list, 10, elem_size, get_elem);
	linklist_sort(&list->next, compar_rule);
	linklist_traverse(list->next, show_elem);

	linklist_delete_repeat(&list->next, equal);
	linklist_traverse(list->next, show_elem);

	linklist_destroy(&list);
	
	return EXIT_SUCCESS;
}
