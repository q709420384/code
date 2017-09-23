#include<stdio.h>
#include<unistd.h>
#ifdef __linux__
char* cl = "reset";
#elif __WIN32__
char* cl = "cls";
#else
printf("count not support\n");
exit(0);
#endif

int main()
{
	printf("XiYou\n");
	sleep(2);
	system(cl);
	printf("Linux\n");
}
