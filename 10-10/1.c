/*************************************************************************
> File Name: 1.c
> Author:Sanjingye 
> Mail: 
> Created Time: 2017年10月10日 星期二 17时26分33秒
************************************************************************/

typedef int ElemType; 
typedef struct Queue 
{ ElemType data; 
 struct Queue *rear; 
 struct Queue length; 
}Queue; /* 将data入循环队列 */ 
void EnQueue(Queue *Q, ElemType data) 
{ if((Q->rear+1)%MAX == (Q->rear-Q->length+MAX)%MAX) 
 return; 
 Q->base[Q->rear] = data; 
 Q->rear = (Q->rear+1)%MAX; Q->length++; 
} /* 出队列，结果存*data中 */ 
void DeQueue(Queue *Q, ElemType *data) 
{ if(Q->rear == (Q->rear-Q->length+MAX)%MAX) 
 return; 
 *data = Q->base[(Q->rear-Q->length+MAX)%MAX]; 
 Q->length--; 
}

