/*************************************************************************
	> File Name: ser.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年11月11日 星期六 11时14分00秒
 ************************************************************************/

#include"utili.h"

int sockSer;
void* talk(void *arg)
{
	int clifd = *(int*)arg;
	char buff[BUFFER_SIZE];
	while(1)
    {
    	recv(sockConn, buff, BUFFER_SIZE, 0);
    	if(strcmp(buff,"return") == 0)
    		break;
        printf("Cli:>%s\n",buff);
        printf("Ser:>%s\n",buff);
        send(sockConn, sendbuf, strlen(sendbuf)+1,0);
    }
    pthread_exit(0);
}
void closeSer()
{
	close(sockSer);
	exit(0);
}
int main()
{
    sockSer = socket(AF_INET, SOCK_STREAM, 0);
    int i=0;
    if(sockSer == -1)
    {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in addrSer, addrCli;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(SERVER_PORT);
    addrSer.sin_addr.s_addr = inet_addr(SERVER_IP);

    socklen_t len = sizeof(struct sockaddr);
    int ret = bind(sockSer, (struct sockaddr*)&addrSer, len);
    if(ret == -1)
    {
        perror("bind");
        exit(1);
    }

    ret = listen(sockSer, LISTEN_QUEUE_SIZE);
    if(ret == -1)
    {
        perror("listen");
        exit(1);
    }
    
    struct sigaction act;
    act.sa_handler = closeSer;
	sigaction(SIGINT, &act, NULL);
	
    pthread_t pid[30];
    
	while(1)
	{
    	int sockConn = accept(sockSer, (struct sockaddr*)&addrCli, &len);
		if(sockConn == -1)
		{
		    printf("Server Accept Client Connect Fail.\n");
		    exit(1);
		}
		else
		{
		    printf("Server Accept Client Connect Success.\n");
		}
		pthread_creadte(&pid[i], NULL, talk, (void)&sockConn);
		i++;
    }
}

