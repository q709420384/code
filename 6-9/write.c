#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
typedef struct student
{
	char num[15];
	char name[15];
	char score[4];	
}stu;

int main()
{
	FILE* fp=fopen("student","wt");
	assert(fp!=NULL);
	stu a;
	scanf("%s %s %s",a.num,a.name,a.score);
	fwrite(&a,sizeof(a),1,fp);
	fclose(fp);
}
