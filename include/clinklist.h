#ifndef _CLINKLIST_H
#define _CLINKLIST_H

#include "common.h"

typedef struct clnode{
	void *data;
	struct clnode *next;
}clnode, *clinklist;

extern status clinklist_init(clinklist *list);
extern status clinklist_destroy(clinklist *list);
extern status clinklist_clear(clinklist list);

extern status clinklist_empty(clinklist list);
extern int clinklist_length(clinklist list);

extern status clinklist_get_elem(clinklist list, int n, void **e);
extern int clinklist_local_elem(clinklist list, void *e,
			int (*compare)(void *, void *));

extern status clinklist_prev_elem(clinklist list, void *cur_e, 
			void **e, int (*compare)(void *, void *));
extern status clinklist_next_elem(clinklist list, void *cur_e,
			void **e, int (*compare)(void *, void *));

extern status clinklist_insert(clinklist list, int n, void *e);

extern status clinklist_delete(clinklist list, int n, void **e);

extern status clinklist_traverse(clinklist list, void visit(void *));

/*
 * These functions are support "None-Head Circular Linklist", 
 * 	@list is the first element's address in the memory.
 * Find the extremum of @list, compare rule is @compare.
 **/
extern status clinklist_find_extremum(clinklist *list, 
			clinklist **extrem, status (*compare)(void *, void *));

/* Create a clinklist by using "Head-Insert" way for tests. */
extern status clinklist_head_create(clinklist list, int len,
			int size, void (*get_elem)(void *));

/* Create a clinklist by using "Tail-Insert" way for tests. */
extern status clinklist_tail_create(clinklist list, int len,
			int size, void (*get_elem)(void *));

#endif	/* _CLINKLIST_H */
