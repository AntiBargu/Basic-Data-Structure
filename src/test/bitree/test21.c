#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "bitree.h"
#include "sqstack.h"
#include "generic_type.h"


static void *terminator;

void get_terminator(int size)
{
	void (*get_elem)(void *) = TYPE_FUNC(get_stdin_elem);

	if(!(terminator = malloc(size)))
		exit(ENOMEM);

	printf("Please insert the terminator of the tree:\n");
	get_elem(terminator);
}

status bitree_get_data(void *ptr)
{
	TYPE_FUNC(get_stdin_elem)(ptr);
	
	return !TYPE_FUNC(equal)(ptr, terminator);
}

void show_bitree_info(void *ptr)
{
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	show_elem(((bitree)ptr)->data);
}

bitree *bitree_get_longest_path(bitree root, int *max_len)
{
	sq_stack stack;
	bitree last, *rslt;
	int cur_len, selem_size = sizeof(bitree);

	*max_len = 0;

	if(!(rslt = malloc(sizeof(bitree) * 100)))
		exit(ENOMEM);

	sqstack_init(&stack, selem_size);

	while(root || !sqstack_empty(stack)) {
		if(root) {
			sqstack_push(&stack, selem_size, &root);

			cur_len = sqstack_length(stack, selem_size);

			if(cur_len > *max_len) {
				*max_len = cur_len;
				memcpy(rslt, stack.base, selem_size * *max_len);
			}

			root = root->lchild;
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

	sqstack_destroy(&stack);
	
	return rslt;
}

int main(int argc, char *argv[])
{
	int elem_size = TYPE_SIZE;
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	int i, max_len;
	bitree root, *tree_path;
	
	printf("[bitree - Test 21] Get Longest Path of The Bitree:\n") ;

	get_terminator(elem_size);

	bitree_init(&root);
	bitree_levelorder_create(&root, elem_size, bitree_get_data);

	printf("The binary tree is:\n");
	bitree_to_glist(root, show_elem);
	printf("\n");

	tree_path = bitree_get_longest_path(root, &max_len);

	printf("The length of longest path is %d\n", max_len);

	for(i = 0; i < max_len; ++i) {
		show_elem(tree_path[i]->data);
	}
	printf("\n");

	free(tree_path);
	bitree_destroy(&root);

	return EXIT_SUCCESS;
}
