#ifndef _SQQUEUE_H
#define _SQQUEUE_H

#include "common.h"

typedef struct {
	void *data;
	int front, rear;
}sq_queue;

extern status sqqueue_init(sq_queue *queue, int size);
extern status sqqueue_destroy(sq_queue *queue);

extern status sqqueue_clear(sq_queue *queue);
extern status sqqueue_empty(sq_queue queue);
extern int sqqueue_length(sq_queue queue);

extern status sqqueue_get_head(sq_queue queue, int size, void *e);
extern status sqqueue_enque(sq_queue *queue, int size, void *e);
extern status sqqueue_deque(sq_queue *queue, int size, void *e);
extern status sqqueue_traverse(sq_queue queue, int size, 
			void (*visit)(void *));

#endif /* _SQQUEUE_H */
