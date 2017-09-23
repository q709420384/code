#include<iostream>
using namespace std;
#include"queue.h"

int main()
{
	int i;
	queue q;
	init_queue(&q);
	for(i=0;i<10;i++)
	{
		push(&q,i);
	}
	show_queue(&q);
	pop(&q);
	pop(&q);
	cout<<"head="<<gethead(&q)<<endl;
}
