#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "linklist.h"
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

int main(int argc, char *argv[])
{
	/* For generic type conversion */
	int elem_size = TYPE_SIZE;
	void (*get_elem)(void *) = TYPE_FUNC(get_rand_elem);
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	linklist list;

	printf("[linklist - Test 2/3] Condition Delete(equal to x):\n");

	linklist_init(&list);

	linklist_head_create(list, 10, elem_size, get_elem);
	linklist_traverse(list->next, show_elem);

	get_elem_x();

	/* 
	 * The condition of deletion can be arbitrary, 
	 *  such as elems are odd or elems are vowel.
	 **/
#if 0
	linklist_cond_delete_rec(&list->next, equal_to_x);
#else
	list->next = linklist_cond_delete_rec_ex(list->next, equal_to_x);
#endif

	linklist_traverse(list->next, show_elem);
	
	linklist_destroy(&list);

	return EXIT_SUCCESS;
}
