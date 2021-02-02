#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "bitree.h"
#include "sqqueue.h"
#include "sqstack.h"
#include "exchange.h"

#define MAX_TREE_NUM	(100)

void bitree_init(bitree *t)
{
	*t = NULL;
}

void bitree_destroy(bitree *t)
{
	if(!*t)
		return ;
	
	bitree_destroy(&(*t)->lchild);
	bitree_destroy(&(*t)->rchild);
	
	free((*t)->data);
	free(*t);
	*t = NULL;
}

/*
 * It dose exist of @root while @get_elem returns TRUE,
 *  otherwise it dosen't exist.
 * */
void bitree_preorder_create(bitree *root, int size, status (*get_elem)(void *))
{
	void *new_data;
	
	do {
		if(!(new_data = malloc(size)))
			exit(ENOMEM);
	
		if(!get_elem(new_data)) {
			*root = NULL;
			free(new_data);
			break;
		}
	
		if(!(*root = malloc(sizeof(bitnode))))
			exit(ENOMEM);
	
		(*root)->data = new_data;

		bitree_preorder_create(&(*root)->lchild, size, get_elem);
		bitree_preorder_create(&(*root)->rchild, size, get_elem);

	} while(0);
}

void bitree_levelorder_create(bitree *root, int size, status (*get_elem)(void *))
{
	sq_queue queue;
	void *new_data;
	bitree *ptr, *lchild_ptr, *rchild_ptr;
	int gelem_size = sizeof(bitree *);

	sqqueue_init(&queue, gelem_size);
	sqqueue_enque(&queue, gelem_size, &root);

	while(!sqqueue_empty(queue)) {
		sqqueue_deque(&queue, gelem_size, &ptr);

		if(!(new_data = malloc(size)))
			exit(ENOMEM);
	
		if(!get_elem(new_data)) {
			*ptr = NULL;
			free(new_data);
		}
		else {
			if(!(*ptr = malloc(sizeof(bitnode))))
				exit(ENOMEM);
			
			(*ptr)->data = new_data;

			lchild_ptr = &(*ptr)->lchild;
			rchild_ptr = &(*ptr)->rchild;

			sqqueue_enque(&queue, gelem_size, &lchild_ptr);
			sqqueue_enque(&queue, gelem_size, &rchild_ptr);
		}
	}

	sqqueue_destroy(&queue);
}

int bitree_depth(bitree root)
{
	int left_depth, right_depth;

	if(!root)
		return 0;

	left_depth = bitree_depth(root->lchild);
	right_depth = bitree_depth(root->rchild);

	return (left_depth > right_depth ? left_depth : right_depth) + 1;
}

int bitree_width(bitree root)
{
	bitree ptr;
	sq_queue queue;
	int last_pos = 0, width = 1, qelem_size = sizeof(bitree);
	
	if(!root)
		return 0;

	sqqueue_init(&queue, qelem_size);	
	sqqueue_enque(&queue, qelem_size, &root);

	while(!sqqueue_empty(queue)) {
		sqqueue_deque(&queue, qelem_size, &ptr);

		if(ptr->lchild)
			sqqueue_enque(&queue, qelem_size, &ptr->lchild);

		if(ptr->rchild)
			sqqueue_enque(&queue, qelem_size, &ptr->rchild);

		if(queue.front > last_pos) {
			width = sqqueue_length(queue) > width ?
					sqqueue_length(queue) : width;

			last_pos = queue.rear - 1;
		}
	}

	sqqueue_destroy(&queue);
	
	return width;
}

/*
 * On success, the pointer of target node is returned.
 * On failed, NULL is returned.
 * */
bitree bitree_local_elem(bitree t, void *elem, 
			status (*compare)(void *, void *))
{
	sq_stack stack;
	bitree rslt = NULL;
	int selem_size = sizeof(bitree);

	sqstack_init(&stack,selem_size);

	while(t || !sqstack_empty(stack)) {
		if(t) {
			if(compare(t->data, elem)) {
				rslt = t;
				break;
			}

			sqstack_push(&stack, selem_size, &t);
			t = t->lchild;
		}
		else {
			sqstack_pop(&stack, selem_size, &t);
			t = t->rchild;
		}
	}

	sqstack_destroy(&stack);

	return rslt;
}

/*
 * On success, array of the ancestors is returned.
 * On failed, NULL is returned.
 * */
bitree *bitree_get_ancestor(bitree root, bitree tree, int *len,
			status (*compare)(void *, void *))
{
	bitree *rslt, last;
	sq_stack stack;
	int selem_size = sizeof(bitree);

	if(!(rslt = malloc(bitree_depth(root) * sizeof(bitree))))
		exit(ENOMEM);

	sqstack_init(&stack,selem_size);

	while(root || !sqstack_empty(stack)) {
		if(root) {
			if(compare(root->data, tree->data))
				break;

			sqstack_push(&stack, selem_size, &root);
			root =root->lchild;
		}
		else {
			sqstack_get_top(stack, selem_size, &root);

			if(!root->rchild || root->rchild == last) {
				sqstack_pop(&stack, selem_size, &root);
				last = root;
				root = NULL;
			}
			else 
				root = root->rchild;
		}
	}
	
	*len = sqstack_length(stack, selem_size);
	memcpy(rslt, stack.base, stack.top - stack.base);

	sqstack_destroy(&stack);
	
	return rslt;
}

status bitree_is_complete(bitree t)
{
	int tree_size = sizeof(bitree);

	bitree ptr;
	sq_queue queue;

	if(!t)
		return OK;

	sqqueue_init(&queue, tree_size);
	sqqueue_enque(&queue, tree_size, &t);

	while(!sqqueue_empty(queue)) {
		sqqueue_deque(&queue, tree_size, &ptr);

		if(!ptr)
			break;
	
		sqqueue_enque(&queue, tree_size, &ptr->lchild);
		sqqueue_enque(&queue, tree_size, &ptr->rchild);
	}

	while(!sqqueue_empty(queue)) {
		sqqueue_deque(&queue, tree_size, &ptr);

		if(ptr)
			return ERROR;
	}

	return OK;
}

void bitree_preorder_traverse(bitree t, void (*visit)(void *))
{
	if(t) {
		visit(t->data);
		bitree_preorder_traverse(t->lchild, visit);
		bitree_preorder_traverse(t->rchild, visit);
	}
}

void bitree_inorder_traverse(bitree t, void (*visit)(void *))
{
	if(t) {
		bitree_inorder_traverse(t->lchild, visit);
		visit(t->data);
		bitree_inorder_traverse(t->rchild, visit);
	}
}

void bitree_postorder_traverse(bitree t, void (*visit)(void *))
{
	if(t) {
		bitree_postorder_traverse(t->lchild, visit);
		bitree_postorder_traverse(t->rchild, visit);
		visit(t->data);
	}
}

void bitree_levelorder_traverse(bitree t, void (*visit)(void *))
{
	bitree ptr;
	sq_queue queue;
	int tree_size = sizeof(bitree);
	
	if(!t)
		return ;

	sqqueue_init(&queue, tree_size);	
	sqqueue_enque(&queue, tree_size, &t);

	while(!sqqueue_empty(queue)) {
		sqqueue_deque(&queue, tree_size, &ptr);

		visit(ptr->data);

		if(ptr->lchild)
			sqqueue_enque(&queue, tree_size, &ptr->lchild);

		if(ptr->rchild)
			sqqueue_enque(&queue, tree_size, &ptr->rchild);

	}

	sqqueue_destroy(&queue);
}

void bitree_levelorder_reverse_traverse(bitree t,
			void (*visit)(void *))
{
	int front = 0, rear = 1;
	bitree *trees;

	if(!t)
		return ;

	if(!(trees = malloc(MAX_TREE_NUM * sizeof(bitree))))
		exit(ENOMEM);

	trees[0] = t;

	while(front != rear) {
		t = trees[front++];
		if(t->lchild)
			trees[rear++] = t->lchild;
		if(t->rchild)
			trees[rear++] = t->rchild;
	}

	while(rear > 0)
		visit(trees[--rear]->data);
}

/* Non recurse binary tree preorder traverse. */
void bitree_preorder_traverse_ex(bitree t, void (*visit)(void *))
{
	sq_stack stack;
	int elem_size = sizeof(bitree);

	sqstack_init(&stack, elem_size);

	while(t || !sqstack_empty(stack)) {
		if(t) {
			visit(t->data);
			sqstack_push(&stack, elem_size, &t);
			t = t->lchild;
		}
		else {
			sqstack_pop(&stack, elem_size, &t);
			t = t->rchild;
		}
	}

	sqstack_destroy(&stack);
}

/* Non recurse binary tree inorder traverse. */
void bitree_inorder_traverse_ex(bitree t, void (*visit)(void *))
{
	sq_stack stack;
	int elem_size = sizeof(bitree);

	sqstack_init(&stack, elem_size);

	while(t || !sqstack_empty(stack)) {
		if(t) {
			sqstack_push(&stack, elem_size, &t);
			t = t->lchild;
		}
		else {
			sqstack_pop(&stack, elem_size, &t);
			visit(t->data);
			t = t->rchild;
		}
	}

	sqstack_destroy(&stack);
}

/* Non recurse binary tree postorder traverse. */
void bitree_postorder_traverse_ex(bitree t, void (*visit)(void *))
{
	bitree last;
	sq_stack stack;
	int elem_size = sizeof(bitree);

	sqstack_init(&stack, elem_size);

	while(t || !sqstack_empty(stack)) {
		if(t) {
			sqstack_push(&stack, elem_size, &t);
			t = t->lchild;
		}
		else {
			sqstack_get_top(stack, elem_size, &t);

			if(!t->rchild || t->rchild == last) {
				sqstack_pop(&stack, elem_size, &t);
				visit(t->data);
				last = t;
				t = NULL;
			}
			else 
				t = t->rchild;
		}
	}

	sqstack_destroy(&stack);
}

void bitree_to_glist(bitree root, void (*visit)(void *))
{
	if(NULL == root) {
		printf("NULL");
		return ;
	}
		
	visit(root->data);

	if(root->lchild || root->rchild) {
		printf("(");
		bitree_to_glist(root->lchild, visit);
		printf(",");
		bitree_to_glist(root->rchild, visit);
		printf(")");
	}
}

void bitree_exchange_childs(bitree root)
{
	if(NULL == root)
		return ;

	exchange(&root->lchild, &root->rchild, sizeof(bitree));

	bitree_exchange_childs(root->lchild);
	bitree_exchange_childs(root->rchild);
}

void bitree_copy(bitree *dest, const bitree *src, int size)
{
	if(!*src)
		*dest = NULL;
	else {
		if(!(*dest = malloc(sizeof(bitnode))))
			exit(ENOMEM);

		if(!((*dest)->data = malloc(size)))
			exit(ENOMEM);

		memcpy((*dest)->data, (*src)->data, size);
		bitree_copy(&(*dest)->lchild, &(*src)->lchild, size);
		bitree_copy(&(*dest)->rchild, &(*src)->rchild, size);
	}
		
}
