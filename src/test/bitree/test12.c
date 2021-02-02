#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "bitree.h"
#include "sqqueue.h"
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

/* Simulation condition functions. */
status int_bitree_cond(void *ptr)
{
	int range = 50;

	return int_more_than(ptr, &range);
}

status char_bitree_cond(void *ptr)
{
	char range = 'a';
		
	return char_more_than(ptr, &range);
}

static void bitree_levelorder_cond_print(bitree root,
			status (*cond)(void *))
{
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	bitree ptr;
	sq_queue queue;
	int last_pos = 0, num = 1, qelem_size = sizeof(bitree);
	
	if(!root)
		return ;

	sqqueue_init(&queue, qelem_size);	
	sqqueue_enque(&queue, qelem_size, &root);

	while(!sqqueue_empty(queue)) {
		sqqueue_deque(&queue, qelem_size, &ptr);
	
		if(cond(ptr->data)) {
			printf("[%d]", num);
			show_elem(ptr->data);
		}
		
		++num;

		if(ptr->lchild)
			sqqueue_enque(&queue, qelem_size, &ptr->lchild);

		if(ptr->rchild)
			sqqueue_enque(&queue, qelem_size, &ptr->rchild);

		if(queue.front > last_pos) {
			printf("\n");

			num = 1;
			last_pos = queue.rear - 1;
		}
	}

	sqqueue_destroy(&queue);
}

int main(int argc, char *argv[])
{
	/* For generic type conversion */
	int elem_size = TYPE_SIZE;
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	bitree root;

	printf("[bitree - Test 12] Bitree Condition Print:\n") ;

	get_terminator(elem_size);

	bitree_init(&root);
	bitree_levelorder_create(&root, elem_size, bitree_get_data);

	printf("Print the bitree in the Gener-List way:\n");
	bitree_to_glist(root, show_elem);
	printf("\n");

	bitree_levelorder_cond_print(root, TYPE_FUNC(bitree_cond));

	bitree_destroy(&root);

	return EXIT_SUCCESS;
}
