#include <stdio.h>
#include <stdlib.h>

#include "clinklist.h"


status clinklist_init(clinklist *list)
{
	if(!(*list = malloc(sizeof(clnode))))
		return OVERFLOW;

	(*list)->next = *list;

	return OK;
}

status clinklist_destroy(clinklist *list)
{
	if(!clinklist_clear(*list))
		return ERROR;
	
	free(*list);
	*list = NULL;

	return OK;
}

status clinklist_clear(clinklist list)
{
	clinklist p, del_node;

	if(!list)
		return ERROR;

	for(p = list->next; p != list; 
			p = p->next, free(del_node->data), free(del_node))
		del_node = p;
	
	list->next = list;

	return OK;
}

status clinklist_empty(clinklist list)
{
	return list == list->next; 
}

int clinklist_length(clinklist list)
{
	int len = 0;
	clinklist p;

	for(p = list->next; p != list; p = p->next)
		++len;

	return len;
}

status clinklist_get_elem(clinklist list, int n, void **e)
{
	int i;
	clinklist p;

	if(!list)
		return ERROR;

	for(i = 1, p = list->next; i < n && p != list; ++i, p = p->next)
		--i;
		
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
int clinklist_local_elem(clinklist list, void *e,
			int (*compare)(void *, void *))
{
	int i, rslt = -1;
	clinklist p;

	if(!list)
		return -1;

	for(i = 1, p = list->next; p != list; ++i, p = p->next) {
		if(compare(p->data, e)) {
			rslt = i;
			break;
		}
	}

	return rslt;
}

status clinklist_prev_elem(clinklist list, void *cur_e, void **e, 
			int (*compare)(void *, void *))
{
	clinklist p;
	
	if(!list || list->next == list)
		return ERROR;
	
	for(p = list->next; p->next != list; p = p->next) {	
		if(compare(p->next->data, cur_e)) {
			*e = p->data;
			return OK;
		}
	}
	
	return ERROR;
}

status clinklist_next_elem(clinklist list, void *cur_e, void **e,
			int (*compare)(void *, void *))
{
	clinklist p;

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

status clinklist_insert(clinklist list, int n, void *e)
{
	int i;
	clinklist p, new_node;

	if(!list)
		return ERROR;
	
	for(i = 1, p = list; i < n && p->next != list; ++i, p = p->next)
		;

	if(i < n)
		return ERROR;

	if(NULL == (new_node = malloc(sizeof(clnode))))
		exit(OVERFLOW);

	new_node->data = e;
	new_node->next = p->next;

	p->next = new_node;

	return OK;
}

status clinklist_delete(clinklist list, int n, void **e)
{
	int i;
	clinklist p, del;

	if(!list)
		return ERROR;

	for(i = 1, p = list; i < n && p->next != list; ++i, p = p->next)
		;

	if(i < n)
		return ERROR;

	del = p->next;

	*e = del->data;

	p->next = del->next;
	free(del);

	return OK;
}

status clinklist_traverse(clinklist list, void visit(void *))
{
	clinklist p;

	if(!list)
		return ERROR;

	for(p = list->next; p != list; p = p->next)
		visit(p->data);

	printf("\n");

	return OK;
}

status clinklist_find_extremum(clinklist *list,
			clinklist **extrem, status (*compare)(void *, void *))
{
	clinklist *p;

	if((*list)->next == *list)
		return ERROR;
	
	*extrem = list;

	for(p = list; (*p)->next != *list; p = &(*p)->next) {
		if(compare((*p)->data, (**extrem)->data))
			*extrem = p;	
	}
	
	return OK;
}

status clinklist_head_create(clinklist list, int len, int size,
				void (*get_elem)(void *))
{
	int i;
	clinklist new_node;

	for(i = 0; i < len; ++i) {
		if(!(new_node = malloc(sizeof(clnode))))
			return OVERFLOW;

		if(!(new_node->data = malloc(size)))
			return OVERFLOW;

		get_elem(new_node->data);
		new_node->next = list->next;

		list->next = new_node;
	}

	return OK;
}

status clinklist_tail_create(clinklist list, int len, int size,
				void (*get_elem)(void *))
{
	int i;
	clinklist new_node, prev;
	
	for(i = 0, prev = list; i < len; ++i, prev = prev->next) {
		if(!(new_node = malloc(sizeof(clnode))))
			return OVERFLOW;

		if(!(new_node->data = malloc(size)))
			return OVERFLOW;

		get_elem(new_node->data);
		new_node->next = list;
	
		prev->next = new_node;
	}

	return OK;		
}
