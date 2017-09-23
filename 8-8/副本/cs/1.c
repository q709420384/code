#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<signal.h>
int main()
{
	char str[15];
	signal(SIGINT,SIG_IGN);
	while(1)
	{
		gets(str);
		puts(str);
	}
}
