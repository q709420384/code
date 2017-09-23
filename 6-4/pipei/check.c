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
	assert((p->arr=(char*)malloc(SIZE))!=NULL);
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
void input(stack* p)
{
	char arr[SIZE];
	cin>>arr;
	int i=0;
	p->arr[p->top++]=arr[i++];
	while(arr[i]!='\0')
	{
		if((arr[i]==')'&&p->arr[p->top-1]=='(')||(arr[i]==']'&&p->arr[p->top-1]=='['))
		{
			pop(p);
		}
		else
			push(p,arr[i]);
		i++;
	}	
}
int check(stack* p)
{
	if(p->top==0)
		cout<<"YES!"<<endl;
	else
		cout<<"NO!"<<endl;
}
int main()
{
	stack p;
	init(&p);
	input(&p);
	check(&p);
}
