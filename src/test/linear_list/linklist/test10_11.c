#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "linklist.h"
#include "generic_type.h"


/* 
 * Separate the @list into @n parts @list_array, 
 *  and each lists' order are the reverse order of the original order.
 **/
status separate_list(linklist list, int n, linklist **list_array)
{
	linklist p, cur_node;
	int i;

	if(n <= 0 || !list)
		return ERROR;
	
	if(!(*list_array = malloc(sizeof(linklist) * n)))
		exit(OVERFLOW);
	
	for(i = 0; i < n; ++i) {
		if(!((*list_array)[i] = malloc(sizeof(lnode))))
			exit(OVERFLOW);
		
		(*list_array)[i]->next = NULL;
	}

	for(i = 0, p = list->next; p;  i = (i + 1) % n) {
		cur_node = p;
		p = p->next;

		/* 
		 * Head-Insert Method create list @(*list_array)[i], 
		 * 	they are the reverse order of the original order.
		 **/
		cur_node->next = (*list_array)[i]->next;
		(*list_array)[i]->next = cur_node;
	}
	
	return OK;
}

int main(int argc, char *argv[])
{
	/* For generic type conversion */
	int elem_size = TYPE_SIZE;
	void (*get_elem)(void *) = TYPE_FUNC(get_rand_elem);
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	int i, n;
	linklist list, *list_array;

	printf("[linklist - Test 10/11] Separate Linklist in N Parts:\n");

	linklist_init(&list);

	linklist_head_create(list, 10, elem_size, get_elem);
	linklist_traverse(list->next, show_elem);

	printf("Please Insert N:\n");
	scanf("%d", &n);

	if(!separate_list(list, n, &list_array)) {
		printf("Separate Failed.\n");
		exit(EINVAL);
	}

	for(i = 0; i < n; ++i) {
		linklist_traverse(list_array[i]->next, show_elem);
		linklist_destroy(&list_array[i]);
	}
	
	return EXIT_SUCCESS;
}
