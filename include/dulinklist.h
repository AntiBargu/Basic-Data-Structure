#ifndef _DULINKLIST_H
#define _DULINKLIST_H

#include "common.h"

typedef struct dulnode{
	void * data;
	struct dulnode *prev, *next;
}dulnode, *dulinklist;

extern status dulinklist_init(dulinklist *list);
extern status dulinklist_destroy(dulinklist *list);
extern status dulinklist_clear(dulinklist list);

extern status dulinklist_empty(dulinklist list);
extern int dulinklist_length(dulinklist list);

extern status dulinklist_get_elem(dulinklist list, int n, void **e);
extern int dulinklist_local_elem(dulinklist list, void *e,
			int (*compare)(void *, void *));

extern status dulinklist_prev_elem(dulinklist list, void *cur_e, 
			void **e, int (*compare)(void *, void *));
extern status dulinklist_next_elem(dulinklist list, void *cur_e,
			void **e, int (*compare)(void *, void *));

extern status dulinklist_insert(dulinklist list, int n, void *e);
extern status dulinklist_delete(dulinklist list, int n, void **e);

extern status dulinklist_traverse(dulinklist list, void visit(void *));

#if 0
extern void dulinklist_reverse_traverse(dulinklist list, void visit(void *));
#endif

extern status dulinklist_find_extremum(dulinklist *list, 
			dulinklist **extrem, status (*compare)(void *, void *));

extern status dulinklist_head_create(dulinklist list, int len, int size,
			void (*get_elem)(void *));

extern status dulinklist_tail_create(dulinklist list, int len, int size, 
			void (*get_elem)(void *));

#endif /* _DULINKLIST_H */
