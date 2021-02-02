#ifndef _GENERIC_TYPE_H
#define _GENERIC_TYPE_H

#include "common.h"

#define CHAR_TYPE

/***** Integer Defintion *****/
#ifdef INT_TYPE
#define TYPE_FUNC(func) int_##func
#define TYPE_SIZE (sizeof(int))
#endif

#define INT_MAX_VALUE	(100)
#define INT_MIN_VALUE 	(0)
#define INT_RANGE_VALUE	(INT_MAX_VALUE - INT_MIN_VALUE)

/***** Char Defintion *****/
#ifdef CHAR_TYPE
#define TYPE_FUNC(func) char_##func
#define TYPE_SIZE (sizeof(char))
#endif

#define CHAR_RANGE_VALUE	(26)


/***** Integer Functions *****/
extern void int_get_rand_elem(void *ptr);
extern void int_get_stdin_elem(void *ptr);

extern void int_show_elem(void *ptr);

extern status int_equal(void *a, void *b);
extern status int_more_than(void *a, void *b);
extern status int_less_than(void *a, void *b);
extern status int_odd_up_even_down(void *a, void *b);

/***** Char Functions *****/
extern void char_get_rand_elem(void *ptr);
extern void char_get_stdin_elem(void *ptr);

extern void char_show_elem(void *ptr);

extern status char_equal(void *a, void *b);
extern status char_more_than(void *a, void *b);
extern status char_less_than(void *a, void *b);

#endif	/* _GENERIC_TYPE_H */
