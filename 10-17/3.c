/*************************************************************************
> File Name: 3.c
> Author:Sanjingye 
> Mail: 
> Created Time: 2017年10月17日 星期二 21时41分55秒
************************************************************************/

#include<stdio.h>

void replace(char* r,char ch1,char ch2)
{
    int i=0;
    while(r[i]!='\0')
    {
        if(r[i]==ch1)
        {
            r[i]=ch2;
        }
        i++;
    }
}
char* delete(char* r,char ch)
{ 
    int i=0; 
    int len=r.len; 
    while (i<len) 
    { 
        if (r->vec[i]==ch}  
            {
                for(j=i; j<len-1; j++) 
                r->vec[j]=r-vec[j+1]; 
                len--;
            } 
        else
            i++;
}
int position(str r1,int index,char r2)  
{ 
	if(index<1||index>r.len) 
		return ERROR; 
	int i=index;  
	while (r,vec[i]!=r2&&i<r.len)  
		i++; 
	if (i=r.len)  
	{
		cout<<”不存在”;
		return; 
	} 
	return i+1; 
}
void converse(str *r) 
{ 
	for(int i=0;i<(r->len/2);i++)    
	{
		char ch=r->vec[i];  
		r->vec[i]=r->vec[r->len-1-i]; 
		r->vec[r->len-1-i]=ch;
	}   
		return; 
}
int main()
{
	char *str="asdaaasd";
	printf("%s \n",delete(str,'a'));
}
