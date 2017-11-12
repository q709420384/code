/*************************************************************************
	> File Name: wrong_return.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年10月24日 星期二 21时43分21秒
 ************************************************************************/

#include<stdio.h>
#include<setjmp.h>
#include<signal.h>

jmp_buf env ;
void handler_sigrtmin15(int signo)
{
    printf("recv SIGNRTMIN+15 \n");
    longjmp(env,1);
}
void handler_sigrtmax15(int signo)
{
    printf("recv SIGRTMAX-15");
    longjmp(env,2);
}
int main()
{
    switch(setjmp(env))
    {
        case 0:
            break;
        case 1:
            printf("return from SIGRTMIN+15\n");
            break;
        case 2:
            printf("return from SIGRTMAX-15\n");
            break;
        default:
            break;
    }
    signal(SIGINT,handler_sigrtmin15);
    signal(SIGRTMAX-15,handler_sigrtmax15);
    while(1);
    
    return 0;
}
