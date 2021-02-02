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

/* 
 * Link the leaves by their @rchild,
 *  and return the leftmost leaf of @root.
 * */
bitree bitree_link_leaves(bitree root)
{
	bitree left, right, p;

	if(!root->lchild && !root->rchild)
		return root;

	if(root->rchild)
		right = bitree_link_leaves(root->rchild);

	if(root->lchild)
		left  = bitree_link_leaves(root->lchild);

	for(p = left; p->rchild; p = p->rchild)
		;

	p->rchild = right;

	return left;
}

int main(int argc, char *argv[])
{
	int elem_size = TYPE_SIZE;
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	bitree root, leftmost;

	printf("[bitree - Test 16] Link Bitree's Leaves:\n") ;

	get_terminator(elem_size);

	bitree_init(&root);
	bitree_levelorder_create(&root, elem_size, bitree_get_data);

	printf("The binary tree is:\n");
	bitree_to_glist(root, show_elem);
	printf("\n");

	leftmost = bitree_link_leaves(root);
	
	printf("The leaves linklist:\n");
	bitree_to_glist(leftmost, show_elem);
	printf("\n");

	/* 
	 * Original node structure has been destroyed,
	 * 	@root can't be destoryed. 
	 **/
/* 	bitree_destroy(&root); */

	return EXIT_SUCCESS;
}
