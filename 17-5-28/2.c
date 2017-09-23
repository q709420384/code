#include<stdio.h>
#include<string.h>

void fun(int a[3][4])
{
	printf("%d\n",sizeof(a));
}
void main()
{
	int a[3][4];
	char str1[]={'h','e','l','l','o'};
	char* str2="hello";
	printf("%d %d\n",strlen(str1),sizeof(str2));   //sizeof(str1)=5;
	printf("%d %d\n",strlen(str2),sizeof(str2));
	printf("%d\n",sizeof(a));
	fun(a);
}
