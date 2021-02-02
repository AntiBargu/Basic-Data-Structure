#include <stdio.h>
#include <stdlib.h>

#include "sqlist.h"
#include "generic_type.h"

#include "exchange.h"


void reverse_list(void *array, int p, int size)
{
	int i;
	
	for(i = 0; i < p / 2; ++i)
		exchange(array + i * size, array + (p - i - 1) * size, size);
}

int main(int argc, char *argv[])
{
	/* For generic type conversion */
	int elem_size = TYPE_SIZE;
	void (*get_elem)(void *) = TYPE_FUNC(get_rand_elem);
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	int p;
	sq_list list;

	printf("[sqlist - Test 8] Loop Left Shift:\n");

	sqlist_init(&list, elem_size);

	sqlist_rand_create(&list, 10, elem_size, get_elem);
	sqlist_traverse(list, elem_size, show_elem);

	printf("please insert p:\n");
	scanf("%d", &p);

	p %= list.usage;
	
	reverse_list(list.elem, p, elem_size);
	reverse_list(list.elem + p * elem_size, list.usage - p, elem_size);
	reverse_list(list.elem, list.usage, elem_size);
	
	sqlist_traverse(list, elem_size, show_elem);

	sqlist_destroy(&list);
	
	return EXIT_SUCCESS;
}
