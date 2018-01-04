/*************************************************************************
	> File Name: utili.h
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年11月18日 星期六 10时13分30秒
 ************************************************************************/

#ifndef _UTILI_H
#define _UTILI_H

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<errno.h>

#define LISTENQ 5
#define IP "127.0.0.1"

typedef enum{ADD, SUB, MUL, DIV, MOD, NOINPUT}OPERATION;
typedef struct
{
    int op1;
    int op2;
    OPERATION op;
}calcst;
int start_up(int port);
char* myrecv(int clifd,char* buf,int len);
char* s_gets(char* st,int n);


int start_up(int port)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1)
    {
        printf("Created socket fail......\n");
        return -1;
    }
    struct sockaddr_in seraddr;
    int reuse = 1;
    if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
    {
        return -1;
    }
    bzero(&seraddr, sizeof(seraddr));
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    seraddr.sin_port = htons(port);

    if(bind(fd, (struct sockaddr*)&seraddr, sizeof(seraddr)) == -1)
    {
        perror("bind error: ");
        return -1;
    }
    listen(fd, LISTENQ);

    return fd;
}

char* myrecv(int clifd,char* buf,int len)
{
	int sum=0,n;
	while(sum!=len)
	{
		n=recv(clifd,buf+sum,len-sum,0);
		if(n<0)
			perror("myrecv");
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
#endif
