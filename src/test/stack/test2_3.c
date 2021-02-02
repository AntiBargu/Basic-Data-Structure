#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "sqstack.h"

#define TERMINATOR	'\0'


static status judge_expression(const char *str);

status judge_expression(const char *str)
{
	int elem, map;
	sq_stack stack;
	status rslt = OK;
	int elem_size = sizeof(int);

	sqstack_init(&stack, elem_size);

	for( ; *str != TERMINATOR && rslt; ++str) {
		map = 0;

		switch(*str) {
			case '(' : ++map;
			case '[' : ++map;
			case '{' : ++map;
				if(!sqstack_push(&stack, elem_size, &map)) 
					rslt = ERROR;
				break;
		
			case ')' : ++map;
			case ']' : ++map;
			case '}' : ++map;
				if(!sqstack_pop(&stack, elem_size, &elem) || map != elem) 
					rslt = ERROR;
				break;
		}
	}

	if(!sqstack_empty(stack))
		rslt = ERROR;

	sqstack_destroy(&stack);

	return rslt;
}

int main(int argc, char *argv[])
{
	if(argc < 2) {
		fprintf(stderr, "Usage: %s [string]\n", argv[0]);
		exit(EINVAL);
	}

	printf("[stack - Test 2/3] Judge Whether The Expression is Legal :\n");

	printf("This %s a Legal Expression.\n", 
		judge_expression(argv[1]) ? "is" : "isn't");

	return EXIT_SUCCESS;
}
