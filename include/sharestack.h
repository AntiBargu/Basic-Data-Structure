#ifndef _SHARESTACK_H
#define _SHARESTACK_H

#include "common.h"

#define SHARE_STACK_INIT_SIZE	(5)

typedef struct {
	void *data;
	int top[2];
}share_stack;

extern status sharestack_init(share_stack *stack, int size);
extern status sharestack_destory(share_stack *stack);
extern status sharestack_clear(share_stack *stack, int num);

extern status sharestack_empty(share_stack stack, int num);
extern int sharestack_length(share_stack stack, int num);

extern status sharestack_get_top(share_stack stack, int num,
			int size, void **e);
extern status sharestack_push(share_stack *stack, int num,
			int size, void *e);
extern status sharestack_pop(share_stack *stack, int num,
			int size, void *e);

extern status sharestack_traverse(share_stack stack, int num,
			int size, void (*visit)(void *));

#endif	/* _SHARESTACK_H */
