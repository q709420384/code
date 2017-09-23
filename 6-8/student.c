#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
typedef struct student
{
	char num[15];
	char name[20];
	int chinese;
	int math;
	int english;
	int average;
	struct student* next;
}stu;
typedef struct List
{
	int size;
	stu* head;
	stu* last;
}List;
stu* increase(List* list)
{
	stu* pnew=(stu*)malloc(sizeof(stu));
	assert(pnew!=NULL);
	printf("请输入学号,姓名，语文，英语，数学：");
	scanf("%s %s %d %d %d %d",pnew->num,pnew->name,&pnew->chinese,&pnew->math,&pnew->english);

}
int main()
{
	List list;
	memset(&list,0,sizeof(list));
	
}
