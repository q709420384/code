#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>

typedef struct Tree
{
	int weight;   //权值
	int left;     //左子树
	int right;    //右子数
	int flag;     //标记，用来鉴定是否使用
	int parent;   //父节点
}HaffTree;

void CreateHaffTree(int* weight,int n,HaffTree* pHaffTree)
{
	int i,j,min1,min2,x1,x2;   //min1,min2分别为最小值和次最小值，x1,x2分别为最小值和次最小值对应下标
	for(i=0;i<2*n-1;i++)       //初始化HaffTree
	{
		if(i<n)
			pHaffTree[i].weight=weight[i];
		else
			pHaffTree[i].weight=0;
		pHaffTree[i].left=0;
		pHaffTree[i].right=0;
		pHaffTree[i].flag=0;	//未使用的初始化为0
		pHaffTree[i].parent=0;
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
void HaffCode(HaffTree* pHaffTree,int n,char*** code)
{
	int i;
	char ch[20]="";
	int start;
	int parent;
	int child;
	int len;
	*code=(char**)malloc(sizeof(char**)*n);
	for(i=0;i<n;++i)
	{
		parent=pHaffTree[i].parent;
		child=i;
		start=18;
		while(parent!=0)
		{
			if(pHaffTree[parent].left==child)
				ch[start--]='0';
			else
				ch[start--]='1';
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
	int n,i;
	printf("请输入字符集大小：");
	scanf("%d",&n);
	getchar();
	char *p = (char*)malloc(sizeof(char) * n);
	int *weight = (int *)malloc(sizeof(int) * n);
	
	printf("请输入字符:");
	for(i=0; i<n; i++)
	{
		scanf(" %c",&p[i]);
	}
	
	printf("请输入权值:");
	for(i=0; i<n; i++)
	{
		scanf("%d",&weight[i]);
	}
	HaffTree* pHaffTree=(HaffTree*)malloc(sizeof(HaffTree)*(2*n-1));
	CreateHaffTree(weight,n,pHaffTree);
	char** code=NULL;
	HaffCode(pHaffTree,n,&code);
	for(i=0;i<n;i++)
	{
		printf("字符:%c 权值:%d 编码:",p[i],weight[i]);
		puts(code[i]);
	}
}
