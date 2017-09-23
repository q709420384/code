#include<stdio.h>

int main()
{
	int a[10]={23,34,12,5,13,43,27,34,65,78};
	int i,j,t;
	for(i=0;i<9;i++)
		for(j=0;j<9-i;j++)
		{
			if(a[j]>a[j+1])
			{
				t=a[j];
				a[j]=a[j+1];
				a[j+1]=t;
			}	
		}
	for
}
