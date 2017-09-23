#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<pthread.h>
#include"view.h"
#include"logic.h"
#include"my_recv.h"

extern int sockfd;
extern int flag;
int pubflag=1;
void view_menu()
{
	char chose[15];
	
	do{
		fflush(stdin); 
		system("clear");
		printf("\n\n\n");
		printf("\t\t\t1\t\t注册\n");
		printf("\t\t\t2\t\t登陆\n");
		printf("\t\t\t3\t\t注销\n");
		printf("请选择1~3:");
		s_gets(chose,15);
		fflush(stdin);
		if(strcmp(chose,"1")==0)
		{
			send(sockfd,"1",2,0);
			reg_account(sockfd);
		}
		else if(strcmp(chose,"2")==0)
		{
			send(sockfd,"2",2,0);
			if(lading(sockfd)==0)
			continue;
			view_afterlading(sockfd);
		}
		else if(strcmp(chose,"3")==0)
		{
			send(sockfd,"3",2,0);
			return;
		}
	}while(1);
}
void reg_account(int sockfd)
{
	char passwd[20];
	int t=0;
	account_t account;
	printf("请输入账号:");
	s_gets(account.name,15);
	do
	{	if(t!=0)
		{
			printf("两次密码不匹配，请重新输入\n");
			t++;	
		}
		printf("\n请输入密码:");
		s_gets(account.passwd,20);
		printf("\n请再次输入密码:");
		s_gets(passwd,20);
	}while(strcmp(account.passwd,passwd)!=0);
	char buf[200];
	sendaccount(sockfd,account,buf);
	puts(buf);
	sleep(1);
}
int lading(int sockfd)
{
	account_t account;
	printf("请输入账号:");
	s_gets(account.name,15);
	printf("\n请输入密码:"); 
	s_gets(account.passwd,20);
	char buf[200];
	sendaccount(sockfd,account,buf);
	if(strcmp(buf,"success")==0)
	{
		printf("lading success\n");
		sleep(1);
		return 1;
	}
	else
	{
		printf("lading fail\n");
		sleep(3);
		return 0;	
	}
}
void view_afterlading(int sockfd)
{
	char chose[15];
	
	do{
		fflush(stdin);
		system("clear");
		printf("\n\n\n");
		printf("\t\t\t1\t\t好友列表\n");
		printf("\t\t\t2\t\t群列表\n");
		printf("\t\t\t3\t\t返回\n");
		printf("请选择1~3:");
		s_gets(chose,15);
		fflush(stdin);
		if(strcmp(chose,"1")==0)
		{
			send(sockfd,"1",2,0);
			view_friends(sockfd);
		}
		else if(strcmp(chose,"2")==0)
		{
			send(sockfd,"2",2,0);
			view_public(sockfd);
		}
		else if(strcmp(chose,"3")==0)
		{
			send(sockfd,"3",2,0);
			return;
		}
		
	}while(1);
}
void view_friends(int sockfd)
{
	char chose[15];
	pthread_t tid;
	
	do{
		fflush(stdin);
		pthread_create(&tid,NULL,(void*)print_view_friend,(void*)sockfd);  //动态打印好友列表
		s_gets(chose,15);
		flag=0;
		send(sockfd,"0",2,0);
		fflush_sock(sockfd,200);
		fflush(stdin);
		if(strcmp(chose,"1")==0)
		{
			send(sockfd,"1",2,0);
			add_friend(sockfd);
		}
		else if(strcmp(chose,"2")==0)
		{
			send(sockfd,"2",2,0);
			delete_friend(sockfd);
		}
		else if(strcmp(chose,"3")==0)
		{
			send(sockfd,"3",2,0);
			friend_notice_cli(sockfd);
		}
		else if(strcmp(chose,"4")==0)
		{
			send(sockfd,"4",2,0);
			chat_friend_cli(sockfd);
		}
		else if(strcmp(chose,"5")==0)
		{
			send(sockfd,"5",2,0);
			sendfile_view(sockfd);
		}
		else if(strcmp(chose,"6")==0)
		{
			send(sockfd,"6",2,0);
			return;
		}
	}while(1);
}
void* print_view_friend(int sockfd)
{
	while(flag)
	{
		system("clear");
		print_friendlist(sockfd);
		printf("\n\n\n");
		printf("\t\t\t1\t\t添加好友\n");
		printf("\t\t\t2\t\t删除好友\n");
		printf("\t\t\t3\t\t好友通知\n");
		printf("\t\t\t4\t\t聊天\n");
		printf("\t\t\t5\t\t文件传送\n");
		printf("\t\t\t6\t\t返回\n");
		printf("请输入选项1~6:\n");
		sleep(3);
	}
	flag=1;
	pthread_exit(0);
}
void sendfile_view(int sockfd)
{
	char chose[15];
	
	do{
		print_friendlist(sockfd);
		printf("\t\t\t1\t\t发送文件\n");
		printf("\t\t\t2\t\t接受文件\n");
		printf("\t\t\t3\t\t返回\n");
		printf("请选择1~3:\n");
		s_gets(chose,15);
		//send(sockfd,chose,15,0);
		if(strcmp(chose,"1")==0)
		{
			send(sockfd,"1",2,0);
			sendfile(sockfd);
		}
		else if(strcmp(chose,"2")==0)
		{
			send(sockfd,"2",2,0);
			recvfile(sockfd);
		}
		else if(strcmp(chose,"3")==0)
		{
			send(sockfd,"3",2,0);
			return;
		}
	}while(1);
}
void view_public(int sockfd)
{
	char chose[15];
	pthread_t tid;
	
	do{
		fflush(stdin);
		pthread_create(&tid,NULL,(void*)print_view_public,(void*)sockfd);  //动态打印群列表
		s_gets(chose,15);
		pubflag=0;
		//send(sockfd,"0",2,0);
		fflush_sock(sockfd,200);
		fflush(stdin);
		if(strcmp(chose,"1")==0)
		{
			send(sockfd,"1",2,0);
			create_public_cli(sockfd);
		}
		else if(strcmp(chose,"2")==0)
		{
			send(sockfd,"2",2,0);
			public_management_view(sockfd);  //群管理
		}
		else if(strcmp(chose,"3")==0)
		{
			send(sockfd,"3",2,0);
			public_request(sockfd);   //群请求
		}
		else if(strcmp(chose,"4")==0)
		{
			send(sockfd,"4",2,0);
			public_chat(sockfd); 	//群聊
			fflush_sock(sockfd,500);
		}
		else if(strcmp(chose,"5")==0)
		{
			send(sockfd,"5",2,0);
			return;
		}
	}while(1);
}
void* print_view_public(int sockfd)
{
	while(pubflag)
	{
		system("clear");
		print_friendlist(sockfd);
		printf("\n\n\n");
		printf("\t\t\t1\t\t创建群\n");
		printf("\t\t\t2\t\t群管理\n");
		printf("\t\t\t3\t\t群请求\n");
		printf("\t\t\t4\t\t群聊\n");
		printf("\t\t\t5\t\t返回\n");
		printf("请选择1~5:\n");
		sleep(3);
	}
	pubflag=1;
	pthread_exit(0);
}
void public_management_view(int sockfd)
{
	char chose[15];
	char buf[20];
	char pubname[50];
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
	int publicman=0;
	recv(sockfd,buf,20,0);
	if(strcmp(buf,"yes")==0)
	{
		publicman=1;
	}
	do{
		fflush(stdin);
		system("clear");
		print_friendlist(sockfd);   //获取群列表
		printf("\n\n\n");
		printf("\t\t\t1\t\t查看群成员\n");
		printf("\t\t\t2\t\t邀请新成员\n");
		printf("\t\t\t3\t\t踢人\n");
		printf("\t\t\t4\t\t退群\n");
		printf("\t\t\t5\t\t解散群\n");
		printf("\t\t\t6\t\t返回\n");
		printf("请选择1~6:\n");
		s_gets(chose,15);
		fflush(stdin);
		
		if(strcmp(chose,"1")==0)
		{
			send(sockfd,"1",2,0);
			view_members(sockfd);
		}
		else if(strcmp(chose,"2")==0)
		{
			if(publicman==1)
			{
				send(sockfd,"2",2,0);
				invite_members(sockfd);
			}
			else
			{
				send(sockfd,"0",2,0);//用来刷新服务端
				printf("没有权限\n");
				sleep(1);
			}
		}
		else if(strcmp(chose,"3")==0)
		{
			if(publicman==1)
			{
				send(sockfd,"3",2,0);
				delete_members(sockfd);/*踢人*/
			}
			else
			{
				send(sockfd,"0",2,0);
				printf("没有权限\n");
				sleep(1);
			}
		}
		else if(strcmp(chose,"4")==0)
		{
			if(publicman!=1)
			{
				send(sockfd,"4",2,0);
				dropout_public(sockfd);/*退群*/
			}
			else
			{
				send(sockfd,"0",2,0);
				printf("你是群主请不要任性好吗\n");
				sleep(1);
			}
		}
		else if(strcmp(chose,"5")==0)
		{
			if(publicman==1)
			{
				send(sockfd,"5",2,0);
				disbanded_public(sockfd);/*解散群*/
				return;
			}
			else
			{
				send(sockfd,"0",2,0);
				printf("没有权限\n");
				sleep(1);
			}
		}
		else if(strcmp(chose,"6")==0)
		{
			send(sockfd,"6",2,0);
			return;
		}

	}while(1);
}
		
