#include<stdio.h>
#include<math.h>
int dao(int n)
{
	int arr[10],i=0,t,sum=0,j;
        while(n)
        {
                arr[i++]=n%10;
                n/=10;
        }
        t=i-1;
        for(j=0;j<i;j++)
        {
                sum+=arr[j]*pow(10,t--);
        }
        return sum;
}

int main()
{
	int n=3,x;
	while(n--)
	{
		scanf("%d",&x);
		printf("%d\n",dao(x));
	}
}
