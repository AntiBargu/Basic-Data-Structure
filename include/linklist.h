#ifndef _LINKLIST_H
#define _LINKLIST_H

#include "common.h"

typedef struct lnode{
	void *data;
	struct lnode *next;
}lnode, *linklist;

extern status linklist_init(linklist *list);
extern status linklist_destroy(linklist *list);
extern status linklist_clear(linklist list);

extern status linklist_empty(linklist list);
extern int linklist_length(linklist list);

extern status linklist_get_elem(linklist list, int i, void **e);
extern int linklist_local_elem(linklist list, void *e,
			int (*compare)(void *, void *));

extern status linklist_prior_elem(linklist list, void *cur_e, void **e, 
			int (*compare)(void *, void *));
extern status linklist_next_elem(linklist list, void *cur_e, void **e,
			int (*compare)(void *, void *));

extern status linklist_insert(linklist list, int i, void *e);

extern status linklist_delete(linklist list, int i, void **e);

extern void linklist_traverse(linklist list, void visit(void *));
extern void linklist_reverse_traverse(linklist list, void visit(void *));

/*
 * These functions are support "None-Head Linklist", 
 * 	@list is the first element's address in the memory.
 * Find the extremum of @list, compare rule is @compare.
 **/
extern status linklist_find_extremum(linklist *list,
			linklist **extrem, status (*compare)(void *, void *));

/*
 * These functions are support "None-Head Linklist", 
 * 	@list is the first element's address in the memory.
 * Delete all the elements of @list which @cond(elems) is TRUE. 
 **/
extern status linklist_cond_delete(linklist *list, status (*cond)(void *));
extern status linklist_cond_delete_rec(linklist *list, status (*cond)(void *));
extern linklist linklist_cond_delete_rec_ex(linklist list, status (*cond)(void *));

extern status linklist_reverse(linklist list);

/* Append @list_b to @list_a. */
extern status linklist_append(linklist list_a, linklist list_b);

/*
 * These functions are support "None-Head Linklist", 
 * 	@list is the first element's address in the memory.
 * Sort list according to the compare rule @compare. 
 **/
extern void linklist_sort(linklist *list, 
				status (*compare)(void *, void *));

/*
 * These functions are support "None-Head Linklist", 
 * 	@list is the first element's address in the memory.
 * Delete the repeating elements in the sorted linklist @list.
 **/
extern status linklist_delete_repeat(linklist *list,
			status equal_to(void *, void *));

/*
 * These functions are support "None-Head Linklist", 
 * 	@list is the first element's address in the memory.
 * Judge whether @list_b is @list_a's sub sequence.
 **/
extern status linklist_subseq(linklist list_a, linklist list_b,
			status equal_to(void *, void *));

/* Create a linklist by using "Head-Insert" way for tests. */
extern status linklist_head_create(linklist list, int len, int size,
				void (*get_elem)(void *));

/* Create a linklist by using "Tail-Insert" way for tests. */
extern status linklist_tail_create(linklist list, int len, int size,
				void (*get_elem)(void *));

#endif	/* _LINKLIST_H */
