#pragma once

#define HOST    "localhost"
#define USER    "root"
#define PASSWD  "Asd892058773asd."
#define DB_NAME "chatroom"
typedef struct data
{
	int clifd;
	int flag;
	MYSQL* mysql;
	char name[50];
}data; 
typedef struct datapu
{
	int clifd;
	int flag;
	MYSQL* mysql;
	char name[50];
	char friname[50];
	
}datapu; 


void myrecv(int clifd,char* buf,int len);
void reg_account_per(int clifd,MYSQL* mysql);
void lading_ser(int clifd,MYSQL* mysql);
void serv_friends(int clifd,MYSQL* mysql,char* name);
void send_friendlist(int clifd,MYSQL* mysql,char* name);
void* send_friendlistdata(data* pack);
int match_tabledata(MYSQL *mysql,char* tablename,char* name);
void add_friend_ser(int clifd,MYSQL* mysql,char* name);
void friend_notice_ser(int clifd,MYSQL* mysql,char* name);
void delete_friend_ser(int clifd,MYSQL* mysql,char* name);
void chat_friend_ser(int clifd,MYSQL* mysql,char* name);
void send_friend_history(int clifd,MYSQL* mysql,char* name,char* friname);
void* send_frhistory(datapu* pack);
void file_ser(int clifd,MYSQL* mysql,char* name);
void sendfile_ser(int clifd,MYSQL* mysql,char* name);
void recvfile_ser(int clifd,MYSQL* mysql,char* name);

void mysql_connect(MYSQL *mysql);                   // 连接mysql数据库
int insert_account(MYSQL *mysql,char* name,char* passwd);                     // 插入数据
int match_account(MYSQL *mysql,char* name,char* passwd);	 //账号匹配
void close_connection(MYSQL *mysql);                // 关闭mysql数据库
int insert_Online(MYSQL* mysql,char* name,int clifd);                  //插入在线列表
void print_table(MYSQL *mysql);				//显示表中内容
void mysql_initOnline(MYSQL* mysql); 		//初始化在线列表
void delete_data(MYSQL *mysql,char* table,char* name);   //删除表中数据
int mysql_createftable(MYSQL* mysql,char* tablename);     //建表
int mysql_createptable(MYSQL* mysql,char* tablename);
void public_view(int clifd,MYSQL* mysql,char* name);      //群聊界面
void public_management_ser(int clifd,MYSQL* mysql,char* name);  //群管理
void create_public_ser(int clifd,MYSQL* mysql,char*name);     //创建群
void sendmypublic(int clifd,MYSQL* mysql,char* name,char* pubname);         //发送自己的群列表
void view_members_ser(int clifd,MYSQL* mysql,char* name,char* pubname);		//显示群成员
void* send_publiclistdata(data* pack);					//发送群列表
void send_publiclist(int clifd,MYSQL* mysql,char* name);	//群名，消息数，位置
void invite_members_ser(int clifd,MYSQL* mysql,char* name,char* pubname); //邀请群成员
void public_request_ser(int clifd,MYSQL* mysql,char* name);           //群请求
void delete_members_ser(int clifd,MYSQL* mysql,char* name,char* pubname); //踢人
void dropout_public_ser(int clifd,MYSQL* mysql,char* name,char* pubname); //退群
void disbanded_public_ser(int clifd,MYSQL* mysql,char* name,char* pubname);   //解散群
void delete_mbdata(MYSQL* mysql,char* mbname,char* pubname); //删除成员表中的群
void public_chat_ser(int clifd,MYSQL* mysql,char* name);		//群聊
void* send_puhistory(datapu* pack);	//群聊记录
void send_public_history(int clifd,MYSQL* mysql,char* pubname); //群聊记录
void updatepu(MYSQL* mysql,char* name,char* pubname);   //更新群消息记录
