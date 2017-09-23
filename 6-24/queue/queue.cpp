#include<iostream>
using namespace std;
#include"queue.h"
#include"assert.h"
void init_queue(queue *q)
{
	q->base = (ElemType *)malloc(sizeof(ElemType) * DEFAULT_QUEUE_SIZE);
	assert(q->base != NULL);
	q->capacity = DEFAULT_QUEUE_SIZE;
	q->front = q->rear = 0;
}

void push(queue *q, ElemType x)
{
	if((q->rear+1)%q->capacity == q->front)
	{
		cout<<"队列已满,"<<x<<"不能入队."<<endl;
		return;
	}
	q->base[q->rear++] = x;
	q->rear = q->rear % q->capacity;
}
void pop(queue *q)
{
	if(q->front == q->rear)
		return;
	q->front++;
	q->front = q->front % q->capacity;
}
ElemType gethead(queue *q)
{
	assert(q->front != q->rear);
	return q->base[q->front];
}
void show_queue(queue *q)
{
	for(int i=q->front; i!=q->rear; )
	{
		cout<<q->base[i]<<" ";
		i++;
		i = i%q->capacity;
	}
	cout<<endl;
}
