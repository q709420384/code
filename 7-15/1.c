#include<stdio.h>

int main()
{
	int a[10]={23,34,12,5,13,43,27,34,65,78};
	int* p,*q,i,j,t;
	p=q=a;
	for(p=a;p<a+9;p++)
	{
		for(q=a;q<a+9-p;q++)
		{
			if(*(q)>*(q+1))
			{
				t=*q;
				*q=*p;
				*p=t;
			}
		}
	}
	for(i=0;i<10;i++)
		printf("%d ",a[i]);
	printf("\n");
}
