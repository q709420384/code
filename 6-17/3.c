#include<stdio.h>
#include<math.h>
int main()
{
	int w,m,n,rm,rn,cm,cn,d;
	scanf("%d %d %d",&w,&m,&n);
	rm=m/w;
	rn=n/w;
	if((m/w)%2==0)
		cm=(m-1)%w;
	else
		cm=w-1-(m-1)%w;
	if((n/w)%2==0)
		cn=(n-1)%w;
	else
		cn=w-1-(n-1)%w;
	d=abs(rm-rn)+abs(cm-cn);
	printf("%d",d);

	
}
