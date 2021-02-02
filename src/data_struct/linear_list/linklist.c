#include <stdio.h>
#include <stdlib.h>

#include "linklist.h"


status linklist_init(linklist *list)
{
	if(!(*list = malloc(sizeof(lnode))))
		return OVERFLOW;

	(*list)->next = NULL;

	return OK;
}

status linklist_destroy(linklist *list)
{
	if(!linklist_clear(*list))
		return ERROR;

	free(*list);
	*list = NULL;

	return OK;
}

status linklist_clear(linklist list)
{
	linklist p, del_node;

	if(!list)
		return ERROR;

	for(p = list->next; p; p = p->next, free(del_node->data), free(del_node))
		del_node = p;
	
	list->next = NULL;

	return OK;
}

status linklist_empty(linklist list)
{
	return NULL == list->next; 
}

int linklist_length(linklist list)
{
	int len = 0;
	linklist p;

	for(p = list->next; p; p = p->next)
		++len;

	return len;
}

status linklist_get_elem(linklist list, int n, void **e)
{
	int i;
	linklist p;

	if(!list)
		return ERROR;

	for(i = 1, p = list->next; i < n && p; ++i, p = p->next)
		;
	
	if(i < n)
		return ERROR;

	*e = p->data;

	return OK;
}

/*
 * On success, the number of @e in the @list is returned.
 * On error, -1 is returned.
 **/
int linklist_local_elem(linklist list, void *e,
			int (*compare)(void *, void *))
{
	int i, rslt = -1;
	linklist p;

	if(!list)
		return rslt;

	for(i = 1, p = list->next; p; ++i, p = p->next) {
		if(compare(p->data, e)) {
			rslt = i;
			break;
		}
	}

	return rslt;
}

status linklist_prev_elem(linklist list, void *cur_e, void **e, 
			int (*compare)(void *, void *))
{
	linklist p;
	
	if(!list || !list->next)
		return ERROR;
	
	for(p = list->next; p->next; p = p->next) {	
		if(compare(p->next->data, cur_e)) {
			*e = p->data;
			return OK;
		}
	}
	
	return ERROR;
}

status linklist_next_elem(linklist list, void *cur_e, void **e,
			int (*compare)(void *, void *))
{
	linklist p;

	if(!list || !list->next)
		return ERROR;

	for(p = list->next; p->next; p = p->next) {
		if(compare(p->data, cur_e)) {
			*e = p->next->data;
			return OK;
		}
	}

	return ERROR;
}

status linklist_insert(linklist list, int n, void *e)
{
	int i;
	linklist p, new_node;

	if(!list)
		return ERROR;
	
	for(i = 1, p = list; p->next && i < n; ++i, p = p->next)
		;

	if(i < n)
		return ERROR;

	if(!(new_node = malloc(sizeof(lnode))))
		return OVERFLOW;

	new_node->data = e;
	new_node->next = p->next;

	p->next = new_node;

	return OK;
}

status linklist_delete(linklist list, int n, void **e)
{
	int i;
	linklist p, del;

	if(!list)
		return ERROR;

	for(i = 1, p = list; p->next && i < n; ++i, p = p->next)
		;

	if(i < n)
		return ERROR;

	*e = p->data;

	del = p->next;
	p->next = del->next;
	free(del);

	return OK;
}

/*
 * These functions are support "None-Head Linklist", 
 * 	@list is the first element's pointer.
 */
void linklist_traverse(linklist list, void visit(void *))
{
	while(list) {
		visit(list->data);
		list = list->next;
	}

	printf("\n");
}

/* Refer to the notes above. */
void linklist_reverse_traverse(linklist list, void visit(void *))
{
	if(list) {
		linklist_reverse_traverse(list->next, visit);
		visit(list->data);
	}
}

/*
 * These functions are support "None-Head Linklist", 
 * 	@list is the first element's address in the memory.
 * Find the extremum of @list, compare rule is @compare.
 **/
status linklist_find_extremum(linklist *list,
			linklist **extrem, status (*compare)(void *, void *))
{
	if(!*list)
		return ERROR;
	
	*extrem = list;

	for(list = &(*list)->next; *list; list = &(*list)->next) {
		if(compare((*list)->data, (**extrem)->data))
			*extrem = list;
	}
	
	return OK;
}

/*
 * These functions are support "None-Head Linklist", 
 * 	@list is the first element's address in the memory.
 * Delete all the elements of @list which @cond(elems) is TRUE. 
 **/
status linklist_cond_delete(linklist *list, status (*cond)(void *))
{
	linklist del_node;

	if(!*list)
		return ERROR;

	while(*list) {
		if(cond((*list)->data)) {
			del_node = *list;
			*list = (*list)->next;
			
			free(del_node->data);
			free(del_node);
		}
		else
			list = &(*list)->next;
	}

	return OK;
}

/* Recursive method 1, refer to the notes above. */
status linklist_cond_delete_rec(linklist *list, status (*cond)(void *))
{
	linklist del_node;

	if(!*list)
		return ERROR;

	linklist_cond_delete_rec(&(*list)->next, cond);

	if(cond((*list)->data)) {
		del_node = *list;
		*list = (*list)->next;

		free(del_node->data);
		free(del_node);
	}

	return OK;
}

/* Recursive method 2, refer to the notes above. */
linklist linklist_cond_delete_rec_ex(linklist list, status (*cond)(void *))
{
	linklist del_node;

	if(!list)
		return NULL;
	
	list->next = linklist_cond_delete_rec_ex(list->next, cond);

	if(cond(list->data)) {
		del_node = list;
		list = list->next;

		free(del_node->data);
		free(del_node);
	}

	return list;
}				

status linklist_reverse(linklist list)
{
	linklist new_node, p;

	if(!list)
		return ERROR;

	for(p = list->next, list->next = NULL; p; ) {
		new_node = p;
		p = p->next;

		new_node->next = list->next;
		list->next = new_node;
	}
	
	return OK;
}

/* Append @list_b to @list_a. */
status linklist_append(linklist list_a, linklist list_b)
{
	linklist p;

	if(!list_a || !list_b)
		return ERROR;

	for(p = list_a; p->next; p = p->next)
		;

	p->next = list_b->next;

	return OK;
}

/*
 * These functions are support "None-Head Linklist", 
 * 	@list is the first element's address in the memory.
 * Sort list according to the rule @compare. 
 **/
void linklist_sort(linklist *list, 
				status (*compare)(void *, void *))
{
	linklist remains = *list;
	linklist *p = list, *extrem_ptr;

	while(linklist_find_extremum(&remains, &extrem_ptr, compare)
				&& *extrem_ptr) {

		*p = *extrem_ptr;
		p = &(*p)->next;

		*extrem_ptr = (*extrem_ptr)->next;
	}
	
}

/*
 * These functions are support "None-Head Linklist", 
 * 	@list is the first element's address in the memory.
 * Delete the repeating elements in the sorted linklist @list.
 **/
status linklist_delete_repeat(linklist *list,
			status equal(void *, void *))
{
	linklist del;
	linklist *prev, *p;

	if(!*list)
		return ERROR;
	
	for(prev = list, p = &(*list)->next; *p; p = &(*p)->next) {
		if(equal((*prev)->data, (*p)->data)) {
			del = *prev;
			*prev = (*prev)->next;
			free(del);	
		}
		else 
			prev = &(*prev)->next;
	}
	
	return OK;
}

/*
 * These functions are support "None-Head Linklist", 
 * 	@list is the first element's address in the memory.
 * Judge whether @list_b is @list_a's sub sequence.
 **/
status linklist_subseq(linklist list_a, linklist list_b,
			status equal(void *, void *))
{
	int sub_len;
	linklist pa = list_a, pb = list_b, cur_pa = pa;

	sub_len = linklist_length(list_a) - linklist_length(list_b);
	
	while(sub_len >= 0)	{
		if(!pb)
			return OK;

		if(equal(pa->data, pb->data)) {
			pa = pa->next;
			pb = pb->next;
		}
		else {
			cur_pa = cur_pa->next;

			pa = cur_pa;
			pb = list_b;
			
			--sub_len;
		}
	}
	
	return ERROR;
}

/* Create a linklist by using "Head-Insert" way for tests. */
status linklist_head_create(linklist list, int len, int size,
				void (*get_elem)(void *))
{
	int i;
	linklist new_node;

	for(i = 0; i < len; ++i) {
		if(!(new_node = malloc(sizeof(lnode))))
			return OVERFLOW;

		if(!(new_node->data = malloc(size)))
			return OVERFLOW;

		get_elem(new_node->data);
		new_node->next = list->next;

		list->next = new_node;
	}

	return OK;
}

/* Create a linklist by using "Tail-Insert" way for tests. */
status linklist_tail_create(linklist list, int len, int size,
				void (*get_elem)(void *))
{
	int i;
	linklist new_node, prev;
	
	for(i = 0, prev = list; i < len; ++i, prev = prev->next) {
		if(!(new_node = malloc(sizeof(lnode))))
			return OVERFLOW;
	
		if(!(new_node->data = malloc(size)))
			return OVERFLOW;

		get_elem(new_node->data);
		new_node->next = NULL;
	
		prev->next = new_node;
	}

	return OK;
}
