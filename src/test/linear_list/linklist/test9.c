#include <stdio.h>
#include <stdlib.h>

#include "linklist.h"
#include "generic_type.h"


/*
 * These functions are support "None-Head Linklist", 
 * 	@list_a and @list_b are the first element's address in the memory.
 **/
void get_intersection(linklist *list_a, linklist *list_b, 
			status (*compare)(void *, void *),
			status (*equal)(void *, void *))
{
	linklist del_node;
	linklist **min_ptr;
	linklist *p = list_a, *q = list_b;

	while(*p && *q) {
		if(equal((*p)->data, (*q)->data)) {
			p = &(*p)->next;
			q = &(*q)->next;
		}
		else {
			min_ptr = compare((*p)->data, (*q)->data) ? &p : &q;

			del_node = **min_ptr;
			**min_ptr = del_node->next;

			free(del_node->data);
			free(del_node);
		}
	}

	min_ptr = *p ? &p : &q;
	linklist_destroy(*min_ptr);
}

int main(int argc, char *argv[])
{
	/* For generic type conversion */
	int elem_size = TYPE_SIZE;
	void (*get_elem)(void *) = TYPE_FUNC(get_rand_elem);
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	status (*compar_rule)(void *, void *) = TYPE_FUNC(less_than);
	status (*equal)(void *, void *) = TYPE_FUNC(equal);

	linklist list_a, list_b;

	printf("[linklist - Test 9] Get Sorted Linklists' Intersection:\n");

	linklist_init(&list_a);
	linklist_init(&list_b);

	linklist_head_create(list_a, 10, elem_size, get_elem);
	linklist_sort(&list_a->next, compar_rule);
	linklist_delete_repeat(&list_a->next, equal);
 
	printf("list_a :\n");
	linklist_traverse(list_a->next, show_elem);

	linklist_head_create(list_b, 10, elem_size, get_elem);
	linklist_sort(&list_b->next, compar_rule);
	linklist_delete_repeat(&list_b->next, equal);

	printf("list_b :\n");
	linklist_traverse(list_b->next, show_elem);

	get_intersection(&list_a->next, &list_b->next, compar_rule, equal);
	printf("The intersection:\n");
	linklist_traverse(list_a->next, show_elem);

	linklist_destroy(&list_a);
	linklist_destroy(&list_b);
	
	return EXIT_SUCCESS;
}
