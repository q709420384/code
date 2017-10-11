/*************************************************************************
	> File Name: horse.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年09月28日 星期四 11时29分26秒
 ************************************************************************/

#include<stdio.h>
#define M 8
int fx[8] = {1,2,2,1,-1,-2,-2,-1};
int fy[8]= {2,1,-1,-2,-2,-1,1,2};
int desk[M][M];

void Output()
{
    int i,j;
    for(i=0;i<M;i++)
    {
        for(j=0;j<M;j++)
            printf("%3d",desk[i][j]);
        printf("\n");
    }
}
int check(int xx,int yy)
{
    if(xx>=0&&xx<M&&yy>=0&&yy<M&&desk[xx][yy]==0)
        return 1;
    return 0;
}
int Find(int x,int y,int dep)
{
    int xx,yy,i;
    for(i=0;i<8;i++)
    {
        xx=x+fx[i];
        yy=y+fy[i];
        if(check(xx,yy)==1)
        {
            desk[xx][yy]=dep;
            if(dep==64)
            {
                Output();
                return 1;
            }
            if(Find(xx,yy,dep+1)==1)
                return 1;
            else
                desk[xx][yy]=0;
        }
    }
    return 0;
}
int main()
{
    int i,j,x,y;
    for(i=0;i<M;i++)
    {
        for(j=0;j<M;j++)
        {
            desk[i][j]=0;
        }
    }
    printf("请输入x y:");
    scanf("%d %d",&x,&y);
    desk[x-1][y-1]=1;
    if(Find(x-1,y-1,2)==1)
        printf("Success!\n");
    else
        printf("Failed!\n");
}
