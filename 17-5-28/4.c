#include<stdio.h>

char *f()
{
	char str[]="welcome to 2+2!!!";
	return str;
}
int main()
{
	char* p;
	p=f();
	puts(p);
}
