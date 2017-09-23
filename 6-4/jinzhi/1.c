#include<iostream>
using namespace std;


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
void main()
{
	int value;
	cout<<"input value:>";
	cin>>value;
	cout<<value<<":二进制=";
	Convert_2(value);
	cout<<value<<":十六进制=0x";
	cout<<Convert_16(value)<<endl;
}

