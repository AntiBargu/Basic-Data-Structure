#ifndef _LINKQUEUE_H
#define _LINKQUEUE_H

#include "common.h"

typedef struct qnode {
	void *data;
	struct qnode *next;
}qnode, *queue_ptr;

typedef struct {
	queue_ptr front, rear;
}linkqueue;

extern status linkqueue_init(linkqueue *queue);
extern status linkqueue_destory(linkqueue *queue);
extern status linkqueue_clear(linkqueue *queue);

extern status linkqueue_empty(linkqueue queue);
extern int linkqueue_length(linkqueue queue);

extern status linkqueue_get_head(linkqueue queue, void **e);

extern status linkqueue_enqueue(linkqueue *queue, void *e);
extern status linkqueue_dequeue(linkqueue *queue, void **e);

extern status linkqueue_traverse(linkqueue queue, 
			void (*visit)(void *));

#endif
