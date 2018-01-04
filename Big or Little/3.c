/*************************************************************************
	> File Name: 3.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年12月25日 星期一 16时49分45秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    short a = 0x1122;
    char b = a;
    if(b == 0x11)
    {
        printf("big endian\n");
    }
    else if(b == 0x22)
    {
        printf("little endian\n");
    }
}
