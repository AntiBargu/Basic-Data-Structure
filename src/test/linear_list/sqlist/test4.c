#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "sqlist.h"
#include "generic_type.h"

#include "sort.h"
#include "search.h"


void init_ptr(void **ptr, int size)
{
	if(!(*ptr = malloc(size)))
		exit(ENOMEM);
}

int main(int argc, char *argv[])
{
	/* For generic type conversion */
	int elem_size = TYPE_SIZE;
	void (*get_elem)(void *) = TYPE_FUNC(get_rand_elem);
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);
	void (*scan_elem)(void *) = TYPE_FUNC(get_stdin_elem);

	status(*equal)(void *, void *) = TYPE_FUNC(equal);
	status(*sort_rule)(void *, void *) = TYPE_FUNC(less_than);

	sq_list list;
	void *s, *t;
	int pos_s, pos_t;

	printf("[sqlist - Test 4] Sorted List Delete Elements(between s to t):\n");
	
	sqlist_init(&list, elem_size);

	/* Create a sorted list. */
	sqlist_rand_create(&list, 10, elem_size, get_elem);
	bubble_sort(list.elem, list.usage, elem_size, sort_rule);
	sqlist_traverse(list, elem_size, show_elem);

	/* Get @s and @t. */	
	init_ptr(&s, elem_size);
	scan_elem(s);

	init_ptr(&t, elem_size);
	scan_elem(t);

	/* 
 	 * Get the position of @s and @t.
 	 * If @s or @t are not found in @list, @binary_search return FALSE,
 	 * 	and @pos will be the next position of @s or @t in the @list.
 	 **/
	binary_search(list.elem, list.usage, elem_size, s, &pos_s, 
		sort_rule, equal);

	/* Refer to the notes above. */
	if(binary_search(list.elem, list.usage, elem_size, t, &pos_t, 
		sort_rule, equal))
		++pos_t;

	if(sqlist_block_delete(&list, pos_s, pos_t, elem_size))
		sqlist_traverse(list, elem_size, show_elem);
	else
		printf("Argument Error\n");
	
	sqlist_destroy(&list);
	
	return EXIT_SUCCESS;
}
