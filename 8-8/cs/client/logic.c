#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<pthread.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"my_recv.h"
#include"logic.h"

#define  IP1   "47.94.12.103"
#define  IP2   "182.254.227.246"


char friname[15];
int flag1=1;
char ppubname[50];
int flag2=1;
int con_service()
{
	int				conn_fd;
	struct sockaddr_in serv_addr;

	memset(&serv_addr,0,sizeof(struct sockaddr_in));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(4507);
	if(inet_aton(IP1,&serv_addr.sin_addr)==0)
	{
		printf("invalid server ip address\n");
		exit(1);
	}
	conn_fd=socket(AF_INET,SOCK_STREAM,0);
	if(conn_fd<0)
		my_err("socket",__LINE__);
	if(connect(conn_fd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr))<0)
		my_err("connect",__LINE__);
	else
	{
		printf("Connect process!\n");
		return conn_fd;
	}
	/*for(i=1;i<argc;i++)
	{
		if(strcmp("-p",argv[i])==0)
		{
			serv_port=atoi(argv[i+1]);
			if(serv_port<0||serv_port>65535)
			{
				printf("invalid serv_addr.sin_port\n");
				exit(1);
			}
			else
				serv_addr.sin_port=htons(serv_port);
			continue;
		}
		if(strcmp("-a",argv[i])==0)
		{
			if(inet_aton(argv[i+1],&serv_addr.sin_addr)==0)
			{
				printf("invalid server ip address\n");
				exit(1);
			}
			continue;
		}
	}
	if(serv_addr.sin_port==0||serv_addr.sin_addr.s_addr==0)
	{
		printf("Usage: [-p] [ser_addr.sin_port] [-a] [serv_address\n]");
		exit(1);
	}
	conn_fd=socket(AF_INET,SOCK_STREAM,0);
	if(conn_fd<0)
		my_err("socket",__LINE__);
	if(connect(conn_fd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr))<0)
		my_err("connect",__LINE__);
	else
	{
		printf("Connect process!\n");
		return conn_fd;
	}*/
}
//发送账户
void sendaccount(int sockfd,account_t account,char* buf)
{
	int len;
	if(send(sockfd,(void*)&account,sizeof(account),0)<0)
		my_err("sendaccount",__LINE__);
	myrecv(sockfd,buf,200);
}
void print_friendlist(int sockfd)
{
	char buf[300];
	while(1)
	{
		recv(sockfd,buf,300,0);
		if(strcmp(buf,"\r\n")==0)
		{
			break;	
		}
		else
		{
			puts(buf);
		}
	}
	
}
int add_friend(int sockfd)
{
	char name[15];
	char buf[40];
	printf("请输入要添加好友的账号:");
	s_gets(name,15);
	send(sockfd,name,15,0);
	recv(sockfd,buf,40,0);
	puts(buf);
	sleep(1);
}
void friend_notice_cli(int sockfd)
{
	system("clear");
	char buf[200];
	while(1)
	{
		myrecv(sockfd,buf,200);
		if(strcmp(buf,"\r\n")==0)
			break;
		else
			puts(buf);
	}
	printf("请选择要处理的消息(输入return返回):");
	s_gets(buf,15);
	send(sockfd,buf,15,0);
	if(strcmp(buf,"return")==0)
		return;
fuck1:
	printf("请选择(y/n)");
	s_gets(buf,15);
	if(strcmp(buf,"y")!=0&&strcmp(buf,"n")!=0)
		goto fuck1;
	send(sockfd,buf,15,0);
	recv(sockfd,buf,200,0);
	puts(buf);
	sleep(1);
}
void delete_friend(int sockfd)
{
	char friname[15];
	char chose[15];
	print_friendlist(sockfd);
	printf("请输入要删除好友的账号(return退出):");
	s_gets(friname,15);
	send(sockfd,friname,15,0);
	if(strcmp(friname,"return")==0)
		return;
fuck2:
	printf("请再次确认y/n:");
	s_gets(chose,15);
	if(strcmp(chose,"y")!=0&&strcmp(chose,"n")!=0)
		goto fuck2;
	if(strcmp("y",chose)==0)
		send(sockfd,chose,15,0);
	else
	{
		send(sockfd,chose,15,0);
		return;
	}
	char buf[40];
	myrecv(sockfd,buf,40);
	puts(buf);
}
void fflush_sock(int sockfd,int size)
{
	char buf[size];
	fd_set readfds;
	int ret;
	struct timeval tv;
	while(1)
	{
		FD_ZERO(&readfds);
		FD_SET(sockfd,&readfds);
		tv.tv_sec = 0;
		tv.tv_usec = 0;
		ret=select(sockfd+1,&readfds,NULL,NULL,&tv);
		switch(ret)
		{
			case -1:
				exit(-1);
				break;
			case 0:
				return;
			default:
				recv(sockfd,buf,size,0);
		}
	}
}
void chat_friend_cli(int sockfd)
{
	char buf[40];
	chat mess;
	system("clear");
	print_friendlist(sockfd);

	printf("请选择好友(return退出):\n");
	s_gets(friname,15);
	send(sockfd,friname,15,0);
	if(strcmp(friname,"return")==0)
		return;
	recv(sockfd,buf,40,0);
	if(strcmp(buf,"is not your friends")==0)
	{
		printf("%s %s\n",friname,buf);
		sleep(2);
		return;
	}
	pthread_t tid;
	pthread_create(&tid,NULL,(void*)print_view_fhistory,(void*)sockfd);  //动态打印聊天记录
	while(1)
	{
		s_gets(mess.news,200);
		gettime(mess.time);
		send(sockfd,(void*)&mess,sizeof(chat),0);
		if(strcmp(mess.news,"return")==0)
		{
			flag1=0;
			//send(sockfd,"0",2,0);	
			fflush_sock(sockfd,500);
			return;
		}
	}
	
}
void public_chat(int sockfd)
{
	char chose[15];
	char buf[20];
	char pubname[50];
	chat mess;
	printf("请选择群:\n");
	s_gets(pubname,50);
	send(sockfd,pubname,50,0);
	recv(sockfd,buf,20,0);
	if(strcmp(buf,"success")!=0)
	{
		printf("你不是该群成员或该群不存在\n");
		sleep(1);
		return;
	}
	strcpy(ppubname,pubname);
	pthread_t tid;
	pthread_create(&tid,NULL,(void*)print_view_phistory,(void*)sockfd);  //动态打印聊天记录
	while(1)
	{
		s_gets(mess.news,200);
		gettime(mess.time);
		send(sockfd,(void*)&mess,sizeof(chat),0);
		if(strcmp(mess.news,"return")==0)
		{
			flag2=0;
			//send(sockfd,"0",2,0);	
			fflush_sock(sockfd,500);
			return;
		}
	}
}
void* print_view_phistory(int sockfd)
{
	while(flag2)
	{
		system("clear");
		print_friend_history(sockfd);
		printf("Me @ %s(return退出聊天):\n",ppubname);
		sleep(5);
	}
	flag2=1;
	pthread_exit(0);
}
void print_friend_history(int sockfd)
{
	char buf[500];
	while(1)
	{
		myrecv(sockfd,buf,500);
		if(strcmp(buf,"\r\n")==0)
			break;
		else
			puts(buf);
	}
}
void* print_view_fhistory(int sockfd)
{
	while(flag1)
	{
		system("clear");
		print_friend_history(sockfd);
		printf("Me @ %s(return退出聊天):\n",friname);
		sleep(5);
	}
	flag1=1;
	pthread_exit(0);
}
void sendfile(int sockfd)
{
	char friname[15];
	char path[256];
	char res[20];
	printf("请选择要发送的好友(return退出):");
	s_gets(friname,15);
	send(sockfd,friname,15,0);
	if(strcmp(friname,"return")==0)
	{
		return;
	}
	recv(sockfd,res,20,0);
	if(strcmp(res,"is not you friend")==0)
	{
		printf("%s %s\n",friname,res);
		sleep(1);
		return;
	}
	printf("请输入文件及路径:");
	s_gets(path,256);
	FILE* fp=fopen(path,"r");
	if(fp==NULL)
	{
		send(sockfd,"fail",15,0);
		fprintf(stderr,"文件不存在或路径输入有误\n");
		sleep(1);
		return;
	}
	send(sockfd,"success",15,0);
	
	////////////////////////////////////
	/*
	printf("请等待对方回应\n");  	         //此处应当添加取消/////////////////////////////////////////
	recv(sockfd,res,40,0);

	if(strcmp(res,"success")!=0)
	{
		printf("%s %s\n",friname,res);
		sleep(2);
		fclose(fp);
		return;
	}
	char*p=strchr(path,'/');
	if(p==NULL)
		send(sockfd,path,256,0);
	else
	{
		p=path;
		while(*p)
			p++;
		while(*p!='/')
			p--;
		send(sockfd,++p,256,0);
	}
	int size,len;
	char buf[1024];
	while((size=fread(buf,1,1024,fp))>0)
	{
		send(sockfd,(void*)&size,4,0);
		len=send(sockfd,buf,size,0);
		printf("size=%d len=%d \n",size,len);
	}
	fclose(fp);
	
	*/
	//////////////////////////////////////
	
	
	///////////////////////////////////
	//传服务器
	char*p=strchr(path,'/');
	if(p==NULL)
		send(sockfd,path,256,0);
	else
	{
		p=path;
		while(*p)
			p++;
		while(*p!='/')
			p--;
		send(sockfd,++p,256,0);
	}
	int size,len;
	char buf[1024];
	while((size=fread(buf,1,1024,fp))>0)
	{
		send(sockfd,(void*)&size,4,0);
		len=send(sockfd,buf,size,0);
		//printf("size=%d len=%d \n",size,len);
		if(size<1024)
			break;
	}
	fclose(fp);
	recv(sockfd,buf,20,0);
	//////////////////////////////////
}
void recvfile(int sockfd)
{
	char buf[1024];
	char filename[50];
	char friname[15];
	char chose[15];
	int size,len;
	while(1)
	{
		myrecv(sockfd,buf,500);
		if(strcmp(buf,"\r\n")==0)
			break;
		else
			puts(buf);
	}
	printf("请输入接收好友:");
	s_gets(friname,15);
	send(sockfd,friname,15,0);
	printf("请输入要接收的文件名:");
	s_gets(filename,50);
	send(sockfd,filename,50,0);
	recv(sockfd,buf,20,0);
	if(strcmp(buf,"success")!=0)
	{
		printf("输入有误，请重试\n");
		return;
	}
	FILE* fp=fopen(filename,"w");
	while(recv(sockfd,(void*)&size,4,0))
	{
		myrecv(sockfd,buf,size);
		len=fwrite(buf,1,size,fp);
		//printf("size=%d len=%d \n",size,len);
		if(size<1024)
			break;
	}
	fclose(fp);
}
void create_public_cli(int sockfd)
{
	char pubname[50];
	char buf[20];
	printf("请输入要创建的群名(return退出):");
	s_gets(pubname,50);
	send(sockfd,pubname,50,0);
	if(strcmp(pubname,"return")==0)
		return;
	recv(sockfd,buf,20,0);
	if(strcmp(buf,"success")!=0)
	{
		printf("该群名已被注册！\n");
		return;
	}
	printf("注册成功！\n");
	sleep(1);
}
void invite_members(int sockfd)
{
	char friname[15];
	char buf[50];
	printf("请输入要邀请的账号:");
	s_gets(friname,15);
	send(sockfd,friname,15,0);
	recv(sockfd,buf,50,0);
	if(strcmp(buf,"success")!=0)
	{
		puts(buf);
		sleep(1);
		return;
	}	
}
void public_request(int sockfd)
{
	system("clear");
	char buf[200];
	while(1)
	{
		myrecv(sockfd,buf,200);
		if(strcmp(buf,"\r\n")==0)
			break;
		else
			puts(buf);
	}
	printf("请选择要处理的消息(输入return返回):");
	s_gets(buf,50);
	send(sockfd,buf,50,0);
	if(strcmp(buf,"return")==0)
		return;
fuck3:
	printf("请选择(y/n)");
	s_gets(buf,15);
	if(strcmp(buf,"y")!=0&&strcmp(buf,"n")!=0)
		goto fuck3;
	send(sockfd,buf,15,0);
	recv(sockfd,buf,200,0);
	puts(buf);
	sleep(1);
}
void delete_members(int sockfd)
{
	char friname[15];
	char chose[15];
	print_friendlist(sockfd);
	printf("请输入要删除的账号(return退出):");
	s_gets(friname,15);
	send(sockfd,friname,15,0);
	if(strcmp(friname,"return")==0)
		return;
fuck4:
	printf("请再次确认y/n:");
	s_gets(chose,15);
	if(strcmp(chose,"y")!=0&&strcmp(chose,"n")!=0)
		goto fuck4;
	if(strcmp("y",chose)==0)
		send(sockfd,chose,15,0);
	else
	{
		send(sockfd,chose,15,0);
		return;
	}
	char buf[40];
	myrecv(sockfd,buf,40);
	puts(buf);
}
void dropout_public(int sockfd)
{
	char chose[2];
	printf("请再次确认y/n:");
	s_gets(chose,2);
	send(sockfd,chose,2,0);
	if(strcmp(chose,"n")==0)
	{
		return;
	}
	printf("退群成功\n");
}
void disbanded_public(int sockfd)
{
	char chose[2];
	printf("请再次确认y/n:");
	s_gets(chose,2);
	send(sockfd,chose,2,0);
	if(strcmp(chose,"n")==0)
	{
		return;
	}
	printf("群已解散\n");
}

void view_members(int sockfd)
{
	print_friendlist(sockfd);
	printf("\n\n按任意键退出");
	getchar();
}
