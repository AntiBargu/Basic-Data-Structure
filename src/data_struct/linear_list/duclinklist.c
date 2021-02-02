#include <stdio.h>
#include <stdlib.h>

#include "duclinklist.h"


status duclinklist_init(duclinklist *list)
{
	if(!(*list = malloc(sizeof(duclnode))))
		return OVERFLOW;

	(*list)->prev = *list;
	(*list)->next = *list;

	return OK;
}

status duclinklist_destroy(duclinklist *list)
{
	if(!duclinklist_clear(*list))
		return ERROR;

	free(*list);
	*list = NULL;
	
	return OK;
}

status duclinklist_clear(duclinklist list)
{
	duclinklist p, del_node;
		
	if(!list)
		return ERROR;

	for(p = list->next; p != list; 
			p = p->next, free(del_node->data), free(del_node)) 
		del_node = p;
	
	list->next = list;
	list->prev = list;	

	return OK;
}

status duclinklist_empty(duclinklist list)
{
	return list == list->next; 
}

int duclinklist_length(duclinklist list)
{
	int len = 0;
	duclinklist p;

	for(p = list->next; p != list; p = p->next)
		++len;

	return len;
}

status duclinklist_get_elem(duclinklist list, int n, void **e)
{
	int i;
	duclinklist p;
	
	if(!list)
		return ERROR;

	for(i = 1, p = list->next; i < n && p != list; ++i, p = p->next)
		;

	if(i < n)
		return ERROR;

	*e = p->data;

	return OK;
}

/*
 * On success, the number of @e in the @list is returned.
 * On error, -1 is returned.
 * 
 **/
int duclinklist_local_elem(duclinklist list, void *e,
			int (*compare)(void *, void *))
{
	int i, rslt = -1;
	duclinklist p;
	
	if(!list)
		return rslt;

	for(i = 1, p = list->next; p != list ; ++i, p = p->next) {
		if(compare(p->data, e)) {
			rslt = i;
			break;
		}
	}

	return rslt;
}

status duclinklist_prev_elem(duclinklist list, void *cur_e, void **e, 
			int (*compare)(void *, void *))
{
	duclinklist p;
	
	if(!list || list->next == list)
		return ERROR;
	
	for(p = list->next->next; p != list; p = p->next) {	
		if(compare(p->data, cur_e)) {
			*e = p->prev->data;
			return OK;
		}
	}
	
	return ERROR;
}

status duclinklist_next_elem(duclinklist list, void *cur_e, void **e,
			int (*compare)(void *, void *))
{
	duclinklist p;

	if(!list || list->next == list)
		return ERROR;

	for(p = list->next; p->next != list; p = p->next) {
		if(compare(p->data, cur_e)) {
			*e = p->next->data;
			return OK;
		}
	}

	return ERROR;
}

status duclinklist_insert(duclinklist list, int n, void *e)
{
	int i;
	duclinklist p, new_node;

	if(!list)
		return ERROR;
	
	for(i = 1, p = list; i < n && p != list; ++i, p = p->next)
		;

	if(i < n)
		return ERROR;

	if(!(new_node = malloc(sizeof(duclnode))))
		return OVERFLOW;

	new_node->data = e;
	new_node->prev = p;
	new_node->next = p->next;

	p->next->prev = new_node;
	p->next = new_node;

	return OK;
}

status duclinklist_delete(duclinklist list, int n, void **e)
{
	int i;
	duclinklist p;

	if(!list)
		return ERROR;

	for(i = 1, p = list->next; i < n && p != list; ++i, p = p->next)
		;

	if(i < n)
		return ERROR;

	*e = p->data;

	p->next->prev = p->prev;
	p->prev->next = p->next;
	free(p);

	return OK;
}

status duclinklist_traverse(duclinklist list, void (*visit)(void *))
{
	duclinklist p;
	
	if(!list)
		return ERROR;

	for(p = list->next; p != list; p = p->next)
		visit(p->data);

	printf("\n");

	return OK;
}

status duclinklist_head_create(duclinklist list, int len, int size,
			void (*get_elem)(void *))
{
	int i;
	duclinklist new_node;

	for(i = 0; i < len; ++i) {
		if(!(new_node = malloc(sizeof(duclnode))))
			return OVERFLOW;

		if(!(new_node->data = malloc(size)))
			return OVERFLOW;

		get_elem(new_node->data);

		new_node->next = list->next;
		new_node->prev = list;

		list->next->prev = new_node;
		list->next = new_node;
	}

	return OK;
}

status duclinklist_tail_create(duclinklist list, int len, int size,
			void (*get_elem)(void *))
{
	int i;
	duclinklist new_node, prev;
	
	for(i = 0, prev = list; i < len; ++i, prev = prev->next) {
		if(!(new_node = malloc(sizeof(duclnode))))
			return OVERFLOW;

		if(!(new_node->data = malloc(size)))
			return OVERFLOW;

		get_elem(new_node->data);

		new_node->next = list;
		new_node->prev = prev;

		list->prev = new_node;
		prev->next = new_node;
	}

	return OK;
}
