#include<iostream>
using namespace std;
#include<assert.h>
#define SIZE 100
typedef struct stack
{
	int size;
	char* arr;
	int top;
}stack;
void init(stack* p)
{
	p->size=SIZE;
	p->arr=(char*)malloc(SIZE);
	p->top=0;
}
void push(stack* p,char c)
{
	assert(p->top!=p->size);
	p->arr[p->top++]=c;
}
void pop(stack* p)
{
	assert(p->top!=0);
	p->top--;
}
void gettop(stack* p)
{
	cout<<p->arr[p->top]<<endl;
}
void input(stack* p)
{
	char arr[SIZE];
	scanf("%s",arr);
	char* ptr=arr;
	while(*ptr!='\0')
	{
		push(p,*ptr++);
	}
}
void show(const stack* p)
{
	assert(p->top!=0);
	int i=p->top-1;
	for(;i>=0;i--)
		cout<<p->arr[i]<<" ";
	cout<<endl;
}
int main()
{
	stack p;
	init(&p);
	input(&p);
	show(&p);
}
