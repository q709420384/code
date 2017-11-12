#include <stdio.h>
#include <stdlib.h>

#define MAX 7
int x[9]={0,-1,1,2,2,1,-1,-2,-2};
int y[9]={0,2,2,1,-1,-2,-2,-1,1};
int count = 1;
typedef struct stack
{
	int x;
	int y;
	int p;
}stack;
stack horse[100];

void printarr(int chees[][MAX])
{
	int i,j;
	for(i= 0 ;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
			printf("%5d",chees[i][j]);
		}
		printf("\n");
	}
}

void hchees(int chees[][MAX],int step_x,int step_y)
{
	int i ,j , f ,xx ,yy;
	chees[step_x][step_y]=count;
	horse[count].x = step_x;
	horse[count].y = step_y;
	while(count != MAX * MAX)
	{
		f = 1;
		for( i = horse[count].p+1;i<9;i++)
		{
			xx=horse[count].x+x[i];
			yy=horse[count].y+y[i];
			if(xx>-1 && xx<MAX && yy>-1 && yy<MAX && chees[xx][yy]==0)
			{
					horse[count].p = i;
					count ++;
					horse[count].x = xx;
					horse[count].y = yy;
					chees[horse[count].x][horse[count].y]=count;
					f = 0;
					//printf("%d\n",count);
					break;
			}
		}
		if(f)
		{
			horse[count].p = 0;
			chees[horse[count].x][horse[count].y]=0;
			count--;

		}
	}
}

int main() 
{
	int chees[MAX][MAX];
	int i ,j;
	
	for(i= 0 ;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
			chees[i][j] = 0;
		}
	}
	int z,h;
	printf("请输入横纵坐标中间以逗号隔开：\n");
	scanf("%d,%d",&h,&z);
    hchees(chees,h,z);
	printarr(chees);
	return 0;
}

