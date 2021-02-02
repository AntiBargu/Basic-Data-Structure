#include <stdio.h>
#include <stdlib.h>

#include "linklist.h"
#include "generic_type.h"

/*
 * These functions are support "None-Head Linklist", 
 * 	@list_a and @list_b are the first element's address in the memory.
 * Reverse merge @list_a and @list_b into @list_a. 
 **/
void linklist_reverse_merge(linklist *list_a, linklist *list_b, 
			status (*compare)(void *, void *))
{
	linklist *ptr;
	linklist p = *list_a, q = *list_b, mov_node;

	*list_a = NULL;
	*list_b = NULL;

	while(p && q) {
		ptr = compare(p->data, q->data) ? &p : &q;
	
		mov_node = *ptr;
		*ptr = (*ptr)->next;

		mov_node->next = *list_a;
		*list_a = mov_node;
	}

	/* Merge the remainers into @list_a. */	
	ptr = p ? &p : &q;

	while(*ptr) {
		mov_node = *ptr;
		*ptr = (*ptr)->next;
	
		mov_node->next = *list_a;
		*list_a = mov_node;
	}
}

int main(int argc, char *argv[])
{
	/* For generic type conversion */
	int elem_size = TYPE_SIZE;
	void (*get_elem)(void *) = TYPE_FUNC(get_rand_elem);
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	status (*compar_rule)(void *, void *) = TYPE_FUNC(less_than);

	linklist list_a, list_b;

	printf("[linklist - Test 13] Reverse Merge The Sorted Linklists:\n");

	linklist_init(&list_a);
	linklist_init(&list_b);

	linklist_head_create(list_a, 10, elem_size, get_elem);
	linklist_sort(&list_a->next, compar_rule);
	
	printf("list_a :\n");
	linklist_traverse(list_a->next, show_elem);

	linklist_head_create(list_b, 10, elem_size, get_elem);
	linklist_sort(&list_b->next, compar_rule);

	printf("list_b :\n");
	linklist_traverse(list_b->next, show_elem);

	linklist_reverse_merge(&list_a->next, &list_b->next, compar_rule);
	printf("list after merge :\n");
	linklist_traverse(list_a->next, show_elem);

	linklist_destroy(&list_a);
	linklist_destroy(&list_b);
	
	return EXIT_SUCCESS;
}
