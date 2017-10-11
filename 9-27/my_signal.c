/*************************************************************************
	> File Name: my_signal.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年09月27日 星期三 21时35分44秒
 ************************************************************************/

#include<stdio.h>
#include<signal.h>

void handler_sigint(int signo)
{
    printf("recv SIGINT\n");
}

int main()
{
    signal(SIGINT,handler_sigint);
    while(1);
    return 0;
}
