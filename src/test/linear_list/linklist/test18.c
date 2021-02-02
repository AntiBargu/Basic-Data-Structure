#include <stdio.h>
#include <stdlib.h>

#include "dulinklist.h"
#include "generic_type.h"

typedef struct {
	int data;
	int freq;
}info_st;


static void get_struct_info(void *ptr);
static void show_struct_info(void *ptr);

static status frequency_increasing(int freq_a, int freq_b);

#if 0
static status frequency_decreasing(int freq_a, int freq_b);
#endif

static dulinklist dulinklist_locate_ex(dulinklist list, int x,
			status (*freq_order)(int, int));

void get_struct_info(void *ptr)
{
	scanf("%d", &((info_st *)ptr)->data);
	((info_st *)ptr)->freq = 0;
}

void show_struct_info(void *ptr)
{
	printf("(%d, %d) ", ((info_st *)ptr)->data, ((info_st *)ptr)->freq);
}

status frequency_increasing(int freq_a, int freq_b)
{
	return freq_a <= freq_b;
}

status frequency_decreasing(int freq_a, int freq_b)
{
	return freq_a >= freq_b;
}

dulinklist dulinklist_locate_ex(dulinklist list, int x,
			status (*freq_order)(int, int))
{
	dulinklist p, prev;

	for(p = list->next; p; p = p->next) {
		if(x == ((info_st *)p->data)->data)
			break;
	}
	
	if(p) {
		++((info_st *)p->data)->freq;

		for(prev = p->prev; 
				prev != list && freq_order(((info_st *)prev->data)->freq, ((info_st *)p->data)->freq);	
				prev = prev->prev)
			;
		
		/* delete p */
		p->prev->next = p->next;
		if(p->next)
			p->next->prev = p->prev;

		/* insert p */
		p->next = prev->next;
		p->prev = prev;

		prev->next->prev = p;
		prev->next = p;
	}

	return p;
}

int main(int argc, char *argv[])
{
	/* For generic type conversion */
	int elem_size = sizeof(info_st);
	void (*get_elem)(void *) = get_struct_info;
	void (*show_elem)(void *) = show_struct_info;

	int i, x;
	dulinklist list;

	dulinklist_init(&list);

	printf("[linklist - Test 18] Double-Linklist Access Frequency:\n");
	
	printf("Insert the elements of the list:\n");
	dulinklist_tail_create(list, 10, elem_size, get_elem);
	dulinklist_traverse(list, show_elem);

	for(i = 0; i < 10; ++i) {
		printf("Please insert x:\n");
		scanf("%d", &x);

		dulinklist_locate_ex(list, x, frequency_increasing);
		dulinklist_traverse(list, show_elem);
	}	
	
	dulinklist_destroy(&list);

	return EXIT_SUCCESS;
}
