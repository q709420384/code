#include <stdio.h>
#include <stdlib.h>

#define MAX 8
int fx[9]={0,-1,1,2,2,1,-1,-2,-2};
int fy[9]={0,2,2,1,-1,-2,-2,-1,1};
int count = 1;
int F[9];
typedef struct stack
{
	int x;
	int y;
	int p[9];
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
int minIndex(int* F)
{
    int i,min=9,index=9;
    for(i=1;i<9;i++)
    {
        if(F[i]!=-1&&F[i]<min)
        {
            min=F[i];
            index=i;
        }
    }
    return index;
}
void hchees(int chees[][MAX],int step_x,int step_y)
{
	int i ,j ,x ,y ,xx ,yy, pos, preIndex=0;
	chees[step_x][step_y]=count;
	horse[count].x = step_x;
	horse[count].y = step_y;
	while(count != 62)
	{
		//该部分用来求出下一步的下一步的出路
		///////////////////////////////////////////////////////////////////
		for( i=1;i<9;i++)
		{
            F[i]=-1;
			x=horse[count].x+fx[i];
			y=horse[count].y+fy[i];
			if(x>-1 && x<MAX && y>-1 && y<MAX && chees[x][y]==0)  
			{
                F[i]++;
				for(j=1;j<9;j++)
                {
                    xx=x+fx[j];
                    yy=y+fy[j];
                    if(xx>-1 && xx<MAX && yy>-1 && yy<MAX && chees[xx][yy]==0)
                    {
                        F[i]++;
                    }

                }
			}
		}
		////////////////////////////////////////////////////////////////////
		printf("Indexvalue = %d count = %d \n",F[minIndex(F)],count);
		//minIndex用来求出下一步的下一步最少的那个方向的下标，当没有出路时，返回9
        if(minIndex(F)==9)
        {
        	chees[x][y]=0;
            horse[count].p[minIndex(F)] = -1;
            chees[horse[count].x][horse[count].y]=0;
            count--;

        }
        else
        {
            preIndex=minIndex(F);
            count++;
            horse[count].x=horse[count-1].x+fx[preIndex];
            horse[count].y=horse[count-1].y+fy[preIndex];
            printf("horse[count].x = %d horse[count].y = %d fx[preIndex] = %d fy[preIndex] = %d\n",horse[count].x,horse[count].y,fx[preIndex],fy[preIndex]);
            chees[horse[count].x][horse[count].y]=count;
            
        }
       // printarr(chees);
	}
}

int main(/*int argc, char *argv[]*/) 
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
	chees[1][2]=99;
	chees[7][7]=99;
	int z,h;
	printf("请输入横纵坐标中间以逗号隔开：\n");
	scanf("%d,%d",&h,&z);
    hchees(chees,h,z);
	printarr(chees);
	return 0;
}

