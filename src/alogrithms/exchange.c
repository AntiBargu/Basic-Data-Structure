void exchange(void *a, void *b, int size)
{
	char tmp;
	
	while(size--) {
		tmp = *(char *)a;
		*(char *)a = *(char *)b;
		*(char *)b = tmp;

		++a;
		++b;
	}
}

void exchange_ex(void *a, void *b, int size)
{
	while(size--) {
		*(char *)a = *(char *)a ^ *(char *)b;
		*(char *)b = *(char *)a ^ *(char *)b;
		*(char *)a = *(char *)a ^ *(char *)b;
		
		++a;
		++b;
	}
}

