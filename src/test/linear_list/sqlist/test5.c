#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sqlist.h"
#include "generic_type.h"

#include "sort.h"


int main(int argc, char *argv[])
{
	/* For generic type conversion */
	int elem_size = TYPE_SIZE;
	void (*get_elem)(void *) = TYPE_FUNC(get_rand_elem);
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	status(*sort_rule)(void *, void *) = TYPE_FUNC(less_than);

	sq_list list_a, list_b, list_c;

	printf("[sqlist - Test 5] Merge Sorted List:\n");

	sqlist_init(&list_a, elem_size);
	sqlist_init(&list_b, elem_size);

	/* Create sorted lists */
	printf("list a:\n");
	sqlist_rand_create(&list_a, 10, elem_size, get_elem);
	bubble_sort(list_a.elem, list_a.usage, elem_size, sort_rule);
	sqlist_traverse(list_a, elem_size, show_elem);

	printf("list b:\n");
	sqlist_rand_create(&list_b, 10, elem_size, get_elem);
	bubble_sort(list_b.elem, list_b.usage, elem_size, sort_rule);
	sqlist_traverse(list_b, elem_size, show_elem);

	sqlist_merge(list_a, list_b, &list_c, elem_size, sort_rule);

	printf("list c after merge:\n");
	sqlist_traverse(list_c, elem_size, show_elem);
	
	sqlist_destroy(&list_a);
	sqlist_destroy(&list_b);
	sqlist_destroy(&list_c);

	return EXIT_SUCCESS;
}
