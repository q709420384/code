#include<stdio.h>

int main()
{
	char str[]="welcome to 2+2!";
	char *p=str;
	while(*p!='\0')
	{
		if(*p==' ')
			printf("%20");
		else
			printf("%c",*p);
		p++;
	}
	printf("\n");
}
