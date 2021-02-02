#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sqstack.h"


status sqstack_init(sq_stack *stack, int size)
{
	if(!(stack->base = malloc(STACK_INIT_SIZE * size)))
		return OVERFLOW;

	stack->top = stack->base;
	stack->size = STACK_INIT_SIZE;

	return OK;	
}

status sqstack_destroy(sq_stack *stack)
{
	if(!stack || !stack->base)
		return ERROR;
	
	free(stack->base);

	stack->top = stack->base = NULL;
	stack->size = 0;

	return OK;
}

status sqstack_clear(sq_stack *stack)
{
	if(!stack || !stack->base)
		return ERROR;

	stack->top = stack->base;

	return OK;
}

status sqstack_empty(sq_stack stack)
{
	return stack.base == stack.top;
}

int sqstack_length(sq_stack stack, int size)
{
	return (stack.top - stack.base) / size;
}

status sqstack_get_top(sq_stack stack, int size, void *e)
{
	if(!stack.base || stack.top == stack.base)
		return ERROR;

	memcpy(e, stack.top - size, size);

	return OK;
}

status sqstack_push(sq_stack *stack, int size, void *e)
{
	if(sqstack_length(*stack, size) >= stack->size)
		return ERROR;
	
	memcpy(stack->top, e, size);
	stack->top += size;

	return OK;
}

status sqstack_pop(sq_stack *stack, int size, void *e)
{
	if(sqstack_empty(*stack))
		return ERROR;

	stack->top -= size;
	memcpy(e, stack->top, size);

	return OK;
}

status sqstack_traverse(sq_stack stack, int size, void (*visit)(void *))
{
	void *p;

	if(!stack.base)
		return ERROR;

	for(p = stack.base; p < stack.top; p += size)
		visit(p);
	
	return OK;
}
