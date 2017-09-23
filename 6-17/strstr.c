#include<stdio.h>
#include<stdlib.h>

int strlen(char* p)
{
	if(*p=='\0')
		return 0;
	return 1+strlen(*(p+1));
}
int main()
{
	char str1[100],str2[100];
	scanf("%s %s",str1,str2);
	int len1=strlen(str1);
	int len2=strlen(str2);
	printf("%d %d",len1,len2);
	
}
