#include<stdio.h>
typedef struct
{
	char num[10];
	char name[20];
	int score;
}stu;
int main()
{
	FILE* fp=fopen("data.txt","rb");
	stu st;
	fread(&st,sizeof(stu),1,fp);
	printf("%s %s %d\n",st.num,st.name,st.score);
}
