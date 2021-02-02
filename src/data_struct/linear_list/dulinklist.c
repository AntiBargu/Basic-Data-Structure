#include <stdio.h>
#include <stdlib.h>

#include "dulinklist.h"


status dulinklist_init(dulinklist *list)
{
	if(!(*list = malloc(sizeof(dulnode))))
		return OVERFLOW;

	(*list)->prev = NULL;
	(*list)->next = NULL;

	return OK;
}

status dulinklist_destroy(dulinklist *list)
{
	if(!dulinklist_clear(*list))
		return ERROR;

	free(*list);
	*list = NULL;
	
	return OK;
}

status dulinklist_clear(dulinklist list)
{
	dulinklist p, del_node;
	
	if(!list)
		return ERROR;

	for(p = list->next; p; p = p->next, free(del_node))
		del_node = p;
	
	list->next = NULL;
	list->prev = NULL;

	return OK;
}

status dulinklist_empty(dulinklist list)
{
	return NULL == list->next; 
}

int dulinklist_length(dulinklist list)
{
	int len = 0;
	dulinklist p;

	for(p = list->next; p; p = p->next)
		++len;

	return len;
}

status dulinklist_get_elem(dulinklist list, int n, void * *e)
{
	int i;
	dulinklist p;

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
 * 
 **/
int dulinklist_local_elem(dulinklist list, void *e,
			int (*compare)(void *, void *))
{
	int i, rslt = -1;
	dulinklist p;

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

status dulinklist_prev_elem(dulinklist list, void *cur_e, void **e, 
			int (*compare)(void *, void *))
{
	dulinklist p;
	
	if(!list || !list->next)
		return ERROR;
	
	for(p = list->next->next; p; p = p->next) {	
		if(compare(p->data, cur_e)) {
			*e = p->prev->data;
			return OK;
		}
	}
	
	return ERROR;
}

status dulinklist_next_elem(dulinklist list, void *cur_e,void **e,
			int (*compare)(void *, void *))
{
	dulinklist p;

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

status dulinklist_insert(dulinklist list, int n, void *e)
{
	int i;
	dulinklist p, new_node;

	if(!list)
		return ERROR;
	
	for(i = 1, p = list; i < n && p->next; ++i, p = p->next)
		;

	if(i < n)
		return ERROR;

	if(!(new_node = malloc(sizeof(dulnode))))
		return OVERFLOW;

	new_node->data = e;
	new_node->prev = p;
	new_node->next = p->next;

	p->next->prev = new_node;
	p->next = new_node;

	return OK;
}

status dulinklist_delete(dulinklist list, int n, void **e)
{
	int i;
	dulinklist p;

	if(!list)
		return ERROR;

	for(i = 1, p = list->next; i < n && p; ++i, p = p->next)
		;

	if(i < n)
		return ERROR;

	*e = p->data;

	if(p->next)
		p->next->prev = p->prev;

	p->prev->next = p->next;
	free(p);

	return OK;
}

status dulinklist_traverse(dulinklist list, void visit(void *))
{
	dulinklist p;
	
	if(!list)
		return ERROR;

	for(p = list->next; p; p = p->next)
		visit(p->data);

	printf("\n");

	return OK;
}

#if 0
void dulinklist_reverse_traverse(dulinklist list, void visit(void *))
{
	dulinklist p;

	for(p = list; p->next; p = p->next)
		;

	for(;p != list; p = p->prev)
		visit(p->data);

	printf("\n");
}
#endif

status dulinklist_find_extremum(dulinklist *list, 
			dulinklist **extrem, status (*compare)(void *, void *))
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

status dulinklist_head_create(dulinklist list, int len, int size,
			void (*get_elem)(void *))
{
	int i;
	dulinklist new_node;

	for(i = 0; i < len; ++i) {
		if(!(new_node = malloc(sizeof(dulnode))))
			return OVERFLOW;

		if(!(new_node->data = malloc(size)))
			return OVERFLOW;

		get_elem(new_node->data);

		new_node->next = list->next;
		new_node->prev = list;

		if(list->next)
			list->next->prev = new_node;
		list->next = new_node;
	}

	return OK;
}

status dulinklist_tail_create(dulinklist list, int len, int size,
			void (*get_elem)(void *))
{
	int i;
	dulinklist new_node, prev;
	
	for(i = 0, prev = list; i < len; ++i) {
		if(!(new_node = malloc(sizeof(dulnode))))
			return OVERFLOW;

		if(!(new_node->data = malloc(size)))
			return OVERFLOW;

		get_elem(new_node->data);

		new_node->next = NULL;
		new_node->prev = prev;

		prev->next = new_node;
		prev = prev->next;
	}

	return OK;
}
