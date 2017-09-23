#ifndef QUEUE_H
#define QUEUE_H
#include"Tree.h"
#define ElemTypeB BinTreeNode*
typedef struct queue
{
	ElemTypeB *base;
	int capacity;
	int front;
	int rear;
}queue;

void init_queue(queue* q);

void push(queue* q,ElemTypeB x);

void pop(queue* q);

int Emptyqueue(queue* q);

ElemTypeB Getfront(queue* q);

#endif
