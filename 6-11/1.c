#include<stdio.h>
typedef struct student
{
	char num[10];
	char name[20];
	int score;
}stu;
int main()
{
	FILE* fp=fopen("data.txt","wb");
	stu st={"04163014","lijiahao",89};
	printf("%s %s %d",st.num,st.name,st.score);
	fwrite(&st,sizeof(stu),1,fp);
	fclose(fp);
}	
