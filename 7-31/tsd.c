#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
pthread_key_t key;
int tsd;
int ff(int a)
{
	a+=2;
}
void* thread2(void* arg)
{
    tsd=5;
    printf("thread2 %d is running\n",pthread_self());
    pthread_setspecific(key,(void *)tsd);
    printf("thread2 %d returns %d\n",pthread_self(),pthread_getspecific(key));
    pthread_exit(0);
}
void* thread1(void* arg)
{
    tsd=0;
    pthread_t thid2;
    pthread_t assisthid;
    int status;
    printf("thread1 %d is running\n",pthread_self());
    pthread_setspecific(key,(void *) tsd);
    pthread_create(&thid2,NULL,thread2,NULL);
    sleep(5);
    pthread_join(thid2,(void*)&status);
    printf("thread1 %d returns %d \n",pthread_self(),pthread_getspecific(key));
    pthread_exit(0);
    
}
int main()
{
    pthread_t thid1;
    int status;
    printf("main thread begins running\n");
    pthread_key_create(&key,NULL);
    pthread_create(&thid1,NULL,thread1,NULL);
    
    //sleep(3);
	pthread_join(thid1,(void*)&status);
    pthread_key_delete(key);
    printf("main thread exit\n");
    pthread_exit(0);
}
