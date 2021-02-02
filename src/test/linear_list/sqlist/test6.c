#include <stdio.h>
#include <stdlib.h>

#include "sqlist.h"
#include "generic_type.h"

#include "sort.h"


int main(int argc, char *argv[])
{
	/* For generic type conversion */
	int elem_size = TYPE_SIZE;
	void (*get_elem)(void *) = TYPE_FUNC(get_rand_elem);
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	status(*equal)(void *, void *) = TYPE_FUNC(equal);
	status(*sort_rule)(void *, void *) = TYPE_FUNC(less_than);

	sq_list list;

	printf("[sqlist - Test 6] Delete Repeating Elements:\n");

	sqlist_init(&list, elem_size);

	sqlist_rand_create(&list, 10, elem_size, get_elem);
	bubble_sort(list.elem, list.usage, elem_size, sort_rule);
	sqlist_traverse(list, elem_size, show_elem);
		
	sqlist_delete_repeat(&list, elem_size, equal);
	sqlist_traverse(list, elem_size, show_elem);
	
	sqlist_destroy(&list);
	
	return EXIT_SUCCESS;

}
