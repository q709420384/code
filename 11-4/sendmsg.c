/*************************************************************************
	> File Name: sendmsg.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年11月04日 星期六 13时38分08秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define BUF_SIZE  256
#define PROJ_ID   32
#define PATH_NAME "."

int main()
{
    /*自定义消息缓冲*/
    struct mymsgbuf
    {
        long msgtype;
        char ctrlstring[BUF_SIZE];
    }msgbuffer;

    int qid; //消息队列标识符
    int msglen;
    key_t msgkey;

    /*获取键值*/
    if((msgkey = ftok(PATH_NAME, PROJ_ID)) == -1)
    {
        perror("ftok error! \n");
        exit(1);
    }
    /*创建消息队列*/
    if((qid = msgget(msgkey, IPC_CREAT|0660) == -1))
    {
        perror("msgget error! \n");
        exit(1);
    }
    
    /*填充消息结构，发送到消息队列*/
    msgbuffer.msgtype = 3;
    strcpy(msgbuffer.ctrlstring, "Hello message queue");
    msglen = sizeof(struct mymsgbuf) - sizeof(long);
    if(msgsnd(qid, &msgbuffer, msglen, 0) == -1)
    {
        perror("msgget error!\n");
        exit(1);
    }

    exit(0);

}
