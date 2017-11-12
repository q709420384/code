/*************************************************************************
	> File Name: 1.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年11月03日 星期五 16时07分41秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

#define COUNT 10
static int i = 1;
pthread_mutes_t mutex = PTHREAD_MUTEX_INITIALIZER;

//1 3 5 7 9
void* A_fun(void *arg)
{
    while(i <= COUNT)
    {
        pthread_mutes_lock(&mutex);
        if(i%2 == 1)
            printf("奇数: %d\n", i);

    }
}
//2 4 6 8 10
void* B_fun(void *arg)
{
    
}

int main()
{
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, A_fun, NULL);
    pthread_create(&tid2, NULL, B_fun, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}
