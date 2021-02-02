#include <stdlib.h>
#include <string.h>
#include <errno.h>

static int partition(void *seq, int low, int high, int size,
			int (*rules)(void *, void *));

static void _quick_sort(void *seq, int low, int high, int size,
			int (*rules)(void *, void *));

static int partition(void *seq, int low, int high, int size,
			int (*rules)(void *, void *))
{
	void *pivotkey;
	
	if(!(pivotkey = malloc(size)))
		exit(ENOMEM);

	memcpy(pivotkey, seq + low * size, size);

	while(low < high) {
		while(low < high && rules(pivotkey, seq + high * size))
			--high;

		memcpy(seq + low * size, seq + high * size, size);
	
		while(low < high && rules(seq + low * size, pivotkey))
			++low;

		memcpy(seq + high * size, seq + low * size, size);
	}
	
	memcpy(seq + low * size, pivotkey, size);

	free(pivotkey);

	return low;
}

static void _quick_sort(void *seq, int low, int high, int size,
			int (*rules)(void *, void *))
{
	int mid;

	if(low < high) {
		mid = partition(seq, low, high, size, rules);
		_quick_sort(seq, low, mid - 1, size, rules);
		_quick_sort(seq, mid + 1, high, size, rules);
	}

}

void quick_sort(void *seq, int len, int size,
			int (*rules)(void *, void *))
{
	if(len <= 0)
		return ;

	_quick_sort(seq, 0, len - 1, size, rules);
}

