#include "common.h"


/*
 * Search in the sorted list @array.
 *
 * return value:
 * 	-OK	  	: @e is found, @pos is the position of @e
 * 	-ERROR	: @e is not found, @pos is the first position where it's
 * 				not satisfy @rules.
 */
status binary_search(void *array, int len, int size, void *e, int *pos,
			status (*rules)(void *, void *), 
			status (*equal)(void *,void *))
{
	int low = 0, high = len - 1, mid = -1;

	while(low <= high) {
		mid = (low + high) / 2;

		if(equal(array + mid * size, e)) {
			*pos = mid + 1;

			return OK;
		}
		
		if(rules(e, array + mid * size))
			high = mid - 1;
		else
			low = mid + 1;
	}

	*pos = low + 1;

	return ERROR;
}

/*
 * Search in the unsorted list @array.
 *
 * return value:
 * 	-OK	  	: @e is found, @pos is the position of @e
 * 	-ERROR	: @e is not found
 */
status seq_search(void *array, int len, int size, void *e, int *pos,
			status (*equal)(void *, void *))
{
	int i;

	for(i = 0; i < len; ++i) {
		if(equal(e, array + i * size)) {
			*pos = i + 1;

			return OK;
		}
	}

	return ERROR;
}
