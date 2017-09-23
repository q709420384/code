#pragma once		

#define ElemType int
#define DEFAULT_QUEUE_SIZE  10

typedef struct queue
{
	ElemType *base;
	int capacity;
	int front;
	int rear;
}queue;
		
void init_queue(queue *q);

void push(queue *q, ElemType x);

void pop(queue *q);

ElemType gethead(queue *q);

void show_queue(queue *q);

