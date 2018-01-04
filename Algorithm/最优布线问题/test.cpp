/*************************************************************************
	> File Name: test.cpp
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年11月20日 星期一 21时21分57秒
 ************************************************************************/

#include <iostream>  
#include <stdio.h>  
#include <algorithm>  
 
using namespace std;  
int Father[100001];  
struct node  
{  
    int a,b,w;  
    bool operator<(const node &t)const  
    {  
        return w<t.w;  
    }  
};  
int Find(int x)  
{  
	while(x!=Father[x])
	{
		x = Father[x];
	}
    return Father[x];  
}  
int main()  
{  
    int n,m;  
    node num[100001];
   	while(scanf("%d %d",&n, &m)!=EOF)
   	{
   		long long sum = 0;
   		for(int i = 1; i<=m; i++)
   		{
   			Father[i] = i;
   		}
   		for(int i = 0; i<m; i++)
   		{
   			scanf("%d %d %d",&num[i].a, &num[i].b, &num[i].w);
   		}
   		sort(num, num+m);
   		for(int i = 0; i<m; i++)
   		{
   			int x = Find(num[i].a);
   			int y = Find(num[i].b);
   			if(x!=y)
   			{
   				Father[x] = y;
   				sum += num[i].w;
   			}
   		}
   		cout<<sum<<endl;
   	}
    return 0;  
}

