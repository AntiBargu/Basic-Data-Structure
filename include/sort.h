#ifndef _SORT_H
#define _SORT_H

extern void bubble_sort(void *seq, int len, int size,
			int	(*rules)(void *, void *));

extern void bubble_sort_ex(void *seq, int len, int size,
			int (*rules)(void *, void *));

extern void heap_sort(void *heap, int len, int size,
			int (*rules)(void *, void *));

extern void quick_sort(void *heap, int len, int size,
			int (*rules)(void *, void *));

#endif /* _SORT_H */
