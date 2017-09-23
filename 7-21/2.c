#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	char str[]="abc/sada/sds";
	char* p=str;
	while(*++p);
	while(*--p!='/');
	*p='\0';
	printf("%s\n",str);
}
