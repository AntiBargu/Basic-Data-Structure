#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "linklist.h"
#include "generic_type.h"


int main(int argc, char *argv[])
{
	/* For generic type conversion */
	int elem_size = TYPE_SIZE;
	void (*get_elem)(void *) = TYPE_FUNC(get_rand_elem);
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	status (*compar_rule)(void *, void *) = TYPE_FUNC(less_than);

	linklist list, del_node;
	linklist *extrem;

	printf("[linklist - Test 1] Delete The Extremum of The Linklist:\n");

	linklist_init(&list);

	linklist_head_create(list, 10, elem_size, get_elem);
	linklist_traverse(list->next, show_elem);

	/* Find the extremum of @list. */
	if(!linklist_find_extremum(&list->next, &extrem, compar_rule)) {
		fprintf(stderr, "list is not exist!\n");
		exit(EINVAL);
	}

	printf("Extremum is ");
	show_elem((*extrem)->data);
	printf("\n");

	/* Release the extremum node. */
	del_node = *extrem;
	*extrem = del_node->next;

	free(del_node->data);
	free(del_node);

	linklist_traverse(list->next, show_elem);

	linklist_destroy(&list);
	
	return EXIT_SUCCESS;
}
