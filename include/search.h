#ifndef _SEARCH_H
#define _SEARCH_H

/* Search in the sorted list @array. */
extern status binary_search(void *array, int len, int size, void *e, 
			int *pos, status (*rules)(void *, void *), 
			status (*equal)(void *,void *));

/* Search in the unsorted list @array. */
extern status seq_search(void *array, int len, int size, void *e, 
			int *pos, status (*equal)(void *, void *));

#endif	/* _SEARCH_H */
