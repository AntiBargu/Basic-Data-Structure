#include <stdio.h>
#include <stdlib.h>

#include "sqlist.h"
#include "generic_type.h"


int main(int argc, char *argv[])
{
	/* For generic type conversion */
	int elem_size = TYPE_SIZE;
	void (*get_elem)(void *) = TYPE_FUNC(get_rand_elem);
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	sq_list list;

	printf("[sqlist - Test 1] Reverse List:\n");

	sqlist_init(&list, elem_size);

	sqlist_rand_create(&list, 10, elem_size, get_elem);
	sqlist_traverse(list, elem_size, show_elem);
	
	sqlist_reverse(&list, elem_size);
	sqlist_traverse(list, elem_size, show_elem);

	sqlist_destroy(&list);

	return EXIT_SUCCESS;
}
