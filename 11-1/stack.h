#pragma once
#include<iostream>
using namespace std;
#define STACK_SIZE 100
#define Type BinTreeNode*
typedef struct stack
{
	Type* base;
	size_t capacity;
	int top;
}stack;

void init_stack(stack *pst)
{
	pst->base = (Type*)malloc(sizeof(Type)*STACK_SIZE);
	assert(pst->base != NULL);
	pst->capacity = STACK_SIZE;
	pst->top = 0;
}
void push(stack *pst, Type x)
{
	if(pst->top >= pst->capacity)
	{
		cout<<"栈已满，"<<x<<"不能入栈"<<endl;
		return;
	}
	pst->base[pst->top++] = x;
}
Type gettop(stack *pst)
{
	assert(pst != NULL);
	return pst->base[pst->top-1];
} 
void pop(stack* pst)
{
	if(pst->top == 0)
	{
		cout<<"栈已空，不能出栈"<<endl;
		return;
	}
	pst->top--;
}
bool isempty(stack *pst)
{
	return pst->top == 0;
}
void destroy(stack *pst)
{
	free(pst->base);
}
