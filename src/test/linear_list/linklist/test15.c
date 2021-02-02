#include <stdio.h>
#include <stdlib.h>

#include "linklist.h"
#include "generic_type.h"


int main(int argc, char *argv[])
{
	/* For generic type conversion */
	int elem_size = TYPE_SIZE;
	void (*get_elem)(void *) = TYPE_FUNC(get_rand_elem);
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	status (*equal)(void *, void *) = TYPE_FUNC(equal);

	linklist list_a, list_b;	

	printf("[linklist - Test 15] Judge Sub Linklist:\n");

	linklist_init(&list_a);
	linklist_init(&list_b);

	linklist_head_create(list_a, 10, elem_size, get_elem);

	printf("list_a :\n");
	linklist_traverse(list_a->next, show_elem);

	/* Create @list_b from stdin, and it's lenghth is 3. */
	printf("Please input the list_b :\n");
	linklist_tail_create(list_b, 3, elem_size, TYPE_FUNC(get_stdin_elem));

	printf("list_b :\n");
	linklist_traverse(list_b->next, show_elem);
	
	printf("list_b %s list_a's sub sequence.\n",  
			linklist_subseq(list_a->next, list_b->next, equal) ? 
			"is": "isn't");

	linklist_destroy(&list_a);
	linklist_destroy(&list_b);
	
	return EXIT_SUCCESS;
}
