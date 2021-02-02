#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "exchange.h"

/*
 * Create an inverted top heap.
 *
 * @heap 	: Inverted top heap.
 * @parent 	: The number of parent of the heap.
 * @rules 	: Compare rules which is TRUE while it's correct order. 
 * @child	: The number of child of the heap.
 *
 * Note:
 * @parent and @child is number not index, index = number - 1.
 * Compare and move in real memory.
 *
 */
void percdown(void *heap, int parent, int cnts, int size,
				int (*rules)(void *, void *))
{
	int child;
	void *tmp;

	if(!(tmp = malloc(size)))
		exit(ENOMEM);
	
	memcpy(tmp, heap + (parent - 1) * size, size);

	for(child = parent * 2; child <= cnts; child *= 2) {
		if(child < cnts && 
				rules(heap + (child - 1) * size, heap + child * size))
			++child;
		
		if(!rules(tmp, heap + (child - 1) * size))
			break;
		
		memcpy(heap + (parent - 1) * size, 
				heap + (child - 1) * size, size);

		parent = child;
	}
	
	memcpy(heap + (parent - 1) * size, tmp, size);

	free(tmp);
}

void heap_sort(void *heap, int len, int size,
				int (*rules)(void *, void *))
{
	int parent;

	for(parent = len / 2; parent > 0; --parent)
		percdown(heap, parent, len, size, rules);

	for(parent = len; parent > 0; --parent) {
		exchange(heap, heap + (parent - 1) * size, size);
		percdown(heap, 1, parent - 1, size, rules);
	}
}
