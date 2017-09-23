#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

int main()
{
	char path[256];
	int len;
	printf("路径:");
	gets(path);
	FILE* fp1=fopen(path,"r");
	FILE* fp2=fopen("test","w");
	assert(fp1!=NULL);
	char buf[1024];
	while((len=fread(buf,1,1024,fp1))>0)
	{
		fwrite(buf,1,len,fp2);
	}
	printf("end\n");
	fclose(fp1);
	fclose(fp2);
}
