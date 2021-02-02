#ifndef _BITREE_H
#define _BITREE_H

#include "common.h"

typedef struct bitnode{
	void *data;
	struct bitnode *lchild, *rchild;
}bitnode, *bitree;


extern void bitree_init(bitree *t);
extern void bitree_destroy(bitree *t);

extern void bitree_preorder_create(bitree *t, int size, 
			status (*get_elem)(void *));

extern void bitree_levelorder_create(bitree *t, int size,
			status (*get_elem)(void *));

/*
 * On success, the pointer of target node is returned.
 * On failed, NULL is returned.
 * */
extern bitree bitree_local_elem(bitree t, void *elem, 
			status (*compare)(void *, void *));

extern bitree *bitree_get_ancestor(bitree root, bitree tree, 
			int *len, status (*compare)(void *, void *));

extern int bitree_depth(bitree tree);
extern int bitree_width(bitree root);

extern status bitree_is_complete(bitree t);

extern void bitree_preorder_traverse(bitree t, void (*visit)(void *));
extern void bitree_inorder_traverse(bitree t, void (*visit)(void *));
extern void bitree_postorder_traverse(bitree t, void (*visit)(void *));

extern void bitree_levelorder_traverse(bitree t,
			void (*visit)(void *));
extern void bitree_levelorder_reverse_traverse(bitree t,
			void (*visit)(void *));

extern void bitree_preorder_traverse_ex(bitree t, void (*visit)(void *));
extern void bitree_inorder_traverse_ex(bitree t, void (*visit)(void *));
extern void bitree_postorder_traverse_ex(bitree t, void (*visit)(void *));

extern void bitree_to_glist(bitree t, void (*visit)(void *));

extern void bitree_exchange_childs(bitree root);

extern void bitree_copy(bitree *dest, const bitree *src, int size);

#endif	/* _BITREE_H */
