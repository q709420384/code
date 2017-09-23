#include<stdio.h>

char getch()
{
        char c;
        system("stty -echo");
        system("stty -icanon");
        c=getchar();
        system("stty icanon");
        system("stty echo");
        return c;
}
void inputpasswd(char* pass)
{
	printf("请输入加密密码:\n");
	int i=0;
	char ch;
	while(i<20&&(ch=getch(),ch!='\n'))
	{
		if(ch==127)
		{
			if(i>0)
			{
				i--;
				printf("\b \b");
			}
			else
				putchar(7);
		}
		else
		{
			pass[i++]=ch;
			putchar('*');
		}
	}
	pass[i]='\0';
		
}
int main()
{
	char arr[20];
	inputpasswd(arr);
	printf("%s",arr);
}
