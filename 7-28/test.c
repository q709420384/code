#include<stdio.h>
#include<string.h>
int vis[20],a[20];
int n;

int isp(int n)
{
    if(n<2)
        return 0;
    for (int i=2;i*i<=n; i++)
    {
        if(n % i == 0)
            return 0;
    }
    return 1;
}

void dfs(int s)
{
    if(s==n&&isp(a[1]+a[n]))
    {
        for(int i=1;i<n;i++)
            printf("%d ",a[i]);
        printf("%d\n",a[n]);
    }
    else
    {
        for(int i=2;i<=n;i++)
        {
            if(!vis[i]&&isp(i+a[s]))
            {
                a[s+1]=i;
                vis[i]=1;
                dfs(s+1);
                vis[i]=0;
            }
        }
    }
}
int main()
{
    int t=0;
    while(scanf("%d",&n)!=EOF)
    {
        memset(vis,0,sizeof(vis));
        a[1]=1;
        if(t!=0)
            printf("\n");
        t++;
        printf("Case %d:\n",t);
        dfs(1);
    }
}
