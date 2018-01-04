/*************************************************************************
	> File Name: ipchange.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年12月25日 星期一 19时52分22秒
 ************************************************************************/

#include<stdio.h>
#include<arpa/inet.h>

int main()
{
    
    printf("%s\n", inet_addr("1.2.3.4"));
    printf("%s\n", inet_addr("10.194.71.60"));
}
