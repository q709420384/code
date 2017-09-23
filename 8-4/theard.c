#include<stdio.h>
#include<pthread.h>
#include<sys/time.h>

int main()
{
    struct timeval start;
    struct timeval end;
    unsigned long timer;

    gettimeofday(&start,NULL);
    printf("Hello world !\n");
    gettimeofday(&end,NULL);
    timer=1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
    printf("timer=%ld us\n",timer);
    return 0;
}
