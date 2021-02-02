#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "generic_type.h"

static unsigned int times = 0;

/***** Get elements method *****/
void int_get_rand_elem(void *ptr)
{
	srand(time(NULL) + times++);
	
	*(int *)ptr = rand() % INT_RANGE_VALUE + INT_MIN_VALUE;
}

void int_get_stdin_elem(void *ptr)
{
	scanf("%d", (int *)ptr);
}

/***** Put elements method *****/
void int_show_elem(void *ptr)
{
	printf("%d ", *(int *)ptr);
}

/***** Compare rules *****/
status int_equal(void *a, void *b)
{
	return *(int *)a == *(int *)b;
}

status int_more_than(void *a, void *b)
{
	return *(int *)a >= *(int *)b;
}

status int_less_than(void *a, void *b)
{
	return *(int *)a <= *(int *)b;
}

/*
 * Write for the interview of Continental AG which my friend was invited,
 * 	and this function is just a compare rules.
 *
 * The question is :
 * 	Sort an array of numbers, 
 * 	that the odds are in the front and they are increasing,
 * 	the evens are in the posterior and they are decreasing.
 *
 **/
status int_odd_up_even_down(void *a, void *b)
{
	if((*(int *)a ^ *(int *)b) & 1)
		return 1 == (*(int *)a & 1);

	return 1 == (*(int *)a & 1) ? 
					*(int *)a < *(int *)b : *(int *)a > *(int *)b;
}

/***** Compare rules *****/
status is_even(void *ptr)
{
	return !(*(int *)ptr & 1);
}

status is_odd(void *ptr)
{
	return *(int *)ptr & 1;
}
