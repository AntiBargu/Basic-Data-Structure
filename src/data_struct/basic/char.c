#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "generic_type.h"

static unsigned int times = 0;

void char_get_rand_elem(void *ptr)
{
	char min_val;

	srand(time(NULL) + times++);

	min_val = rand() % 2 ? 'A' : 'a';

	*(char *)ptr = rand() % CHAR_RANGE_VALUE + min_val;

}

void char_get_stdin_elem(void *ptr)
{
	do {
		*(char *)ptr = getchar();
	}while(*(char *)ptr == '\n');
}

void char_show_elem(void *ptr)
{
	printf("%c ", *(char *)ptr);
}

/***** Compare rules *****/
status char_equal(void *a, void *b)
{
	return *(char *)a == *(char *)b;
}

status char_more_than(void *a, void *b)
{
	return *(char *)a >= *(char *)b;
}

status char_less_than(void *a, void *b)
{
	return *(char *)a <= *(char *)b;
}
