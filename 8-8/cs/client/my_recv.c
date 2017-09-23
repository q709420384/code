#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<time.h>
#include"my_recv.h"

void my_err(const char* err_string,int line)
{
	fprintf(stderr,"line:%d",line);
	perror(err_string);
	exit(1);
}

char* myrecv(int clifd,char* buf,int len)
{
	int sum=0,n;
	while(sum!=len)
	{
		n=recv(clifd,buf+sum,len-sum,0);
		if(n<0)
			my_err("myrecv",__LINE__);
		sum+=n;
	}
	return buf;
}
char* s_gets(char* st,int n)
{
	char* ret_val;
	int i=0;
	ret_val=fgets(st,n,stdin);
	if(ret_val)
	{
		while(st[i]!='\n'&&st[i]!='\0')
			i++;
		if(st[i]=='\n')
			st[i]='\0';
		else
			while(getchar()!='\n')
				continue;
	}
	return ret_val;
}
void gettime(char* timenow)
{
	time_t t;
	time(&t);
	strcpy(timenow,ctime(&t));
	char* p=strchr(timenow,'\n');
	*p='\0';
   	return;
}
