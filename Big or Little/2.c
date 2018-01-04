/*************************************************************************
	> File Name: 2.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年12月25日 星期一 16时42分56秒
 ************************************************************************/

#include<stdio.h>
void byteorder()
{
    union
    {
        short value;
        char union_bytes[sizeof(short)];
    }test;
    test.value = 0x0102;
    if((test.union_bytes[0] == 1) && (test.union_bytes[1] == 2))
    {
        printf("big endian.\n");

    }
    else if((test.union_bytes[0] == 2) && (test.union_bytes[1] == 1))
    {
        printf("little endian.\n");
    }
    else
    {
        printf("unknown...\n");
    }
}
int main()
{
    byteorder();
    return 0;
}
