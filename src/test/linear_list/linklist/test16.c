#include <stdio.h>
#include <stdlib.h>

#include "clinklist.h"
#include "generic_type.h"


void clinklist_order_print(clinklist *list, 
			status (*compare)(void *, void *),
			void (*show_elem)(void *))
{
	clinklist del_node;
	clinklist *extrem;

	while(clinklist_find_extremum(&(*list)->next, &extrem, compare)) { 
		show_elem((*extrem)->data);

		del_node = *extrem;
		*extrem = del_node->next;

		free(del_node->data);
		free(del_node);
	}

	printf("\n");
}

int main(int argc, char *argv[])
{
	/* For generic type conversion */
	int elem_size = TYPE_SIZE;
	void (*get_elem)(void *) = TYPE_FUNC(get_rand_elem);
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	status (*compar_rule)(void *, void *) = TYPE_FUNC(more_than);

	clinklist list;

	printf("[linklist - Test 16] Circular Linklist Order Print :\n");

	clinklist_init(&list);

	clinklist_head_create(list, 10, elem_size, get_elem);
	clinklist_traverse(list, show_elem);

	clinklist_order_print(&list, compar_rule, show_elem);

	clinklist_destroy(&list);
	
	return EXIT_SUCCESS;
}
