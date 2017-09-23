#include<stdio.h>
#define PSQR(x) printf("The square of "#x" is %d.\n",((x)*(x)))
int main()
{
	PSQR(5);
	PSQR(2+4);
}
