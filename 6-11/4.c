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
int main()
{
	 int   i=0;   
          char   c;   
          while(i<20&&(c=getch(),c!='\n'))   
          {
                  putchar('*');   
                  ++i;   
          }
          getch();
}
