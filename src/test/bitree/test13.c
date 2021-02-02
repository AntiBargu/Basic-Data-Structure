#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "bitree.h"
#include "generic_type.h"


void binary_sort_tree_insert(bitree *root, void *data, int size,
			status (*compare)(void *, void *))
{
	bitree *child;

	if(NULL == *root) {
		if(!(*root = malloc(sizeof(bitnode))))
			exit(ENOMEM);
		
		if(!((*root)->data = malloc(size)))
			exit(ENOMEM);

		memcpy((*root)->data, data, size);
		(*root)->lchild = NULL;
		(*root)->rchild = NULL;
	}
	else {
		child = compare(data, (*root)->data) ? 
			&(*root)->lchild : &(*root)->rchild;

		binary_sort_tree_insert(child, data, size, compare);
	}
}

int main(int argc, char *argv[])
{
	int elem_size = TYPE_SIZE;
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);
	void (*get_elem)(void *) = TYPE_FUNC(get_stdin_elem);

	status (*compare)(void *, void *) = TYPE_FUNC(less_than);

	int i, len;
	void *data;
	bitree root;

	printf("[bitree - Test 13] Create Binary Sort Tree:\n") ;

	bitree_init(&root);

	if(!(data = malloc(elem_size)))
		exit(ENOMEM);

	printf("Please insert count of tree's node:\n");
	scanf("%d", &len);

	printf("Please insert the elements\n");
	for(i = 0; i < len; ++i) {
		get_elem(data);
		binary_sort_tree_insert(&root, data, elem_size, compare);	
	}
	
	printf("The binary tree is:\n");
	bitree_to_glist(root, show_elem);
	printf("\n");

	printf("Bitree inorder traverse:\n");
	bitree_inorder_traverse(root, show_elem);
	printf("\n");
	
	bitree_destroy(&root);

	return EXIT_SUCCESS;
}
