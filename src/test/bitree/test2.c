#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "bitree.h"


static char *terminator;

status get_from_argument(void *ptr)
{
	status rslt = TRUE;

	if(*terminator)
		*(char *)ptr = *terminator++;
	else
		rslt = FALSE;

	return rslt;
}

void show_char(void *ptr)
{
	printf("%c", *(char *)ptr);
}

/*
 * In this test, 
 *  we create a binary tree through the string which @argv[1] takes,
 *	each element of the binary tree is a char.
 **/
int main(int argc, char *argv[])
{
	bitree root;

	printf("[bitree - Test 2] Create a Complete Bitree Base on Array:\n") ;
	
	if(argc < 2) {
		fprintf(stderr, "Usage: %s [string]\n", argv[0]);
		exit(EINVAL);
	}

	terminator = argv[1];
	
	bitree_init(&root);
	bitree_levelorder_create(&root, 1,
		get_from_argument);

	printf("The binary tree is:\n");
	bitree_to_glist(root, show_char);
	printf("\n");

	bitree_destroy(&root);

	return EXIT_SUCCESS;
}
