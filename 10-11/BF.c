/*************************************************************************
	> File Name: BF.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年10月11日 星期三 15时44分13秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>

int myindex(char * s,int pos,char * t)
{
    int i = pos,j=0;
    while(i<strlen(s)&&j<strlen(t))
    {
        if(s[i]==t[j])
        {
            i++;
            j++;
        }
        else
        {
            i=i-j+1;
            j=0;
        }
    }
    if(j>=strlen(t))
        return i-j;
    return 0;
}

int main()
{
    char* s="qweasdzxc";
    char* t1="asdz";
    char* t2="dzxc";
    printf("%d\n",myindex(s,0,t1));
    printf("%d\n",myindex(s,0,t2));
    printf("%d\n",myindex(s,6,t2));
}
