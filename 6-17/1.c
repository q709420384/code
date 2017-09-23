#include<stdio.h>

int main()
{
	int n,x,y;
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d %d",&x,&y);
		int i=0,sum=0;
		while(sum<x)
		{
			i++;
			sum+=i;
		}
		if(sum!=x)
			printf("NONE\n");
		else
		{
			int j,k,f=1;
			for(j=1;j<i;j++)
				for(k=j+1;k<=i;k++)
				{
					if((x-j-k-2+j*j+k*k)==y)
					{
						printf("(%d,%d)",j,k);
						f=0;
					}
						
				}
			if(f)
				printf("NONE\n");
			else
				printf("\n");
		}
	}
}
