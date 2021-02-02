#include <stdio.h>
#include <stdlib.h>

#include "linklist.h"
#include "generic_type.h"


void linklist_seq_print(linklist *list, 
			status (*compare)(void *, void *))
{
	linklist del_node;
	linklist *min_pos;

	while(linklist_find_extremum(&(*list)->next, &min_pos, compare)) { 
		/* Show Delete Elements. */
		printf("The deleted element is ");
		TYPE_FUNC(show_elem)((*min_pos)->data);
		printf("\n");

		del_node = *min_pos;
		*min_pos = del_node->next;
		
		free(del_node->data);
		free(del_node);
	}
}

int main(int argc, char *argv[])
{
	/* For generic type conversion */
	int elem_size = TYPE_SIZE;
	void (*get_elem)(void *) = TYPE_FUNC(get_rand_elem);
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	status (*compar_rule)(void *, void *) = TYPE_FUNC(less_than);

	linklist list;

	printf("[linklist - Test 8] Linklist Sequence Print:\n");

	linklist_init(&list);

	linklist_head_create(list, 10, elem_size, get_elem);
	linklist_traverse(list->next, show_elem);

	linklist_seq_print(&list, compar_rule);

	linklist_destroy(&list);
	
	return EXIT_SUCCESS;
}
