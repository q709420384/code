#include<stdio.h>

int main()
{
	int n=1,a,b,c;
	scanf("%d %d %d",&a,&b,&c);
	while(1)
	{
		if((n%a==0)&&(n%b==0)&&(n%c==0))
		{	
			printf("%d",n);
			break;
		}
		n++;
	}
}
