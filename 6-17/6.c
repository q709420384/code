#include<stdio.h>
#include<string.h>
int main()
{
	char str[100][21];
	int num=0,i,d;
	while(scanf("%s",str[num++])!=EOF);
	for(i=0;i<num;i++)
	{
		if(i<num)
		{
			d=strlen(str[i])+strlen(str[i+1]);
			if(d<=20)
			{
				printf("%-*s%s\n",20-d,str[i],str[i+1]);
				i++;
			}
			if(d>20)
				printf("%s\n",str[i]);
		}
		else
			printf("%s",str[i]);
	}
}
