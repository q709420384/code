#include<stdio.h>

typedef struct MY_TYPE
{
	short a;
	int b;
	char* c[4];
}MY;
typedef union YOUR_TYPE
{
	int a;
	char* b[4];
	double c;
}YOUR;
int main()
{
	MY* my;
	printf("%d %d %d\n",sizeof(MY),sizeof(YOUR),sizeof(my));
}
