#ifndef _DUCLINKLIST_H
#define _DUCLINKLIST_H

#include "common.h"

typedef struct duclnode{
	void *data;
	struct duclnode *prev, *next;
}duclnode, *duclinklist;

extern status duclinklist_init(duclinklist *list);
extern status duclinklist_destroy(duclinklist *list);
extern status duclinklist_clear(duclinklist list);

extern status duclinklist_empty(duclinklist list);
extern int duclinklist_length(duclinklist list);

extern status duclinklist_get_elem(duclinklist list, int i, void **e);
extern int duclinklist_local_elem(duclinklist list, void *e,
			int (*compare)(void *, void *));

extern status duclinklist_prev_elem(duclinklist list,
			void *cur_e, void **e, int (*compare)(void *, void *));
extern status duclinklist_next_elem(duclinklist list,
			void *cur_e, void **e, int (*compare)(void *, void *));

extern status duclinklist_insert(duclinklist list, int i, void *e);
extern status duclinklist_delete(duclinklist list, int i, void **e);

extern status duclinklist_traverse(duclinklist list, 
			void (*visit)(void *));

extern status duclinklist_head_create(duclinklist list, int len,	
			int size, void (*get_elem)(void *));
extern status duclinklist_tail_create(duclinklist list, int len,
			int size, void (*get_elem)(void *));

#endif /* _DUCLINKLIST_H */
