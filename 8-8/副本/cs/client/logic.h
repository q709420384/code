#pragma once

typedef struct account_t
{
	char name[15];
	char passwd[20];
}account_t;

typedef struct chat
{
	char time[40];
	char news[200];
}chat;
int con_service();
void sendaccount(int sockfd,account_t account,char* buf);
void print_friendlist(int sockfd);
int add_friend(int sockfd);
void friend_notice_cli(int sockfd);
void delete_friend(int sockfd);
void fflush_sock(int sockfd,int size);
void chat_friend_cli(int sockfd);
void print_friend_history(int sockfd);
void* print_view_fhistory(int sockfd);
void sendfile(int sockfd);
void recvfile(int sockfd);
void create_public_cli(int sockfd);
void invite_members(int sockfd);
void public_request(int sockfd);
void delete_members(int sockfd);
void dropout_public(int sockfd);
void disbanded_public(int sockfd);
void public_chat(int sockfd);
void* print_view_phistory(int sockfd);
