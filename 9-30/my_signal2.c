/*************************************************************************
	> File Name: my_signal.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年09月27日 星期三 21时35分44秒
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
int temp = 0;

void handler_sigint(int signo)
{
    printf("recv SIGINT\n");
    sleep(3);
    temp++;
    printf("the value of temp is : %d \n",temp);
    printf("in handler_sigint , after sleep \n");
}

int main()
{
    signal(SIGINT,handler_sigint);
    while(1);
    return 0;
}
