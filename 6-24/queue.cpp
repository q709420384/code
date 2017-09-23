#include<iostream>
using namespace std;
#include"queue.h"
#include"assert.h"
void init_queue(queue* q)
{
	q->base=(ElemTypeB*)malloc(sizeof(ElemTypeB)*10);
	assert(q->base!=NULL);
	q->capacity=10;
	q->front=q->rear=0;
}
void push(queue* q,ElemTypeB x)
{
	if((q->rear+1)%q->capacity==q->front)
	{
		cout<<"队列已满，无法入队"<<endl;
		return;
	}
	if(x)
	{
		q->base[q->rear++]=x;
		q->rear=q->rear%q->capacity;
	}
}
void pop(queue* q)
{
	if(q->front==q->rear)
	{
		cout<<"队列已空"<<endl;
		return;
	}
	cout<<(q->base[q->front++])->data<<" ";
	q->front%=q->capacity;
}
int Emptyqueue(queue* q)
{
	if(q->front==q->rear)
		return 1;
	return 0;
}
ElemTypeB Getfront(queue* q)
{
	return q->base[q->front];
}
