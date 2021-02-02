#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sqqueue.h"

#define QUEUE_INIT_SIZE	(100)

status sqqueue_init(sq_queue *queue, int size)
{
	if(!(queue->data = malloc(QUEUE_INIT_SIZE * size)))
		return OVERFLOW;

	queue->front = queue->rear = 0;

	return OK;
}

status sqqueue_destroy(sq_queue *queue)
{
	if(!queue || !queue->data)
		return ERROR;

	free(queue->data);

	queue->data = NULL;
	queue->front = queue->rear = 0;

	return OK;
}

status sqqueue_clear(sq_queue *queue)
{
	if(!queue || !queue->data)
		return ERROR;

	queue->rear = queue->front;

	return OK;
}

status sqqueue_empty(sq_queue queue)
{
	return queue.rear == queue.front;
}

int sqqueue_length(sq_queue queue)
{
	return (queue.rear - queue.front + QUEUE_INIT_SIZE) 
				% QUEUE_INIT_SIZE;
}

status sqqueue_get_head(sq_queue queue, int size, void *e)
{
	if(!queue.data || queue.front == queue.rear)
		return ERROR;

	memcpy(e, queue.data + queue.front * size, size);

	return OK;
}

/* @e is the memory address of the inserted element. */
status sqqueue_enque(sq_queue *queue, int size, void *e)
{
	if((queue->rear + 1) % QUEUE_INIT_SIZE == queue->front)
		return ERROR;

	memcpy(queue->data + queue->rear * size, e, size);
	queue->rear = (queue->rear + 1) % QUEUE_INIT_SIZE;

	return OK;
}

status sqqueue_deque(sq_queue *queue, int size, void *e)
{
	if(sqqueue_empty(*queue))
		return ERROR;

	memcpy(e, queue->data + queue->front * size, size);
	queue->front = (queue->front + 1) % QUEUE_INIT_SIZE;
	
	return OK;
}

status sqqueue_traverse(sq_queue queue, int size, 
			void (*visit)(void *))
{
	int i;

	if(!queue.data)
		return ERROR;

	for(i = queue.front; i !=  queue.rear; 
			i = (i + 1) % QUEUE_INIT_SIZE)
		visit(queue.data + i * size);

	return OK;
}
