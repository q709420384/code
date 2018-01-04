#include"../utili.h"

int con_service();
void setop(char* op, calcst* oper);

int main()
{
	int sockfd = con_service();
	calcst oper;
    int result;
    char op[10];
    while(1)
    {
    	printf("请输入op1和op2:");
    	scanf("%d %d",&oper.op1, &oper.op2);
    	printf("%d + %d \n",oper.op1,oper.op2);
    haha:
    	printf("请输入操作符:");
    	gets(op);
    	setop(op,&oper);
    	if(oper.op == NOINPUT)
    		goto haha;
    	else
    		send(sockfd, (void*)&oper, sizeof(calcst), 0);
    	recv(sockfd, &result, sizeof(result), 0);
    	printf("result = %d \n",result);
    }
}

int con_service()
{
	int				conn_fd;
	struct sockaddr_in serv_addr;

	memset(&serv_addr,0,sizeof(struct sockaddr_in));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(9090);
	if(inet_aton(IP,&serv_addr.sin_addr)==0)
	{
		printf("invalid server ip address\n");
		exit(1);
	}
	conn_fd=socket(AF_INET,SOCK_STREAM,0);
	if(conn_fd<0)
		perror("socket");
	if(connect(conn_fd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr))<0)
		perror("connect");
	else
	{
		printf("Connect process!\n");
		return conn_fd;
	}
}
void setop(char* op, calcst* oper)
{
	if(strcmp(op,"+")==0)
    {
       oper->op = ADD;
    }
    else if(strcmp(op,"-")==0)
    {
        oper->op = SUB;
    }
    else if(strcmp(op,"*")==0)
    {
        oper->op = MUL;
    }
    else if(strcmp(op,"/")==0)
    {
        oper->op = DIV;
    }
    else if(strcmp(op,"/")==0)
    {
        oper->op = MOD;
    }
    else
    	oper->op = NOINPUT;
}
