#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<stdlib.h>
#include<assert.h>
#include <mysql/mysql.h>
#include<pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include"persist.h"
#include"my_recv.h"
#include"../client/logic.h"

void myrecv(int clifd,char* buf,int len)
{
	int sum=0,n;
	while(sum!=len)
	{
		n=recv(clifd,buf+sum,len-sum,0);
		if(n<0)
			my_err("myrecv",__LINE__);
		sum+=n;
	}
}
void reg_account_per(int clifd,MYSQL* mysql)
{
	account_t* account=(account_t*)malloc(sizeof(account_t));
	myrecv(clifd,(char*)account,sizeof(account_t));
	if(insert_account(mysql,account->name,account->passwd))
	{
		mysql_createftable(mysql,account->name);
		mysql_createptable(mysql,account->name);
		char file[256];
		sprintf(file,"file/%s",account->name);
		mkdir(file,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		if((send(clifd,"Add success!",200,0))<0)
		{
			my_err("send res fail",__LINE__);
		}
	}
	else
	{
		if((send(clifd,"Add fail!",200,0))<0)
		{
			my_err("send res fail",__LINE__);
		}
	}
}
/*登陆*/
void lading_ser(int clifd,MYSQL* mysql)
{
	account_t* account=(account_t*)malloc(sizeof(account_t));
	myrecv(clifd,(char*)account,sizeof(account_t));
	if(match_account(mysql,account->name,account->passwd)&&insert_Online(mysql,account->name,clifd))
	{
		if((send(clifd,"success",200,0))<0)
			my_err("send res fail",__LINE__);
		char recvbuf[2];
		while(1)
		{
			if(recv(clifd,recvbuf,2,0)<0)
			{
				my_err("recv",__LINE__);
			}
			if(strcmp("1",recvbuf)==0)
			{
				serv_friends(clifd,mysql,account->name);
			}
			else if(strcmp("2",recvbuf)==0)
				public_view(clifd,mysql,account->name);
			else if(strcmp("3",recvbuf)==0)
			{
				delete_data(mysql,"Online",account->name);
				return;
			}
		}
	}
	else
	{
		if((send(clifd,"fail",200,0))<0)
			my_err("send res fail",__LINE__);
	}
}
/* 连接mysql数据库 */  
void mysql_connect(MYSQL *mysql)
{  
    if(!mysql_real_connect(mysql, HOST, USER, PASSWD, DB_NAME, 0, NULL, 0)) 
    {  
        printf("Failed to connect:%s\n", mysql_error(mysql));
        my_err("mysql_real_connect", __LINE__);
    }  
    printf("Connect database sucessfully!\n\n");
} 
int insert_account(MYSQL *mysql,char* name,char*passwd)
{  
    int t; 
    char query[200]; 

    /* 把几个变量字符串连接成一个完整的mysql命令 */  
    sprintf(query, "insert into Accounts (name,passwd) values (\"%s\",\"%s\");",name,passwd);
    printf("%s\n", query);  

    t = mysql_real_query(mysql, query, strlen(query));
    if (t) 
    {  
        printf("Failed to query:%s\n", mysql_error(mysql));  
        return 0;
    }
    printf("Success add!\n");
    return 1;
}  
int match_account(MYSQL *mysql,char* name,char* passwd)
{
	int t ;
	MYSQL_RES *res;
	MYSQL_ROW row;          // 返回行数据
	char query[200];
	sprintf(query,"select * from Accounts where name=\"%s\" and passwd=\"%s\"",name,passwd);
	printf("%s\n", query); 
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		printf("Failed to query:%s\n", mysql_error(mysql));  
    }
    res = mysql_store_result(mysql);
    if(mysql_fetch_row(res)==0)
    	return 0;
    mysql_free_result(res);
    return 1;
}

int insert_Online(MYSQL* mysql,char* name,int clifd)
{
	int t;  
    char query[200]; 

    /* 把几个变量字符串连接成一个完整的mysql命令 */  
    sprintf(query, "insert into Online (name,fd) values (\"%s\",%d);",name,clifd);
    printf("%s\n", query);  

    t = mysql_real_query(mysql, query, strlen(query));
    if (t) {  
        printf("Failed to query:%s\n", mysql_error(mysql));  
        return 0;
    }
    printf("Success add!\n");
    return 1;
}
//显示表中内容
void print_table(MYSQL *mysql)  
{  
    int t;
    char query[50];
    MYSQL_RES *res;         // 返回查询结果
    MYSQL_ROW row;          // 返回行数据

    memset(query, '\0', sizeof(query));

    sprintf(query, "select * from Online");

    t = mysql_real_query(mysql, query, strlen(query));  

    if (t) {
        printf("Failed to query: %s\n", mysql_error(mysql));  
        return;
    } 
    printf("\nQuery successfully!\n\n");  

    res = mysql_store_result(mysql);
    while (row = mysql_fetch_row(res)) {  
        for(t = 0; t < mysql_num_fields(res); t++) {  
            printf("%s\t", row[t]);  
        }  
        printf("\n");
    }  
    mysql_free_result(res);
}  
void mysql_initOnline(MYSQL* mysql)
{
	int t;
    char query[50];
    MYSQL_RES *res;         // 返回查询结果
    MYSQL_ROW row;          // 返回行数据

    memset(query, '\0', sizeof(query));

    sprintf(query, "truncate table Online");

    t = mysql_real_query(mysql, query, strlen(query));  

    if (t) {
        printf("Failed to Init: %s\n", mysql_error(mysql));  
        return;
    }  
    printf("\nInit successfully!\n\n");  

    res = mysql_store_result(mysql);
    mysql_free_result(res);
}
//删除数据
void delete_data(MYSQL *mysql,char* table,char* name)
{  
    int t;
    char query[200];     
    MYSQL_RES *res;         // 返回查询结果
    MYSQL_ROW row;          // 返回行数据

    sprintf(query, "delete from %s where name =\"%s\"", table,name);
    printf("%s\n", query);

    t = mysql_real_query(mysql, query, strlen(query));
    if (t) {  
        printf("Failed to delete: %s\n", mysql_error(mysql));  
        return;
    }
    printf("Delete data sucessfully!\n");
}  
//建表
int mysql_createftable(MYSQL* mysql,char* tablename)
{
	int t;
    char query[200];     
    MYSQL_RES *res;         // 返回查询结果
    sprintf(query,"create table %sfr (friends char(15) binary not null unique,count int not null,filecount int not null)",tablename);
    printf("%s\n", query);
    t = mysql_real_query(mysql, query, strlen(query));
    if (t) {  
        printf("Failed to create ctable: %s\n", mysql_error(mysql));  
        return 0;
    }
    printf("create ctable sucessfully!\n");
    return 1;
}
int mysql_createptable(MYSQL* mysql,char* tablename)
{
	int t;
    char query[200];     
    MYSQL_RES *res;         // 返回查询结果
    sprintf(query,"create table %spu (public char(50) binary not null unique,count int not null,position char(15) not null)",tablename);
    printf("%s\n", query);
    t = mysql_real_query(mysql, query, strlen(query));
    if (t) {  
        printf("Failed to create ctable: %s\n", mysql_error(mysql));  
        return 0;
    }
    printf("create ctable sucessfully!\n");
    return 1;
}
void serv_friends(int clifd,MYSQL* mysql,char * name)
{
	char recvbuf[2];
	pthread_t thid;
	data* pack=(data*)malloc(sizeof(data));
	pack->flag=1;
	pack->clifd=clifd;
	pack->mysql=mysql;
	strcpy(pack->name,name);
	while(1)
	{	
		pthread_create(&thid,NULL,(void*)send_friendlistdata,(void*)pack);
		if(recv(clifd,recvbuf,2,0)<0)
		{
			my_err("recv",__LINE__);
		}
		if(recv(clifd,recvbuf,2,0)<0)
		{
			my_err("recv",__LINE__);
		}
		pack->flag=0;
		if(strcmp("1",recvbuf)==0)
			add_friend_ser(clifd,mysql,name);
		else if(strcmp("2",recvbuf)==0)
			delete_friend_ser(clifd,mysql,name);
		else if(strcmp("3",recvbuf)==0)
			friend_notice_ser(clifd,mysql,name);
		else if(strcmp("4",recvbuf)==0)
			chat_friend_ser(clifd,mysql,name);
		else if(strcmp("5",recvbuf)==0)
			file_ser(clifd,mysql,name);
		else if(strcmp("6",recvbuf)==0)
		{	
			return;
		}
	}
}
void public_view(int clifd,MYSQL* mysql,char* name)
{
	char recvbuf[2];
	pthread_t thid;
	data* pack=(data*)malloc(sizeof(data));
	pack->flag=1;
	pack->clifd=clifd;
	pack->mysql=mysql;
	strcpy(pack->name,name);
	while(1)
	{
		pthread_create(&thid,NULL,(void*)send_publiclistdata,(void*)pack);
		/*if(recv(clifd,recvbuf,2,0)<0)
		{
			my_err("recv",__LINE__);
		}
		printf("11111  %s\n",recvbuf);*/
		if(recv(clifd,recvbuf,2,0)<0)
		{
			my_err("recv",__LINE__);
		}
		pack->flag=0;
		if(strcmp("1",recvbuf)==0)
			create_public_ser(clifd,mysql,name);
		else if(strcmp("2",recvbuf)==0)
		{
			public_management_ser(clifd,mysql,name);
		}
		else if(strcmp("3",recvbuf)==0)
			public_request_ser(clifd,mysql,name);//群请求 
		else if(strcmp("4",recvbuf)==0)
			public_chat_ser(clifd,mysql,name);	 //群聊
		else if(strcmp("5",recvbuf)==0)
		{
			return;
		}
	}
}
void public_chat_ser(int clifd,MYSQL* mysql,char* name)
{
	char recvbuf[2];
	char pubname[50];
	recv(clifd,pubname,50,0);
	int t ;
	MYSQL_RES *res;
	MYSQL_ROW row;          // 返回行数据
	char query[200];

	sprintf(query,"select * from %s where name=\"%s\"",pubname,name);
	
	puts(query);
	
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		send(clifd,"fail",20,0);
		printf("Failed to query:%s\n", mysql_error(mysql)); 
		sleep(1);
		return;
    }
    res = mysql_store_result(mysql);
	if(mysql_fetch_row(res)==0) 
	{
		send(clifd,"fail",20,0);
		mysql_free_result(res);
		return;
	}
	send(clifd,"success",20,0);
	mysql_free_result(res);
	
	chat mess;
    pthread_t thid;
    datapu* pack=(datapu*)malloc(sizeof(datapu));
    pack->flag=1;
	pack->clifd=clifd;
	pack->mysql=mysql;
	strcpy(pack->name,name);
	strcpy(pack->friname,pubname);
	pthread_create(&thid,NULL,(void*)send_puhistory,(void*)pack);       //动态更新群消息记录
    while(1)
    {
		
		myrecv(clifd,(char*)&mess,sizeof(chat));
		if(strcmp(mess.news,"return")==0)
		{
			pack->flag=0;
			free(pack);
			break;
		}
		//消息入库
		sprintf(query,"insert into Messagepub value(\"%s\",\"%s\",\"%s\",\"%s\")",pubname,mess.time,name,mess.news);
		t = mysql_real_query(mysql, query, strlen(query));
		if (t) 
		{
			printf("Failed to query:%s\n", mysql_error(mysql)); 
		}
		res = mysql_store_result(mysql);
		mysql_free_result(res);
		
		sprintf(query,"select name from %s",pubname);
		t = mysql_real_query(mysql, query, strlen(query));
		if (t) 
		{
			printf("Failed to query:%s\n", mysql_error(mysql)); 
		}
		res = mysql_store_result(mysql);
		while (row = mysql_fetch_row(res)) 
    	{  
        	updatepu(mysql,row[0],pubname);
    	} 
		mysql_free_result(res);
	}
	sprintf(query,"update %spu set count=0 where public=\"%s\"",name,pubname);
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		printf("Failed to query:%s\n", mysql_error(mysql)); 
	}
	res = mysql_store_result(mysql);
	mysql_free_result(res);
}
void updatepu(MYSQL* mysql,char* name,char* pubname)
{
	int t ;
	MYSQL_RES *res;
	MYSQL_ROW row;          // 返回行数据
	char query[200];

	sprintf(query,"update %spu set count=count+1 where public=\"%s\"",name,pubname);
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		printf("Failed to query:%s\n", mysql_error(mysql)); 
	}
	res = mysql_store_result(mysql);
	mysql_free_result(res);
}
void* send_puhistory(datapu* pack)
{
	while(pack->flag)
	{
		send_public_history(pack->clifd,pack->mysql,pack->friname);
		sleep(5);
	}
	pthread_exit(0);
}
void send_public_history(int clifd,MYSQL* mysql,char* pubname)
{
	int t;
    char query[200];
    char buf[500];
    MYSQL_RES *res;         // 返回查询结果
    MYSQL_ROW row;          // 返回行数据
	//发送消息给客户端
	sprintf(query,"select * from Messagepub where public=\"%s\"",pubname);
    t = mysql_real_query(mysql, query, strlen(query)); 
    if (t) 
    {
        printf("Failed to query: %s\n", mysql_error(mysql));  
        return;
    }
    res = mysql_store_result(mysql);
    while (row = mysql_fetch_row(res)) 
    {  
        sprintf(buf,"%s\t%s @ %s : %s",row[1],row[0],row[2],row[3]);
        send(clifd,buf,500,0);
    } 
    send(clifd,"\r\n",500,0);
    mysql_free_result(res);
}
void public_request_ser(int clifd,MYSQL* mysql,char* name) //群请求
{
	int t;
    char query[200];
    MYSQL_RES *res;         // 返回查询结果
    MYSQL_ROW row;          // 返回行数据
	char buf[200]={0};
	char pubname[50];
	//发送好友请求给客户端
	sprintf(query,"select * from System where recv=\"%s\" and user=0",name);
    t = mysql_real_query(mysql, query, strlen(query)); 

    if (t) {
        printf("Failed to query: %s\n", mysql_error(mysql));  
        return;
    }
    res = mysql_store_result(mysql);
    while (row = mysql_fetch_row(res)) 
    {  
        sprintf(buf,"\t\t\t%s\tinvite you to join",row[0]);
        send(clifd,buf,200,0);
    } 
    send(clifd,"\r\n",200,0);
    mysql_free_result(res);
    recv(clifd,pubname,50,0);
    if(strcmp(pubname,"return")==0)
    	return;
    recv(clifd,buf,15,0);
    if(strcmp(buf,"y")==0)
    {
    	//添加前再次检索
    	sprintf(query,"select * from System where send=\"%s\" and recv=\"%s\" and user=0",pubname,name);
    	t = mysql_real_query(mysql, query, strlen(query));

    	if (t) {
      	  	printf("Failed to query: %s\n", mysql_error(mysql)); 
     	   	return;
    	}
    	res = mysql_store_result(mysql);
    	if(mysql_fetch_row(res)==0)
   	 	{
			send(clifd,"Input error",40,0);
			return;	
    	}
    	mysql_free_result(res);
    	
    	//添加群至自己的列表
    	sprintf(query,"insert into %spu value(\"%s\",0,\"群员\")",name,pubname);
    	t = mysql_real_query(mysql, query, strlen(query)); 

    	if (t) {
      	  	printf("Failed to query: %s\n", mysql_error(mysql));  
     	   	return;
    	}
    	res = mysql_store_result(mysql);
    	mysql_free_result(res);
    	
    	//添加自己到群列表
    	sprintf(query,"insert into %s value(\"%s\",\"群员\")",pubname,name);
    	t = mysql_real_query(mysql, query, strlen(query)); 

    	if (t) {
      	  	printf("Failed to query: %s\n", mysql_error(mysql));  
     	   	return;
    	}
    	res = mysql_store_result(mysql);
    	mysql_free_result(res);
    	
    	//删除通知
    	sprintf(query, "delete from System where send=\"%s\" and recv=\"%s\" and user=0", pubname,name);
    	printf("%s\n", query);

    	t = mysql_real_query(mysql, query, strlen(query));
    	if (t) {  
        	printf("Failed to delete: %s\n", mysql_error(mysql));  
        	return;
    	}
    	mysql_free_result(res);
    	send(clifd,"You can chat in group",200,0);
	}
	else
	{
		sprintf(query, "delete from System where send=\"%s\" and recv=\"%s\" and user=0", pubname,name);
    	printf("%s\n", query);

    	t = mysql_real_query(mysql, query, strlen(query));
    	if (t) {  
        	printf("Failed to delete: %s\n", mysql_error(mysql));  
        	return;
    	}
    	mysql_free_result(res);
	}    
}
//发送群列表
void* send_publiclistdata(data* pack)
{
	while(pack->flag)
	{
		send_publiclist(pack->clifd,pack->mysql,pack->name);
		sleep(3);
	}
	pack->flag=1;
	pthread_exit(0);
}
//群名，消息数，位置
void send_publiclist(int clifd,MYSQL* mysql,char* name)
{
	char buf[200];
	int t ;
	MYSQL_RES *res;
	MYSQL_ROW row;          // 返回行数据
	char query[200];
	
	sprintf(query,"select * from %spu",name);
	puts(query);
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		printf("Failed to query:%s\n", mysql_error(mysql)); 
    }
    res = mysql_store_result(mysql);
	while (row = mysql_fetch_row(res)) 
	{
		sprintf(buf,"\t\t%s\t\t%s\t\t%s",row[0],row[1],row[2]);
		send(clifd,buf,200,0);
	}
	send(clifd,"\r\n",200,0); 
    mysql_free_result(res);
}
void public_management_ser(int clifd,MYSQL* mysql,char* name)
{
	char recvbuf[2];
	char pubname[50];
	recv(clifd,pubname,50,0);
	int t ;
	MYSQL_RES *res;
	MYSQL_ROW row;          // 返回行数据
	char query[200];

	sprintf(query,"select * from %s where name=\"%s\"",pubname,name);
	
	puts(query);
	
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		send(clifd,"fail",20,0);
		printf("Failed to query:%s\n", mysql_error(mysql)); 
		return;
    }
    res = mysql_store_result(mysql);
	if(mysql_fetch_row(res)==0) 
	{
		send(clifd,"fail",20,0);
		mysql_free_result(res);
		return;
	}
	send(clifd,"success",20,0);
	mysql_free_result(res);
	/////////////////////////////////////////
	sprintf(query,"select * from %s where name=\"%s\" and position=\"群主\"",pubname,name);
	puts(query);
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		printf("Failed to query:%s\n", mysql_error(mysql)); 
    }
    res = mysql_store_result(mysql);
	if(mysql_fetch_row(res)==0) 
	{
		send(clifd,"no",20,0);
		mysql_free_result(res);
	}
	else
	{
		send(clifd,"yes",20,0);
		mysql_free_result(res);
	}
	while(1)
	{
		sendmypublic(clifd,mysql,name,pubname);
		recv(clifd,recvbuf,2,0);
		if(strcmp("1",recvbuf)==0)
			view_members_ser(clifd,mysql,name,pubname);
		else if(strcmp("2",recvbuf)==0)
		{
			invite_members_ser(clifd,mysql,name,pubname);//邀请新成员
		}
		else if(strcmp("3",recvbuf)==0)
		{
			delete_members_ser(clifd,mysql,name,pubname);//踢人
		}
		else if(strcmp("4",recvbuf)==0)
			dropout_public_ser(clifd,mysql,name,pubname);//退群
		else if(strcmp("5",recvbuf)==0)
		{
			disbanded_public_ser(clifd,mysql,name,pubname);//解散群
			return;
		}
		else if(strcmp("6",recvbuf)==0)
			return;
	}
}
void disbanded_public_ser(int clifd,MYSQL* mysql,char* name,char* pubname)
{
	char chose[2];
	recv(clifd,chose,2,0);
	if(strcmp(chose,"n")==0)
	{
		return;
	}
	int t ;
	MYSQL_RES *res;
	MYSQL_ROW row;          // 返回行数据
	char query[200];
	//从Publics删除
	sprintf(query,"delete from Publics where public=\"%s\"",pubname);
	puts(query);
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		printf("Failed to query:%s\n", mysql_error(mysql)); 
    }
    res = mysql_store_result(mysql);
	mysql_free_result(res);
	//各个删除
	sprintf(query,"select name from %s",pubname);
	puts(query);
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		printf("Failed to query:%s\n", mysql_error(mysql)); 
    }
    res = mysql_store_result(mysql);
	while (row = mysql_fetch_row(res)) 
	{
		delete_mbdata(mysql,row[0],pubname);
	}
    mysql_free_result(res);
    //删除群表
    sprintf(query,"drop table %s",pubname);
	puts(query);
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		printf("Failed to query:%s\n", mysql_error(mysql)); 
    }
    res = mysql_store_result(mysql);
    mysql_free_result(res);
}
void delete_mbdata(MYSQL* mysql,char* mbname,char* pubname)
{
	int t ;
	MYSQL_RES *res;
	MYSQL_ROW row;          // 返回行数据
	char query[200];

	sprintf(query,"delete from %spu  where public=\"%s\"",mbname,pubname);
	puts(query);
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		printf("Failed to query:%s\n", mysql_error(mysql)); 
    }
    res = mysql_store_result(mysql);
    mysql_free_result(res);
}
void dropout_public_ser(int clifd,MYSQL* mysql,char* name,char* pubname)
{
	char chose[2];
	recv(clifd,chose,2,0);
	if(strcmp(chose,"n")==0)
	{
		return;
	}
	int t ;
	MYSQL_RES *res;
	MYSQL_ROW row;          // 返回行数据
	char query[200];

	sprintf(query,"delete from %s where name=\"%s\"",pubname,name);
	
	puts(query);
	
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		printf("Failed to query:%s\n", mysql_error(mysql)); 
    }
    res = mysql_store_result(mysql);
    mysql_free_result(res);
    //从自己列表删除
    sprintf(query,"delete from %spu where public=\"%s\"",name,pubname);
    t = mysql_real_query(mysql, query, strlen(query));

    if (t) 
    {
   		printf("Failed to query: %s\n", mysql_error(mysql)); 
   	}
    res = mysql_store_result(mysql);
    mysql_free_result(res);
}
void delete_members_ser(int clifd,MYSQL* mysql,char* name,char* pubname)
{
	int t;
    char query[200];
    MYSQL_RES *res;         // 返回查询结果
    MYSQL_ROW row;          // 返回行数据
	char chose[15];
	char friname[15];
	
	view_members_ser(clifd,mysql,name,pubname);
    recv(clifd,friname,15,0);
    if(strcmp(friname,"return")==0)
    	return;
    recv(clifd,chose,15,0);
    if(strcmp(chose,"y")==0)
    {

    	//从群列表删除
    	sprintf(query,"delete from %s where name=\"%s\"",pubname,friname);
    	t = mysql_real_query(mysql, query, strlen(query));

    	if (t) 
    	{
      	  	printf("Failed to query: %s\n", mysql_error(mysql)); 
    	}
    	res = mysql_store_result(mysql);
    	mysql_free_result(res);
    	//从对方列表删除
    	sprintf(query,"delete from %spu where public=\"%s\"",friname,pubname);
    	t = mysql_real_query(mysql, query, strlen(query));

    	if (t) {
      	  	printf("Failed to query: %s\n", mysql_error(mysql)); 
      	  	send(clifd,"Fail! Is not your friend",40,0);
      	  	res = mysql_store_result(mysql);
    		mysql_free_result(res);
     	   	return;
    	}
    	res = mysql_store_result(mysql);
    	mysql_free_result(res);
    	char buf[40];
    	sprintf(buf,"%s has been deleted",friname);
    	send(clifd,buf,40,0);
    	//删除聊天记录
    	
    }
    else
    	return;
}
void invite_members_ser(int clifd,MYSQL* mysql,char* name,char* pubname)
{
	char friname[15];
	recv(clifd,friname,15,0);
	
	int t ;
	MYSQL_RES *res;
	MYSQL_ROW row;          // 返回行数据
	char query[200];
	//检查用户是否存在
	sprintf(query,"select name from Accounts where name=\"%s\"",friname);
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		printf("Failed to query:%s\n", mysql_error(mysql)); 
    }
    res = mysql_store_result(mysql);
    if(mysql_fetch_row(res)==0) 
    {
    	mysql_free_result(res);
    	send(clifd,"This account does not exist",50,0);
    	return; 
    }
    mysql_free_result(res);
    
    //检测是否已经是群成员
    sprintf(query,"select * from %s where name=\"%s\"",pubname,friname);
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		printf("Failed to query:%s\n", mysql_error(mysql)); 
    }
    res = mysql_store_result(mysql);
    if(mysql_fetch_row(res)!=0) 
    {
    	mysql_free_result(res);
    	send(clifd,"Is already group menber",50,0);
    	return; 
    }
    mysql_free_result(res);
	
    //检测是否已经提交过请求
    sprintf(query,"select * from System where send=\"%s\" and recv=\"%s\" and user=0",pubname,friname);
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		printf("Failed to query:%s\n", mysql_error(mysql)); 
    }
    res = mysql_store_result(mysql);
    if(mysql_fetch_row(res)!=0)
    {
    	send(clifd,"A request has been submitted",50,0);
    	return;	
    }
    mysql_free_result(res);
	
	//提交请求	
	sprintf(query,"insert into System values(\"%s\",\"%s\",0)",pubname,friname);
	printf("%s\n", query); 
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		printf("Failed to addfriend:%s\n", mysql_error(mysql)); 
		send(clifd,"add friend fail",50,0);
		return;
    }
   	send(clifd,"success",50,0);
    res = mysql_store_result(mysql);
}
void view_members_ser(int clifd,MYSQL* mysql,char* name,char* pubname)
{

	char buf[200];
	int t ;
	MYSQL_RES *res;
	MYSQL_ROW row;          // 返回行数据
	char query[200];
	sprintf(query,"select name,position from %s ",pubname);
	puts(query);
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		printf("Failed to query:%s\n", mysql_error(mysql)); 
    }
    res = mysql_store_result(mysql);
    
	while(row=mysql_fetch_row(res)) 
	{
		sprintf(buf,"\t\t\t%s\t\t%s",row[0],row[1]);
		send(clifd,buf,200,0);
	}
	send(clifd,"\r\n",200,0); 
    mysql_free_result(res);
}
void sendmypublic(int clifd,MYSQL* mysql,char* name,char* pubname)
{
	char buf[200];
	int t ;
	MYSQL_RES *res;
	MYSQL_ROW row;          // 返回行数据
	char query[200];
	//创建群聊，并检测是否已经存在
	sprintf(query,"select public,position from %spu where public=\"%s\"",name,pubname);

	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		printf("Failed to query:%s\n", mysql_error(mysql)); 
    }
    res = mysql_store_result(mysql);
	while (row = mysql_fetch_row(res)) 
	{
		sprintf(buf,"\t\t\t%s\t\t%s",row[0],row[1]);
		send(clifd,buf,200,0);
	}
	send(clifd,"\r\n",200,0); 
    mysql_free_result(res);
}
void create_public_ser(int clifd,MYSQL* mysql,char*name)
{
	char pubname[50];
	recv(clifd,pubname,50,0);
	if(strcmp(pubname,"return")==0)
		return;
	int t ;
	MYSQL_RES *res;
	MYSQL_ROW row;          // 返回行数据
	char query[200];
	//创建群聊，并检测是否已经存在
	sprintf(query,"insert into Publics values(\"%s\")",pubname);

	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		send(clifd,"fail",20,0);
		printf("Failed to query:%s\n", mysql_error(mysql)); 
		return;
    }
    res = mysql_store_result(mysql);
    mysql_free_result(res);
    //建立群列表
    sprintf(query,"create table %s (name char(15) binary not null unique,position char(15) not null)",pubname);

	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		send(clifd,"fail",20,0);
		printf("Failed to query:%s\n", mysql_error(mysql)); 
		return;
    }
    res = mysql_store_result(mysql);
    mysql_free_result(res);
    //添加成员并设置群主
    sprintf(query,"insert into %s values (\"%s\",\"群主\")",pubname,name);

	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		printf("Failed to query:%s\n", mysql_error(mysql)); 
		return;
    }
    res = mysql_store_result(mysql);
    mysql_free_result(res);
    //添加群至创建者的表中
    sprintf(query,"insert into %spu values (\"%s\",0,\"群主\")",name,pubname);

	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		printf("Failed to query:%s\n", mysql_error(mysql)); 
		return;
    }
    
  	send(clifd,"success",20,0);
    res = mysql_store_result(mysql);
    mysql_free_result(res);
}
//动态打印好友列表
void* send_friendlistdata(data* pack)
{
	while(pack->flag)
	{
		send_friendlist(pack->clifd,pack->mysql,pack->name);
		sleep(3);
	}
	pack->flag=1;
	pthread_exit(0);
}
void send_friendlist(int clifd,MYSQL* mysql,char* name)
{
	int t;
    char query[200];
    MYSQL_RES *res;         // 返回查询结果
    MYSQL_ROW row;          // 返回行数据
	char buf[200];
	sprintf(query,"(select * from %sfr)",name);
    t = mysql_real_query(mysql, query, strlen(query));  

    if (t) {
        printf("Failed to query: %s\n", mysql_error(mysql));  
        return;
    }
    res = mysql_store_result(mysql);
    while (row = mysql_fetch_row(res)) 
    {  
        if(match_tabledata(mysql,"Online",row[0]))
        {
        	sprintf(buf,"\t\tOnline\t\t%s\t\t",row[0]);
        	strcat(buf,row[1]);
        	strcat(buf,"\t\t");
        	strcat(buf,row[2]);
        	send(clifd,buf,200,0);
        }
        else
        {
        	sprintf(buf,"\t\tOffline\t\t%s\t\t",row[0]);
        	strcat(buf,row[1]);
        	strcat(buf,"\t\t");
        	strcat(buf,row[2]);
        	send(clifd,buf,200,0);
        }
    } 
    send(clifd,"\r\n",200,0); 
    mysql_free_result(res);
}
int match_tabledata(MYSQL *mysql,char* tablename,char* name)
{
	int t ;
	MYSQL_RES *res;
	//MYSQL_ROW row;
	char query[200];
	sprintf(query,"select name from %s where name=\"%s\"",tablename,name);
	printf("%s\n", query); 
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		printf("Failed to query:%s\n", mysql_error(mysql)); 
    	return 0;	
    }
    res = mysql_store_result(mysql);
    if(mysql_fetch_row(res)) 
    {
    	mysql_free_result(res);
    	return 1; 
    }
    else
   	{ 
    	mysql_free_result(res);
    	return 0;
	}
}
void add_friend_ser(int clifd,MYSQL* mysql,char* name)
{
	int t ;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[200];
	char friname[15];
	recv(clifd,friname,15,0);
	
	//检查用户是否存在
	sprintf(query,"select name from Accounts where name=\"%s\"",friname);
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		printf("Failed to query:%s\n", mysql_error(mysql)); 
    }
    res = mysql_store_result(mysql);
    if(mysql_fetch_row(res)==0) 
    {
    	mysql_free_result(res);
    	send(clifd,"This account does not exist",40,0);
    	return; 
    }
    mysql_free_result(res);
    
    //检测是否已经是好友
    sprintf(query,"select friends from %sfr where friends=\"%s\"",name,friname);
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		printf("Failed to query:%s\n", mysql_error(mysql)); 
    }
    res = mysql_store_result(mysql);
    if(mysql_fetch_row(res)!=0) 
    {
    	mysql_free_result(res);
    	send(clifd,"Is already friends",40,0);
    	return; 
    }
    mysql_free_result(res);
	
    //检测是否已经提交过请求
    sprintf(query,"select * from System where send=\"%s\" and recv=\"%s\" and user=1",name,friname);
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		printf("Failed to query:%s\n", mysql_error(mysql)); 
    }
    res = mysql_store_result(mysql);
    if(mysql_fetch_row(res)!=0)
    {
    	send(clifd,"A request has been submitted",40,0);
    	return;	
    }
    mysql_free_result(res);
	
	//提交请求	
	sprintf(query,"insert into System values(\"%s\",\"%s\",1)",name,friname);
	printf("%s\n", query); 
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		printf("Failed to addfriend:%s\n", mysql_error(mysql)); 
		send(clifd,"add friend fail",40,0);
    }
   	send(clifd,"success",40,0);
    res = mysql_store_result(mysql);
}
void friend_notice_ser(int clifd,MYSQL* mysql,char* name)
{
	int t;
    char query[200];
    MYSQL_RES *res;         // 返回查询结果
    MYSQL_ROW row;          // 返回行数据
	char buf[200]={0};
	char friname[15];
	//发送好友请求给客户端
	sprintf(query,"select send,recv from System where recv=\"%s\" and user=1",name);
    t = mysql_real_query(mysql, query, strlen(query)); 

    if (t) {
        printf("Failed to query: %s\n", mysql_error(mysql));  
        return;
    }
    res = mysql_store_result(mysql);
    while (row = mysql_fetch_row(res)) 
    {  
        sprintf(buf,"\t\t\t%s\t\tAsking for friends",row[0]);
        send(clifd,buf,200,0);
    } 
    send(clifd,"\r\n",200,0);
    mysql_free_result(res);
    recv(clifd,friname,15,0);
    if(strcmp(friname,"return")==0)
    	return;
    recv(clifd,buf,15,0);
    if(strcmp(buf,"y")==0)
    {
    	//添加前再次检索
    	sprintf(query,"select * from System where send=\"%s\" and recv=\"%s\",user=1",friname,name);
    	t = mysql_real_query(mysql, query, strlen(query));

    	if (t) {
      	  	printf("Failed to query: %s\n", mysql_error(mysql)); 
     	   	return;
    	}
    	res = mysql_store_result(mysql);
    	if(mysql_fetch_row(res)==0)
   	 	{
			send(clifd,"Input error",40,0);
			return;	
    	}
    	mysql_free_result(res);
    	
    	//添加对方至自己的列表
    	sprintf(query,"insert into %sfr value(\"%s\",0,0)",name,friname);
    	t = mysql_real_query(mysql, query, strlen(query)); 

    	if (t) {
      	  	printf("Failed to query: %s\n", mysql_error(mysql));  
     	   	return;
    	}
    	res = mysql_store_result(mysql);
    	mysql_free_result(res);
    	
    	//添加自己到对方列表
    	sprintf(query,"insert into %sfr value(\"%s\",0,0)",friname,name);
    	t = mysql_real_query(mysql, query, strlen(query)); 

    	if (t) {
      	  	printf("Failed to query: %s\n", mysql_error(mysql));  
     	   	return;
    	}
    	res = mysql_store_result(mysql);
    	mysql_free_result(res);
    	
    	//删除通知
    	sprintf(query, "delete from System where send=\"%s\" and recv=\"%s\" user=1", friname,name);
    	printf("%s\n", query);

    	t = mysql_real_query(mysql, query, strlen(query));
    	if (t) {  
        	printf("Failed to delete: %s\n", mysql_error(mysql));  
        	return;
    	}
    	mysql_free_result(res);
    	send(clifd,"You have become friends, you can chat with each",200,0);
	}
	else
	{
		sprintf(query, "delete from System where send=\"%s\" and recv=\"%s\" user=1", friname,name);
    	printf("%s\n", query);

    	t = mysql_real_query(mysql, query, strlen(query));
    	if (t) {  
        	printf("Failed to delete: %s\n", mysql_error(mysql));  
        	return;
    	}
    	mysql_free_result(res);
	}    
    
}
void delete_friend_ser(int clifd,MYSQL* mysql,char* name)
{
	int t;
    char query[200];
    MYSQL_RES *res;         // 返回查询结果
    MYSQL_ROW row;          // 返回行数据
	char chose[15];
	char friname[15];
	
	send_friendlist(clifd,mysql,name);
    recv(clifd,friname,15,0);
    if(strcmp(friname,"return")==0)
    	return;
    recv(clifd,chose,15,0);
    if(strcmp(chose,"y")==0)
    {

    	//从自己列表删除
    	sprintf(query,"delete from %sfr where friends=\"%s\"",name,friname);
    	t = mysql_real_query(mysql, query, strlen(query));

    	if (t) 
    	{
      	  	printf("Failed to query: %s\n", mysql_error(mysql)); 
     	   	return;
    	}
    	res = mysql_store_result(mysql);
    	mysql_free_result(res);
    	//从对方列表删除
    	sprintf(query,"delete from %sfr where friends=\"%s\"",friname,name);
    	t = mysql_real_query(mysql, query, strlen(query));

    	if (t) {
      	  	printf("Failed to query: %s\n", mysql_error(mysql)); 
      	  	send(clifd,"Fail! Is not your friend",40,0);
      	  	res = mysql_store_result(mysql);
    		mysql_free_result(res);
     	   	return;
    	}
    	res = mysql_store_result(mysql);
    	mysql_free_result(res);
    	char buf[40];
    	sprintf(buf,"%s has been deleted",friname);
    	send(clifd,buf,40,0);
    	//删除聊天记录
    	
    }
    else
    	return;
}
void chat_friend_ser(int clifd,MYSQL* mysql,char* name)
{
	char friname[15];
	send_friendlist(clifd,mysql,name);
	recv(clifd,friname,15,0);
	puts(friname);
	if(strcmp(friname,"return")==0)
		return;
	int t ;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[200];
	
    //检测是否是好友
    sprintf(query,"select friends from %sfr where friends=\"%s\"",name,friname);
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		printf("Failed to query:%s\n", mysql_error(mysql)); 
    }
    res = mysql_store_result(mysql);
    if(mysql_fetch_row(res)==0) 
    {
    	mysql_free_result(res);
    	send(clifd,"is not your friends",40,0);
    	return; 
    }
    mysql_free_result(res);
    send(clifd,"success",40,0);
    chat mess;
    pthread_t thid;
    datapu* pack=(datapu*)malloc(sizeof(datapu));
    pack->flag=1;
	pack->clifd=clifd;
	pack->mysql=mysql;
	strcpy(pack->name,name);
	strcpy(pack->friname,friname);
	pthread_create(&thid,NULL,(void*)send_frhistory,(void*)pack);       //动态更新好友消息记录
    while(1)
    {
		
		myrecv(clifd,(char*)&mess,sizeof(chat));
		if(strcmp(mess.news,"return")==0)
		{
			pack->flag=0;
			free(pack);
			break;
		}
		//消息入库
		sprintf(query,"insert into Message value(\"%s\",\"%s\",\"%s\",\"%s\")",mess.time,name,friname,mess.news);
		t = mysql_real_query(mysql, query, strlen(query));
		if (t) 
		{
			printf("Failed to query:%s\n", mysql_error(mysql)); 
		}
		res = mysql_store_result(mysql);
		mysql_free_result(res);
		//添加未读标记
		sprintf(query,"update %sfr set count=count+1 where friends=\"%s\"",friname,name);
		t = mysql_real_query(mysql, query, strlen(query));
		if (t) 
		{
			printf("Failed to query:%s\n", mysql_error(mysql)); 
		}
		res = mysql_store_result(mysql);
		mysql_free_result(res);
	}
	sprintf(query,"update %sfr set count=0 where friends=\"%s\"",name,friname);
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) 
	{
		printf("Failed to query:%s\n", mysql_error(mysql)); 
	}
	res = mysql_store_result(mysql);
	mysql_free_result(res);
}
void* send_frhistory(datapu* pack)
{
	while(pack->flag)
	{
		send_friend_history(pack->clifd,pack->mysql,pack->name,pack->friname);
		sleep(5);
	}
	pack->flag=1;
	pthread_exit(0);
}
void send_friend_history(int clifd,MYSQL* mysql,char* name,char* friname)
{
	int t;
    char query[200];
    char buf[500];
    MYSQL_RES *res;         // 返回查询结果
    MYSQL_ROW row;          // 返回行数据
	//发送消息给客户端
	sprintf(query,"select * from Message where send=\"%s\" and recv=\"%s\" or send=\"%s\" and recv=\"%s\"",name,friname,friname,name);
    t = mysql_real_query(mysql, query, strlen(query)); 
    if (t) 
    {
        printf("Failed to query: %s\n", mysql_error(mysql));  
        return;
    }
    res = mysql_store_result(mysql);
    while (row = mysql_fetch_row(res)) 
    {  
        sprintf(buf,"%s\t%s @ %s : %s",row[0],row[1],row[2],row[3]);
        send(clifd,buf,500,0);
    } 
    send(clifd,"\r\n",500,0);
    mysql_free_result(res);
}
void file_ser(int clifd,MYSQL* mysql,char* name)
{
	char chose[15];

	while(1)
	{
		send_friendlist(clifd,mysql,name);
		
		recv(clifd,chose,15,0);
		
		if(strcmp("1",chose)==0)
			sendfile_ser(clifd,mysql,name);
		else if(strcmp("2",chose)==0)
			recvfile_ser(clifd,mysql,name);
		else if(strcmp("3",chose)==0)
			return;
	}
}
void sendfile_ser(int clifd,MYSQL* mysql,char* name)  //发送文件
{
	char friname[15];
	char chose[15];
	char buf[1024];
	int size;
	int t;
	int sendfd;
    char query[200];
    MYSQL_RES *res;         // 返回查询结果
    MYSQL_ROW row;          // 返回行数据

	recv(clifd,friname,15,0);
	if(strcmp(friname,"return")==0)
	{
		return;
	}
	puts(friname);///////////////////
	
	/////////////////////////////////////////////////////
	//是否为好友
	sprintf(query,"select * from %sfr where friends=\"%s\"",name,friname);
    t = mysql_real_query(mysql, query, strlen(query));

    if (t) {
       	printf("Failed to query: %s\n", mysql_error(mysql));
       	return;
    }
    res = mysql_store_result(mysql);
    puts(query);
    if(mysql_fetch_row(res)==0)
   	{
		send(clifd,"is not you friend",40,0);
		return;	
    }
    mysql_free_result(res);
    //是否在线
    /*
    sprintf(query,"select * from Online where name=\"%s\"",friname);
    t = mysql_real_query(mysql, query, strlen(query));

    if (t) {
       	printf("Failed to query: %s\n", mysql_error(mysql));
       	return;
    }
    res = mysql_store_result(mysql);
    if(row = mysql_fetch_row(res)) 
    {  	
        sendfd=atoi(row[1]);
        printf("fuckfuck%d\n",sendfd);
    } 
    else
   	{
		send(clifd,"is not online",40,0);
		return;	
    }
    mysql_free_result(res);
    */
    //是否已有文件请求
    
    /*sprintf(query,"select * from %sfr where filecount=9999",friname,name);
    t = mysql_real_query(mysql, query, strlen(query));
    if (t) {
       	printf("Failed to query: %s\n", mysql_error(mysql));
       	return;
    }
    res = mysql_store_result(mysql);
    if(mysql_fetch_row(res)) 
    {  	
        send(clifd,"already has a task",40,0);
        return;
    } 
    mysql_free_result(res);
    */
	//提醒有文件
	sprintf(query,"update %sfr set filecount=filecount+1 where friends=\"%s\"",friname,name);
    t = mysql_real_query(mysql, query, strlen(query));
    if (t) {
       	printf("Failed to query: %s\n", mysql_error(mysql));
       	return;
    }
    res = mysql_store_result(mysql);
    mysql_free_result(res);
    /*
    //等待回应
    recv(sendfd,chose,15,0);
    if(strcmp(chose,"n")==0)
    {
    	send(clifd,"rejected your request",40,0);
    	goto rejected;
    }
    send(clifd,"success",40,0);
    char filename[256];
	recv(clifd,filename,256,0);
	send(sendfd,filename,256,0);
	int len;
	while(recv(clifd,(void*)&size,4,0))
	{
		myrecv(clifd,buf,size);
		send(sendfd,(void*)&size,4,0);
		len=send(sendfd,buf,size,0);
		printf("size=%d len=%d \n",size,len);
		if(size<1024)
			break;
	}
rejected:
	sprintf(query,"update %sfr set filecount=0 where friends=\"%s\"",friname,name);
    t = mysql_real_query(mysql, query, strlen(query));
    if (t) {
       	printf("Failed to query: %s\n", mysql_error(mysql));
       	return;
    }
    res = mysql_store_result(mysql);
    mysql_free_result(res);
    */

	///////////////////////////////////////////////////
	//服务端接收客户端文件
	char filename[256];
	recv(clifd,filename,256,0);
	char path[256];
	sprintf(path,"file/%s",friname);
	chdir(path);
	FILE* fp=fopen(filename,"w");
	int len;
	while(recv(clifd,(void*)&size,4,0))
	{
		myrecv(clifd,buf,size);
		len=fwrite(buf,1,size,fp);
		printf("size=%d len=%d \n",size,len);
		if(size<1024)
			break;
	}
	fclose(fp);
	chdir("../..");
	sprintf(query,"insert into Files values (\"%s\",\"%s\",\"%s\")",name,friname,filename);
    t = mysql_real_query(mysql, query, strlen(query));
    if (t) {
       	printf("Failed to query: %s\n", mysql_error(mysql));
       	return;
    }
    res = mysql_store_result(mysql);
    mysql_free_result(res);
	
	/////////////////////////////////////////////////////

}
void recvfile_ser(int clifd,MYSQL* mysql,char* name)
{
	int t;
	int sendfd;
    char query[200];
    char buf[1024];
    MYSQL_RES *res;         // 返回查询结果
    MYSQL_ROW row;          // 返回行数据

	sprintf(query,"select send,filename from Files where recv=\"%s\"",name);
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) {
	   	printf("Failed to query: %s\n", mysql_error(mysql));
	   	return;
	}
	res = mysql_store_result(mysql);
    while (row = mysql_fetch_row(res)) 
    {
        sprintf(buf,"\t\t%s\t%s",row[0],row[1]);
        send(clifd,buf,500,0);
    } 
    send(clifd,"\r\n",500,0);
    mysql_free_result(res);
    char friname[15];
    char filename[50];
    recv(clifd,friname,15,0);
    recv(clifd,filename,50,0);
    sprintf(query,"select * from Files where recv=\"%s\" and send=\"%s\" and filename=\"%s\"",name,friname,filename);
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) {
	   	printf("Failed to query: %s\n", mysql_error(mysql));
	   	return;
	}
	res = mysql_store_result(mysql);
    if(mysql_fetch_row(res))
    {
    	send(clifd,"success",20,0);
    }
    else
    {
    	send(clifd,"fail",20,0);
    	return;
    }
    char path[256];
    sprintf(path,"file/%s/%s",name,filename);
    FILE* fp=fopen(path,"r");
    int size,len;
    while((size=fread(buf,1,1024,fp))>0)
	{
		send(clifd,(void*)&size,4,0);
		len=send(clifd,buf,size,0);
		printf("size=%d len=%d \n",size,len);
	}
	fclose(fp);
	sprintf(query,"delete from Files where recv=\"%s\" and send=\"%s\" and filename=\"%s\"",name,friname,filename);
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) {
	   	printf("Failed to query: %s\n", mysql_error(mysql));
	   	return;
	}
	res = mysql_store_result(mysql);
	sprintf(query,"update %sfr set filecount=filecount-1",name);
	t = mysql_real_query(mysql, query, strlen(query));
	if (t) {
	   	printf("Failed to query: %s\n", mysql_error(mysql));
	   	return;
	}
	res = mysql_store_result(mysql);
	remove(path);
}

void close_connection(MYSQL *mysql)
{
    mysql_close(mysql);
}
