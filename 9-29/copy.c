/*************************************************************************
	> File Name: copy.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年09月29日 星期五 15时14分14秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<getopt.h>

int main(int argc, char** argv)
{
	int chose;
	int fd1,fd2,flag=0;
	while((chose = getopt(argc,argv,":s:d:"))!=-1)
	{
		switch(chose)
		{
		case 's':
			fd1 = open(optarg,O_RDONLY);
			if(fd1 < 0)
    		{
        		printf("open faile!\n");
        		return 0;
    		}
			break;
		case 'd':
			fd2 = open(optarg,O_WRONLY|O_CREAT|O_TRUNC,0755);
			if(fd2 < 0)
			{
				printf("open faile!\n");
				return 0;
			}
			flag=1;
			break;
		case '?':
			printf("无效的选项 -%c !\n",optopt);
			return 0;
			break;
		case ':':
			printf("缺少选项参数!\n");
			return 0;
			break;
	
		}
	}
   char ch;
   if(flag)
   {
    	while(read(fd1,&ch,1)!=0)
		{
			write(fd2,&ch,1);
		}
		close(fd2);
	}
	close(fd1);
}
