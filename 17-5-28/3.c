#include<stdio.h>

int main()
{
	int i;
	for(i=0;i<100;i++)
    	{
		//if(i%3!=0)
		//{
			fprintf(stdout, "This is stdout[%d]", i);
			fprintf(stderr, "This is stderr[%d]\n", i);
    		//}
		/*else
		{
			fprintf(stdout, "This is stdout[%d]", i);
			fprintf(stderr, "This is stderr[%d]\n", i);
		}*/
		}
	/*while(1)
	{
		fprintf(stdout,"Group");
		fprintf(stderr,"XiyouLinux");
		getchar();
	}*/
	return 0;
}
