#include <stdio.h>
#include <stdlib.h>

#include "linklist.h"
#include "generic_type.h"


status linklist_common_node(linklist list_a, linklist list_b,
			linklist *list_com)
{	
	int len_a, len_b, sub;
	linklist longer, shorter;

	if(!list_a || !list_b)
		return ERROR;

	len_a = linklist_length(list_a);
	len_b = linklist_length(list_b);

	longer = len_a > len_b ? list_a : list_b;
	shorter = longer == list_a ? list_b : list_a;

	for(sub = abs(len_a - len_b); sub > 0; --sub)
		longer = longer->next;

	while(longer && longer != shorter) {
		longer = longer->next;
		shorter = shorter->next;
	}

	*list_com = longer;
	
	return OK;
}

int main(int argc, char *argv[])
{
	/* For generic type conversion */
	int elem_size = TYPE_SIZE;
	void (*get_elem)(void *) = TYPE_FUNC(get_rand_elem);
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	linklist list_a, list_b, list_com, rslt;

	printf("[linklist - Test 7] Get Common List:\n");

	/* Create two lists which have common list. */
	linklist_init(&list_a);
	linklist_init(&list_b);
	linklist_init(&list_com);

	linklist_head_create(list_a, 10, elem_size, get_elem);
	linklist_head_create(list_b, 10, elem_size, get_elem);
	linklist_head_create(list_com, 10, elem_size, get_elem);

	linklist_append(list_a, list_com);
	linklist_append(list_b, list_com);

	
	linklist_traverse(list_a->next, show_elem);
	linklist_traverse(list_b->next, show_elem);
	
	linklist_init(&rslt);
	linklist_common_node(list_a, list_b, &rslt->next);

	printf("The common list is :\n");
	linklist_traverse(rslt->next, show_elem);

	/* t.b.d: double free. */
	free(rslt);
	linklist_destroy(&list_com);
/*
	linklist_destroy(&list_a);
	linklist_destroy(&list_b);
*/	
	return EXIT_SUCCESS;
}
