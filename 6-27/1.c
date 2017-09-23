#include<stdio.h>

void fun(int n)
{
	//int i=n;
	//i--;
	if(n==0)
		return;
	fun(n-1);
	printf("%d\n",n);
}
int main()
{
	fun(10);
	fun(20);
}
