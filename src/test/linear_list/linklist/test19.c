#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "linklist.h"
#include "generic_type.h"


status linklist_the_last_kth(linklist list, int k, void **ptr)
{
	int i;
	linklist fronter, follower;

	if(k <= 0)
		return ERROR;

	for(i = 0, fronter = list; i < k && fronter; ++i, fronter = fronter->next)
		;

	/* When the length of @list is less than k, the last kth is not exist. */
	if(i < k)
		return ERROR;

	for(follower = list; fronter; follower = follower->next,
			fronter = fronter->next)
		;

	*ptr = follower->data;
	
	return OK;
}

int main(int argc, char *argv[])
{
	/* For generic type conversion */
	int elem_size = TYPE_SIZE;
	void (*get_elem)(void *) = TYPE_FUNC(get_rand_elem);
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	int k;
	void *last_kth;
	linklist list;

	printf("[linklist - Test 19] The Last kth Element Of The Linklist:\n");

	linklist_init(&list);

	linklist_head_create(list, 10, elem_size, get_elem);
	linklist_traverse(list->next, show_elem);

	printf("Please insert k:\n");
	scanf("%d", &k);

	if(linklist_the_last_kth(list->next, k, &last_kth)) {
		printf("The last kth element of the list is found: ");
		show_elem(last_kth);
		printf("\n");
	}
	else
		printf("The last kth element of the list is not found.\n");

	linklist_destroy(&list);
	
	return EXIT_SUCCESS;
}
