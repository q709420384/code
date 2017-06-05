#include<iostream>
using namespace std;
#include<assert.h>
#define ElemType int
#define STACK_SIZE 100

typedef struct stack
{
	ElemType *base;
	size_t    capacity;
	int       top;
}stack;

void init_stack(stack *pst)
{
	pst->base = (ElemType *)malloc(sizeof(ElemType) * STACK_SIZE);
	assert(pst->base != NULL);
	pst->capacity = STACK_SIZE;
	pst->top = 0;
}
void push(stack *pst, ElemType x)
{
	if(pst->top >= pst->capacity)
	{
		cout<<"栈已满，"<<x<<"不能入栈"<<endl;
		return;
	}
	pst->base[pst->top++] = x;
}
void pop(stack *pst)
{
	if(pst->top == 0)
	{
		cout<<"栈已空，不能出栈."<<endl;
		return;
	}
	pst->top--;
}
ElemType gettop(stack *pst)
{
	assert(pst->top != 0);
	return pst->base[pst->top-1];
}
bool empty(stack *pst)
{
	return pst->top == 0;
}
void Convert_2(int value)
{
	stack st;
	init_stack(&st);
	while(value)
	{
		push(&st, value%2);
		value /= 2;
	}
	while(!empty(&st))
	{
		cout<<gettop(&st);
		pop(&st);
	}
	cout<<endl;
}

char* Convert_16(int value)
{
	static char buffer[sizeof(int)*2+1]; // char *pc = malloc();
	for(int i=sizeof(int)*2-1; i>=0; --i)
	{
		buffer[i] = "0123456789ABCDEF"[value%16];
		value /= 16;
	}
	return buffer;
}

int main()
{
	int value;
	cout<<"input value:>";
	cin>>value;
	cout<<value<<":二进制=";
	Convert_2(value);
	cout<<value<<":十六进制=0x";
	cout<<Convert_16(value)<<endl;
}


