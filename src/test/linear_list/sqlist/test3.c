#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "sqlist.h"
#include "generic_type.h"


static void *s, *t;

void init_ptr(void **ptr, int size)
{
	if(!(*ptr = malloc(size)))
		exit(ENOMEM);
}

void get_s_and_t(void)
{
	printf("Please insert s:\n");
	init_ptr(&s, TYPE_SIZE);
	TYPE_FUNC(get_stdin_elem)(s);

	printf("Please insert t:\n");
	init_ptr(&t, TYPE_SIZE);
	TYPE_FUNC(get_stdin_elem)(t);
}

status between_and(void *ptr)
{
	return TYPE_FUNC(more_than)(ptr, s) && 
				TYPE_FUNC(less_than)(ptr, t);
}

/* Condition delete, please refer to [sqlist - Test 7] */
int main(int argc, char *argv[])
{
	/* For generic type conversion */
	int elem_size = TYPE_SIZE;
	void (*get_elem)(void *) = TYPE_FUNC(get_rand_elem);
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	sq_list list;

	printf("[sqlist - Test 3] Condition Delete(Between s and t)\n");

	sqlist_init(&list, elem_size);

	sqlist_rand_create(&list, 10, elem_size, get_elem);
	sqlist_traverse(list, elem_size, show_elem);
	
	get_s_and_t();

	/* 
	 * The condition of deletion can be arbitrary, 
	 *  such as elems are odd or elems are vowel.
	 **/
	sqlist_cond_delete(&list, elem_size, between_and);
	sqlist_traverse(list, elem_size, show_elem);
	
	sqlist_destroy(&list);
	
	return EXIT_SUCCESS;
}
