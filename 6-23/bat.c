#include<stdio.h>

int ox(int n)
{
	int sum=0;
	while(n)
	{
		sum+=n%16;
		n=n/16;
	}
	return sum;
}
int main()
{
	int a,sum1=0,sum2=0,sum3=0;
	scanf("%d",&a);
	printf("%d\n",ox(a));
	
}
