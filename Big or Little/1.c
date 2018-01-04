#include<stdio.h>  
int main()  
{  
    char c;  
    int a=1;  
    int *p=&a;  
    c = *p;  
    if(c==a)  
    {  
        printf("xiaoduan\n");  
    }  
    else  
    {  
        printf("daduan\n");  
    }  
  
return 0;     
  
  
}
