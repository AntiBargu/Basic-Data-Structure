#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "sqlist.h"
#include "generic_type.h"


static void *x;

void init_ptr(void **ptr, int size)
{
	if(!(*ptr = malloc(size)))
		exit(ENOMEM);
}

void get_elem_x(void)
{
	printf("Please insert x:\n");
	init_ptr(&x, TYPE_SIZE);
	TYPE_FUNC(get_stdin_elem)(x);
}

status equal_to_x(void *ptr)
{
	return TYPE_FUNC(equal)(ptr, x);
}

/* Condition delete, please refer to [sqlist - Test 3] */
int main(int argc, char *argv[])
{
	/* For generic type conversion */
	int elem_size = TYPE_SIZE;
	void (*get_elem)(void *) = TYPE_FUNC(get_rand_elem);
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	sq_list list;

	printf("[sqlist - Test 7] Condition Delete(equal to x) :\n");

	sqlist_init(&list, elem_size);

	sqlist_rand_create(&list, 10, elem_size, get_elem);
	sqlist_traverse(list, elem_size, show_elem);

	get_elem_x();

	/* 
	 * The condition of deletion can be arbitrary, 
	 *  such as elems are odd or elems are vowel.
	 **/
	sqlist_cond_delete(&list, elem_size, equal_to_x);
	sqlist_traverse(list, elem_size, show_elem);
	
	sqlist_destroy(&list);
	
	return EXIT_SUCCESS;

}
