#ifndef _SQSTACK_H
#define _SQSTACK_H

#include "common.h"

#define STACK_INIT_SIZE	(100)

typedef struct {
	void *base, *top;
	int size;
}sq_stack;


extern status sqstack_init(sq_stack *stack, int size);
extern status sqstack_destroy(sq_stack *stack);

extern status sqstack_clear(sq_stack *stack);
extern status sqstack_empty(sq_stack stack);
extern int sqstack_length(sq_stack stack, int size);

extern status sqstack_get_top(sq_stack stack, int size, void *e);

extern status sqstack_push(sq_stack *stack, int size, void *e);
extern status sqstack_pop(sq_stack *stack, int size, void *e);

extern status sqstack_traverse(sq_stack stack, int size, void (*visit)(void *));

#endif	/*_SQSTACK_H */
