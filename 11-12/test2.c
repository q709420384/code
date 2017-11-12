/*************************************************************************
	> File Name: test2.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年11月12日 星期日 14时40分11秒
 ************************************************************************/

#include<stdio.h>

int min(int a, int b);

int main()
{
    printf("min = %d\n",min(100, 10));
}

int min(int a, int b)
{
    return a<b?a:b;
}
