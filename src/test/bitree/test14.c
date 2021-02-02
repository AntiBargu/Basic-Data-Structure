#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "bitree.h"
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

bitree bitree_postorder_first(bitree root)
{
	while(root->lchild || root->rchild) {
		if(root->lchild) {
			root = root->lchild;
			continue;
		}

		if(root->rchild)
			root = root->rchild;
	}

	return root;
}

/* Of the same type, please refer to test7. */
int main(int argc, char *argv[])
{
	int elem_size = TYPE_SIZE;
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	bitree root, last_node;

	printf("[bitree - Test 14] Get Bitree Postorder First Node:\n");

	get_terminator(elem_size);

	bitree_init(&root);
	bitree_levelorder_create(&root, elem_size, bitree_get_data);

	printf("The binary tree is:\n");
	bitree_to_glist(root, show_elem);
	printf("\n");

	last_node = bitree_postorder_first(root);

	printf("Postorder first node is: ");
	show_elem(last_node->data);
	printf("\n");

	bitree_destroy(&root);

	return EXIT_SUCCESS;
}
