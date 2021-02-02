#include <stdio.h>
#include <stdlib.h>

#include "sqstack.h"

/* 
 * Simulate the Stack-Frame of system.
 * Push Stack-Frame into Stack-Space while calling function.
 * Pop Stack-Frame from Stack-Space while function returns.
 **/
typedef struct {
	int *sum;
	int x;
}stack_frame;


#if 0
void test(int *sum)
{
	int x;

	scanf("%d", &x);
	
	if(0 == x)
		*sum = 0;
	else {
		test(sum);
		*sum += x;
	}
	
	printf("%d ", *sum);

}
#else
void test(int *sum)
{
	sq_stack stack;
	stack_frame frame;
	int selem_size = sizeof(stack_frame);

	sqstack_init(&stack, selem_size);

	do{
		scanf("%d", &frame.x);
		frame.sum = sum;

		if(0 == frame.x)
			*frame.sum = 0;

		sqstack_push(&stack, selem_size, &frame);
	}while(0 != frame.x);

	while(!sqstack_empty(stack)) {
		sqstack_pop(&stack, selem_size, &frame);

		*frame.sum += frame.x;

		printf("%d ", *frame.sum);
	}
	
	sqstack_destroy(&stack);
}
#endif

int main(int argc, char *argv[])
{
	int sum;

	printf("[stack - Test 5] Convert Recurse To Non-Recurse 1 :\n");

	test(&sum);

	printf("\n");

	return EXIT_SUCCESS;
}
