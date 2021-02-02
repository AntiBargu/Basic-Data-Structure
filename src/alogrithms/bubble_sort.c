#include "exchange.h"

void bubble_sort(void *seq, int len, int size,
			int	(*rules)(void *, void *))
{
	int i, j;

	for(i = 0; i < len - 1; ++i) {
		for(j = i + 1; j < len; ++j) {
			if(!rules(seq + i * size, seq + j * size))
				exchange(seq + i *size, seq + j * size, size);
		}
	}
}

void bubble_sort_ex(void *seq, int len, int size,
			int (*rules)(void *, void *))
{
	int i, j, inverse_factor =  1;

	for(i = 0; i < len - 1 && !inverse_factor; ++i) {
		for(j = 0, inverse_factor = 0; j < len - 1 - i; ++j) {
			if(!rules(seq + j * size, seq + (j + 1) * size)) {
				exchange(seq + (j + 1) * size, seq + j * size, size);
				inverse_factor = 1;
			}
		}
	}
}
