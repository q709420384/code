#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define INT_MAX 2147483647

typedef struct Tree
{
	int weight;
	int left;
	int right;
	int flag;
	int parent;
}HaffTree;

void CreateHaffTree(int* weight,int n,HaffTree* pHaffTree)
{
	int i,j,min1,min2,x1,x2;
	//初始化HaffTree
	for(i=0;i<2*n-1;i++)
	{
		if(i<n)
			pHaffTree[i].weight=weight[i];
		else
			pHaffTree[i].weight=0;
		pHaffTree[i].left=0;
		pHaffTree[i].right=0;
		pHaffTree[i].parent=0;
		pHaffTree[i].flag=0;
	}
	for(i=0;i<n-1;++i)
	{
		min1=min2=INT_MAX;
		x1=x2=0;
		for(j=0;j<n+i;++j)
		{
			if(pHaffTree[j].weight<min1&&pHaffTree[j].flag==0)
			{
				min2=min1;
				x2=x1;
				min1=pHaffTree[j].weight;
				x1=j;
			}
			else if(pHaffTree[j].weight<min2&&pHaffTree[j].flag==0)
			{
				min2=pHaffTree[j].weight;
				x2=j;
			}
		}
		pHaffTree[x1].flag=1;
		pHaffTree[x2].flag=1;
		pHaffTree[x1].parent=pHaffTree[x2].parent=n+i;
		pHaffTree[n+i].weight=min1+min2;
		pHaffTree[n+i].left=x1;
		pHaffTree[n+i].right=x2;
	}
}

void HaffCode(HaffTree* pHaffTree,int n,char ***code)
{
	int i;
	char ch[20]="";
	int start=0;
	int parent;
	int child;
	int len;
	*code=(char**)malloc(sizeof(char**)*n);
	for(i=0;i<n;++i)
	{
		parent=pHaffTree[i].parent;
		child=i;
		start=10;
		while(parent!=0)
		{
			if(pHaffTree[parent].left==child)
			{
				ch[start--]='0';
			}
			else
			{
				ch[start--]='1';
			}
			child=parent;
			parent=pHaffTree[parent].parent;
		}
		len=strlen(ch+start+1)+1;
		(*code)[i]=(char*)malloc(len);
		strcpy((*code)[i],ch+start+1);
	}
}

void main()
{
	int weight[]={3,5,9,78,67,65,12,34,23};
	int n=sizeof(weight)/sizeof(int);
	HaffTree* pHaffTree=(HaffTree*)malloc(sizeof(HaffTree)*(2*n-1));
	CreateHaffTree(weight,n,pHaffTree);
	char** code=NULL;
	HaffCode(pHaffTree,n,&code);
	for(int i=0;i<n;i++)
	{
		printf("%d ",weight[i]);
		puts(code[i]);
	}
}
