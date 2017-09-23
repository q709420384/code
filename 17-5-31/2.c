#include<stdio.h>

typedef struct student
{
	char num[5];
	char name[20];
	char score[10];
}INFOR;
int main()
{
	int i;
	char str[256]={0};
	INFOR st[5]={"1001","lili","85","2002","qiqi","67","3003","wuwu","78","4004","ququ","68","5005","sisi","89"};
	FILE *fp=fopen("test.txt","w+");
	if(fp==NULL)
	{
		printf("打开文件失败\n");
		return -1;
	}
	for(i=0;i<5;i++)
	{
		fprintf(fp,"%s %s %s\n",st[i].num,st[i].name,st[i].score);
	}
	rewind(fp);
	//fgets(str,18,fp);
	char ch[256];
	while(fgets(str,256,fp))
	{
		fputs(str,stdout);
	
	}


	fclose(fp);
}
