/*************************************************************************
	> File Name: horse.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年10月11日 星期三 15时09分28秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int px[8]={-1,1,2,2,1,-1,-2,-2};
int py[8]={2,2,1,-1,-2,-2,-1,1};
int chess[12][12]={0};
int H[64][3];
int top=-1,cnt=0;

void Horse(){
	int i;
	int a,b,x,y;
	x=2,y=2;
	i=0;
	while(cnt<64){
		for(;i<8;i++){
			a=x+px[i];
			b=y+py[i];
			if(chess[a][b]==0)
				break;
			
		}
		if(i<8){
			chess[a][b]=++cnt;
			top++;
			H[top][0]=a;
			H[top][1]=b;
			H[top][2]=i;
			
			x=a;
			y=b;
			i=0;
		}else{
			chess[x][y]=0;
			cnt--;
			--top;
			x=H[top][0];
			y=H[top][1];
			i=H[top][2];
			i++;
			H[top][2]=i;
		
		
		}
	
	}
	
}

void Print(){
	int i,j;
	for(i=2;i<10;i++){
		for(j=2;j<10;j++){
			printf("%3d",chess[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char *argv[]) {
	int i,j;
	for(i=0;i<12;i++){
		for(j=0;j<12;j++){
			if(i==0||i==1||j==0||j==1||i==10||i==11||j==10||j==11)
			chess[i][j]=-1;
		}
	}
	chess[2][2]=1;
	cnt++;
	top++;
	H[top][0]=H[top][1]=2;
	H[top][2]=0;
	Print();
	puts("######################");
	Horse();
	Print();
	return 0;
}

