#include<stdio.h>
#include<math.h>
int sushu(int n)
{
	int i,f=1;
	for(i=2;i<=sqrt(n);i++)
	{
		if(n%i==0)
			f=0;
	}
	return f;
}
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
	int n,x,f1,f2;
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d",&x);
		f1=sushu(x);
		f2=sushu(dao(x));
		if(f1==1&&f2==1)
			printf("%d是可逆素数\n",x);
		else if(f1==1&&f2!=1)
			printf("%d是素数，但不是可逆素数\n",x);
		else
			printf("%d不是素数\n",x);	
	}
}

