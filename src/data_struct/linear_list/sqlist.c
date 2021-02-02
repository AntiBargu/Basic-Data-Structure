#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exchange.h"
#include "sqlist.h"

#if 0
void exchange(void *a, void *b, int size)
{
	char tmp;
	
	while(size--) {
		tmp = *(char *)a;
		*(char *)a = *(char *)b;
		*(char *)b = tmp;

		++a;
		++b;
	}
}
#endif

/*
 * sqlist_init : Init a sequence list
 *
 * @list : The sequence list to be initized.
 *
 * Return value:
 *	- OVERFLOW : Not enough memory.
 *	- OK	   : Init successed.
 *
 * */
status sqlist_init(sq_list *list, int size)
{
	if(NULL == (list->elem = (void *)malloc(size * LIST_INIT_SIZE)))
		return OVERFLOW;

	list->usage = 0;
	list->size = LIST_INIT_SIZE;

	return OK;
}

status sqlist_destroy(sq_list *list)
{
	if(!list->elem)
		return ERROR;

	free(list->elem);
	list->elem = NULL;

	list->usage = 0;
	list->size = 0;
	
	return OK;
}

status sqlist_clear(sq_list *list)
{
	if(!list->elem)
		return ERROR;
	
	list->usage = 0;

	return OK;
}

status sqlist_empty(sq_list list)
{
	return 0 == list.usage;
}

int sqlist_length(sq_list list)
{
	return list.usage;
}

status sqlist_get_elem(sq_list list, int i, int size, void **e)
{
	if(i <= 0 || i > list.usage)
		return ERROR;

	*e = list.elem + (i - 1) * size;
	
	return OK;
}

/* Return the number of @e in the @list. */
int sqlist_local_elem(sq_list list, int size, void *e, 
			int (*compare)(void *, void *))
{
	int pos;
	
	for(pos = 0; pos < list.usage; ++pos) {
		if(compare(e, list.elem + pos * size))
			break;	
	}

	return pos == list.usage ? 0 : pos + 1;
}

status sqlist_prior_elem(sq_list list, int size, void *cur_e,
			void **e, int (*compare)(void *, void *))
{
	int i;
	
	i = sqlist_local_elem(list, size, cur_e, compare);
	
	if(i <= 1)
		return ERROR;
	
	*e = list.elem + (i - 2) * size;

	return OK;
}

status sqlist_next_elem(sq_list list, int size, void *cur_e,
			void **e, int (*compare)(void *, void *))
{	
	int i;
	
	i = sqlist_local_elem(list, size, cur_e, compare);
	
	if(i == 0 || i == list.usage)
		return ERROR;
	
	*e = list.elem + i * size;

	return OK;
}

/* @e is the memory address of the inserted element. */
status sqlist_insert(sq_list *list, int i, int size, void *e)
{
	int j;

	if(i < 1 || i > list->usage + 1)
		return ERROR;

	for(j = list->usage; j >= i; --j)
		memcpy(list->elem + j * size,
			list->elem + (j - 1) * size, size);

	memcpy(list->elem + j * size, e, size);
	++list->usage;

	return OK;
}

status sqlist_delete(sq_list *list, int i, int size, void **e)
{
	int j;

	if(i < 1 || i > list->usage)
		return ERROR;

	if(!(*e = malloc(size)))
		return OVERFLOW;
	
	memcpy(*e, list->elem + (i - 1) * size, size);

	for(j = i; j <= list->usage; ++j)
		memcpy(list->elem + (j - 1) * size,
			list->elem + j * size, size);

	--list->usage;

	return OK;
}

status sqlist_traverse(sq_list list, int size, void (*visit)(void *))
{
	int i;
	
	if(!list.elem)
		return ERROR;

	for(i = 0; i < list.usage; ++i)
		visit(list.elem + i * size);

	printf("\n");

	return OK;
}

/* Following functions are added for subjects. */
void sqlist_reverse(sq_list *list, int size)
{
	int head = 0, tail = list->usage - 1;

	for( ; head < tail; ++head, --tail)
		exchange(list->elem + head * size, 
					list->elem + tail *size, size);

}

status sqlist_get_extremum(sq_list list, int size,
			status (*compare)(void *, void *), int *pos)
{
	int i;

	if(list.usage <= 0)
		return ERROR;

	*pos = 1;
	
	for(i = 1; i <= list.usage; ++i) {
		if(compare(list.elem + (i - 1) * size, 
				list.elem + (*pos - 1) * size))
			*pos = i;
	}

	return OK;
}

/* Delete all the elements of @list which @cond(elems) is TRUE. */
status sqlist_cond_delete(sq_list *list, int size,
				status (*cond)(void *))
{
	int i, cnts = 0;

	if(list->usage <= 0)
		return ERROR;

	for(i = 0; i < list->usage; ++i) {
		if(cond(list->elem + i * size)) {
			++cnts;
			continue;
		}

		memcpy(list->elem + (i - cnts) * size,
			list->elem + i * size, size);
	}

	list->usage -= cnts;

	return OK;
}

/* Delete elements of @list from @mth to @nth. */
status sqlist_block_delete(sq_list *list, int m, int n, int size)
{
	if(m > n)
		return ERROR;
	
	for(; n <= list->usage; ++n, ++m)
		memcpy(list->elem + (m - 1) * size, 
				list->elem + (n - 1) * size, size);
	
	list->usage -= n - m;

	return OK;
}

/* Merge two sorted list @list_a and @list_b into a sorted list @list_c. */
void sqlist_merge(sq_list list_a, sq_list list_b, sq_list *list_c,
				int size, status (*rules)(void *, void *))
{
	void *pa, *pb, *pa_last, *pb_last, *pc;

	list_c->usage = list_c->size = list_a.usage + list_b.usage;

	if(NULL == (list_c->elem = malloc(list_c->size * sizeof(void *))))
		exit(OVERFLOW);

	pc = list_c->elem;
	
	pa = list_a.elem;
	pb = list_b.elem;

	pa_last = list_a.elem + (list_a.usage - 1) * size;
	pb_last = list_b.elem + (list_b.usage - 1) * size;

	while(pa <= pa_last &&  pb <= pb_last) {
		if(rules(pa, pb)) {
			memcpy(pc, pa, size);
			pa += size;
		}
		else {
			memcpy(pc, pb, size);
			pb += size;
		}

		pc += size;
	}

	if(pa <= pa_last)
		memcpy(pc, pa, pa_last - pa + size);
	
	if(pb <= pb_last)
		memcpy(pc, pb, pb_last - pb + size);

}

/* Delete all repeating elements of sorted list @list. */
void sqlist_delete_repeat(sq_list *list, int size,
				status (*equal)(void *, void *))
{
	int i, cnts = 0;

	for(i = 1; i < list->usage; ++i) {
		if(equal(list->elem + (i - 1) * size,
				list->elem + i * size)) {
			++cnts;
			continue;
		}
		
		memcpy(list->elem + (i - cnts) * size,
			list->elem + i * size, size);
	}
	
	list->usage -= cnts;

}

/* Create a sqlist for tests. */
status sqlist_rand_create(sq_list *list, int len, int size,
				void (*get_elem)(void *))
{
	int i;

	if(len > list->size)
		return ERROR;

	for(i = 0; i < len; ++i)
		get_elem(list->elem + i * size);

	list->usage = len;

	return OK;
}
