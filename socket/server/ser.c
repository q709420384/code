/*************************************************************************
	> File Name: ser.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年11月18日 星期六 10时25分01秒
 ************************************************************************/

#include"../utili.h"

void process_handler(int sockConn);
int main()
{
    int sockSer = start_up(9090);
    printf("Server Wait Client Connect......\n");

    
    struct sockaddr_in addrCli;
    socklen_t len = sizeof(struct sockaddr);
    int sockConn;
    while(1)
    {
        sockConn = accept(sockSer, (struct sockaddr*)&addrCli, &len);
        if(sockConn == -1)
        {
            perror("accept Client Connect Error.");
            continue;
        }
        printf("<=============Client===============>\n");
        printf("<   ip = %s\n", inet_ntoa(addrCli.sin_addr));
        printf("<   port = %d\n", ntohs(addrCli.sin_port));
        printf("<==================================>\n");

        pid_t pid = fork();
        if(pid == 0)
        {
        	//printf("hahah\n");
            process_handler(sockConn);
        }
        
    }
}

void process_handler(int sockConn)
{
    calcst oper;
    int result;
    while(1)
    {
        myrecv(sockConn, (char*)&oper, sizeof(calcst));
        
        if(oper.op == ADD)
        {
            result = oper.op1 + oper.op2;
        }
        else if(oper.op = SUB)
        {
            result = oper.op1 - oper.op2;
        }
        else if(oper.op = MUL)
        {
            result = oper.op1 * oper.op2;
        }
        else if(oper.op = DIV)
        {
            result = oper.op1 / oper.op2;
        }
        else if(oper.op = MOD)
        {
            result = oper.op1 % oper.op2;
        }
        printf("%d + %d = %d\n",oper.op1,oper.op2,result);
        send(sockConn, &result, sizeof(int), 0);
    }

}
