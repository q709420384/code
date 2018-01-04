/*************************************************************************
	> File Name: size.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年12月25日 星期一 19时10分49秒
 ************************************************************************/

#include<stdio.h>
#include<sys/socket.h>

int main()
{
    struct sockaddr_storage a;
    printf("sa_family_t = %d __ss_padding = %d\n", sizeof(a), sizeof(a.__ss_padding));
    return 0;
}
