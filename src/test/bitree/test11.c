#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "bitree.h"
#include "search.h"


void show_char(void *ptr)
{
	printf("%c", *(char *)ptr);
}

status char_equal(void *a, void *b)
{
	return *(char *)a == *(char *)b;
}

static void bitree_inpost_create(bitree *root, 
			char *inorder, char *postorder, int len)
{
	int root_inorder_pos;
	char *data;

	if(0 == len) {
		*root = NULL;
		return ;
	}

	if(!(data = malloc(1)))
		exit(ENOMEM);
	
	*data = *(postorder + len - 1);
	
	if(!(*root = malloc(sizeof(bitnode))))
		exit(ENOMEM);

	(*root)->data = data;
	
	/* Get the position of @root in the inorder sequence @inorder. */
	seq_search(inorder, len, 1, data, &root_inorder_pos, 
			char_equal);

	bitree_inpost_create(&(*root)->lchild, inorder, 
			postorder, root_inorder_pos - 1);

	bitree_inpost_create(&(*root)->rchild, inorder + root_inorder_pos,
			postorder + root_inorder_pos - 1, len - root_inorder_pos);
}

/*
 * In this test, 
 *  we create a binary tree through the string which @argv[1] takes,
 *	each element of the binary tree is a char.
 **/
int main(int argc, char *argv[])
{
	int len;
	bitree root;

	if(argc < 3) {
		fprintf(stderr, "Usage: %s [inorder] [postorder]\n", argv[0]);
		exit(EINVAL);
	}

	if(strlen(argv[1]) != strlen(argv[2])) {
		fprintf(stderr, "Agument Error\n");
		exit(EINVAL);
	}

	printf("[bitree - Test 11] Create Bitree According to Inorder and Postorder sequence:\n") ;

	len = strlen(argv[1]);

	bitree_init(&root);
	bitree_inpost_create(&root, argv[1], argv[2], len);

	printf("The binary tree is:\n");
	bitree_to_glist(root, show_char);
	printf("\n");

	bitree_destroy(&root);

	return EXIT_SUCCESS;
}
