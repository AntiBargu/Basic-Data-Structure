#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sharestack.h"

status sharestack_init(share_stack *stack, int size)
{
	if(!(stack->data = malloc(size * SHARE_STACK_INIT_SIZE)))
		return OVERFLOW;

	stack->top[0] = 0;
	stack->top[1] = SHARE_STACK_INIT_SIZE - 1;

	return OK;
}

status sharestack_destroy(share_stack *stack)
{
	if(!stack || !stack->data)
		return ERROR;
	
	free(stack->data);

	stack->top[0] = stack->top[1] = 0;

	return OK;
}

status sharestack_clear(share_stack *stack, int num)
{
	if((num != 0 && num != 1) || (!stack || !stack->data))
		return ERROR;

	if(0 == num)
		stack->top[0] = 0;
	else
		stack->top[1] = SHARE_STACK_INIT_SIZE - 1;
	
	return OK;
}

status sharestack_empty(share_stack stack, int num)
{
	if((num != 0 && num != 1) || !stack.data)
		return ERROR;

	return 0 == num ? 
		0 == stack.top[0] : (SHARE_STACK_INIT_SIZE - 1) == stack.top[1];
}

int sharestack_length(share_stack stack, int num)
{
	if((num != 0 && num != 1) || !stack.data)
		return -1;

	return 0 == num ? 
		stack.top[0] : (SHARE_STACK_INIT_SIZE - 1) - stack.top[1];
}

status sharestack_get_top(share_stack stack, int num, int size, void **e)
{
	if((num != 0 && num != 1) || !stack.data)
		return ERROR;
	
	if(0 == num)
		*e = stack.data + (stack.top[0] - 1) * size;
	else
		*e = stack.data + (stack.top[1] + 1) * size;

	return OK;
}

status sharestack_push(share_stack *stack, int num, int size, void *e)
{
	if((num != 0 && num != 1) || (!stack || !stack->data))
		return ERROR;
	
	/* "Share-Stack" is full. */
	if(stack->top[0] - 1 == stack->top[1])
		return ERROR;

	memcpy(stack->data + stack->top[num] * size, e, size);

	0 == num ? ++stack->top[num] : --stack->top[num];

	return OK;
}

status sharestack_pop(share_stack *stack, int num, int size, void *e)
{
	if((num != 0 && num != 1) || (!stack || !stack->data))
		return ERROR;

	/* "Share-Stack" is empty. */
	if(sharestack_empty(*stack, num))
		return ERROR;

	0 == num ? --stack->top[num] : ++stack->top[num];
	memcpy(e, stack->data + stack->top[num], size);

	return OK;
}

status sharestack_traverse(share_stack stack, int num, int size,
			void (*visit)(void *))
{
	int i;

	if((num != 0 && num != 1) || !stack.data) 
		return ERROR;

	printf("Stack 0:\n");
	for(i = 0; i < stack.top[0]; ++i)
		visit(stack.data + i * size);
	printf("\n");

	printf("Stack 1:\n");
	for(i = SHARE_STACK_INIT_SIZE - 1; i > stack.top[1]; --i)
		visit(stack.data + i * size);
	printf("\n");

	return OK;
}
