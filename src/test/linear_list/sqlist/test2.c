#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sqlist.h"
#include "generic_type.h"


void delete_max(sq_list *list, int size)
{
	int num;

	sqlist_get_extremum(*list, size, TYPE_FUNC(more_than), &num);
	
	printf("The extremum of this list is ");
	TYPE_FUNC(show_elem)(list->elem + (num - 1) * size);
	printf("\n");
	
	memcpy(list->elem + (num - 1) * size, 
			list->elem + (list->usage - 1) * size, size);

	--list->usage;
}

int main(int argc, char *argv[])
{
	/* For generic type conversion */
	int elem_size = TYPE_SIZE;
	void (*get_elem)(void *) = TYPE_FUNC(get_rand_elem);
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	sq_list list;

	printf("[sqlist - Test 2] Delete Extremum Element:\n");

	sqlist_init(&list, elem_size);

	sqlist_rand_create(&list, 10, elem_size, get_elem);
	sqlist_traverse(list, elem_size, show_elem);

	delete_max(&list, elem_size);
	sqlist_traverse(list, elem_size, show_elem);
	
	sqlist_destroy(&list);
	
	return EXIT_SUCCESS;
}
