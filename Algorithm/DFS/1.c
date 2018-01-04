#include<stdio.h>
#include<stdlib.h>
#define M 5
#define N 4
int s[M][N];
int map[M][N] = {
	{ 1, 1, 0, 1 },
	{ 1, 1, 1, 1 },
	{ 1, 1, 0, 1 },
	{ 1, 0, -1, 1 },
	{ 1, 1, 1, 0 }
};
int fx[4] = { 0, 1, 0,-1 };
int fy[4] = { 1, 0, -1, 0 };

void dfs(int x, int y, int step)
{
	int i, j;
	if (map[x][y] == -1)
	{
		printf("\n\n");
		for (i = 0; i < M; i++)
		{
			for (j = 0; j < N; j++)
				printf("%d ", s[i][j]);
			printf("\n");
		}
		return;
		
	}
	for (i = 0; i < 4; i++)
	{
		int xx = x + fx[i];
		int yy = y + fy[i];
		if (xx>-1 && xx<M && yy>-1 && yy<N && map[xx][yy] != 0 && s[xx][yy]==0)
		{
			s[xx][yy] = step;
			dfs(xx, yy, step + 1);
			s[xx][yy] = 0;
		}
	}
}

int main()
{
	s[0][0]=1;
	dfs(0, 0, 2);
	getchar();
}
