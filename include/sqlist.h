#ifndef _SQLIST_H
#define _SQLIST_H

#include "common.h"

#define LIST_INIT_SIZE	(100)

typedef struct {
	void *elem;
	int usage;
	int size;
}sq_list;

extern status sqlist_init(sq_list *list, int size);
extern status sqlist_destroy(sq_list *list);
extern status sqlist_clear(sq_list *list);

extern status sqlist_empty(sq_list list);
extern int sqlist_length(sq_list list);

extern status sqlist_get_elem(sq_list list, int i, int size, void **e);
extern int sqlist_local_elem(sq_list list, int size, void *e,
			int (*compare)(void *, void *));

extern status sqlist_prior_elem(sq_list list, int size, void *cur_e,
			void **e, int (*compare)(void *, void *));
extern status sqlist_next_elem(sq_list list, int size, void *cur_e,
			void **e, int (*compare)(void *, void *));

extern status sqlist_insert(sq_list *list, int i, int size, void *e);
extern status sqlist_delete(sq_list *list, int i, int size, void **e);

extern status sqlist_traverse(sq_list list, int size, 
			void (*visit)(void *));


/* Following functions are added for subjects. */
extern void sqlist_reverse(sq_list *list, int size);

extern status sqlist_get_extremum(sq_list list, int size,
			status (*compare)(void *, void *), int *pos);

/* Delete all the elements of @list which @cond(elems) is TRUE. */
extern status sqlist_cond_delete(sq_list *list, int size,
			status (*cond)(void *));

/* Delete elements of @list from @mth to @nth. */
extern status sqlist_block_delete(sq_list *list, int m, int n, int size);

/* Merge two sorted list @list_a and @list_b into a sorted list @list_c. */
extern void sqlist_merge(sq_list list_a, sq_list list_b, 
			sq_list *list_c, int size, status (*compare)(void *, void *));

/* Delete all repeating elements of sorted list @list. */
extern void sqlist_delete_repeat(sq_list *list, int size,
			status (*equal)(void *, void *));

/* Create a sqlist for tests. */
extern status sqlist_rand_create(sq_list *list, int len, int size,
			void (*get_elem)(void *));

#endif	/* _SQLIST_H */

