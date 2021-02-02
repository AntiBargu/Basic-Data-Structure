#ifndef _STRUCT_H
#define _STRUCT_H

struct node{
	void *data;
	int freq;
};

extern void get_rand_elem(struct node *elem);
extern void get_stdin_elem(struct node *elem);

extern void show_elem(struct node n);

extern status more_than(struct node a, struct node b);
extern status equal_to(struct node a, struct node b);
extern status less_than(struct node a, struct node b);

#endif	/* _STRUCT_H */
