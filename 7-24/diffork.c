#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int qvar=5;
char *p;
int main()
{	
	pid_t pid;
	int var=1,i;
	char* str="I'm here";
	p=str;
	printf("fork is different with vfork\n");
	
	//pid=fork();
	pid=vfork();
	switch(pid)
	{
		case 0:
			i=3;
			while(i--)
			{
				printf("Child process is running\n");
				qvar++;
				var++;
				sleep(1);
			}

			printf("Child's qvar = %d,var = %d,str = %s\n",qvar,var,p);
			//exit(0);
			break;
		case -1:
			perror("failed\n");
			exit(0);
			break;
		default:
			i=5;
			while(i-->0)
			{
				printf("Parent is running\n");
				qvar++;
				var++;
				sleep(1);
			}
			printf("Parent's qvar = %d,var = %d,str = %s\n",qvar,var,p);
			exit(0);
	}

}

