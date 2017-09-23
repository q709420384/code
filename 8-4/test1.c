#include<stdio.h>
#include<string.h>

int cc(char *p)
{
    int i,j,len=strlen(p),f=1;
    char temp[90];
    for(i=1;i<len;i++)
    {   
        strncpy(temp,p,i);
        for(j=i;j<len;j+=i)
        {
            if(len%j!=0)
                continue;
            if(strncmp(temp,p+j,i)!=0)
            {
                f=0;
                break;
            }
        }
        if(f)
        {
            return i;
        }
    }
}
int main()
{
    int n;
    char str[90];
    scanf("%d",&n);
    while(n--)
    {
        scanf("%s",str);
        printf("%d\n",cc(str));
        
    }
}
