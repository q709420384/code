#include<iostream>
using namespace std;
#include<assert.h>
#include"Tree.h"
#include"queue.h"
void InitBinTree(BinTree *t)           //初始化根结点
{
	t->root=NULL;
	t->ref='#';
}
void CreateBinTree(BinTree* t)         //创建二叉树
{
	CreateBinTree(t->root);
}
void CreateBinTree(BinTreeNode* &t)
{
	ElemType item;
	cin>>item;
	if(item=='#')
	{
		t=NULL;
	}
	else
	{
		t=(BinTreeNode*)malloc(sizeof(BinTreeNode));
		assert(t!=NULL);
		t->data=item;
		CreateBinTree(t->leftChild);
		CreateBinTree(t->rightChild);
	}
}
void PreOrder(BinTree* t)              //前序遍历
{
	PreOrder(t->root);
}
void PreOrder(BinTreeNode* t)
{
	if(t)
	{
		cout<<t->data<<" ";
		PreOrder(t->leftChild);
		PreOrder(t->rightChild);
	}
}
void InOrder(BinTree* t)
{
	InOrder(t->root);
}
void InOrder(BinTreeNode* t)
{
	if(t)
	{
		InOrder(t->leftChild);
		cout<<t->data<<" ";
		InOrder(t->rightChild);
	}
}
void PosOrder(BinTree* t)
{
	PosOrder(t->root);
}
void PosOrder(BinTreeNode* t)
{
	if(t)
	{
		PosOrder(t->leftChild);
		PosOrder(t->rightChild);
		cout<<t->data<<" ";
	}
}
void LevelOrder(BinTree* t)
{
	LevelOrder(t->root);
}
void LevelOrder(BinTreeNode* t)
{
	if(t)
	{
		queue q;
		BinTreeNode* temp=t;
		init_queue(&q);
		push(&q,temp);
		while(Emptyqueue(&q)!=1)
		{
			pop(&q);
			push(&q,temp->leftChild);
			push(&q,temp->rightChild);
			temp=Getfront(&q);
		}
		cout<<endl;
	}
}
int Height(BinTree* t)
{
	return Height(t->root);
}
int  Height(BinTreeNode* t)
{
	if(t==NULL)
		return 0;
	int leftHeight=Height(t->leftChild);
	int rightHeight=Height(t->rightChild);
	return (leftHeight>rightHeight?leftHeight:rightHeight)+1;
}
int  Size(BinTree* t)
{
	return Size(t->root);
}
int  Size(BinTreeNode* t)
{
	if(t==NULL)
		return 0;
	return Size(t->leftChild)+Size(t->rightChild)+1;
}
void CreateBinTree(BinTree *t, const char *&p)
{
	CreateBinTree(t->root, p);
}
void CreateBinTree(BinTreeNode *&t, const char *&p)
{
	if(*p=='#'||*p=='\0')
		t=NULL;
	else
	{
		t=(BinTreeNode*)malloc(sizeof(BinTreeNode));
		assert("t!=NULL");
		t->data=*p;
		CreateBinTree(t->leftChild,++p);
		CreateBinTree(t->rightChild,++p);
	}
}
BinTreeNode* Find(BinTree* t,ElemType key)
{
	return Find(t->root,key);
}
BinTreeNode* Find(BinTreeNode* t,ElemType key)
{
	if(t==NULL)
		return NULL;
	if(t->data==key)
		return t;
	BinTreeNode* p = Find(t->leftChild,key);
	if(p)
		return p;
	return Find(t->rightChild,key);
}
BinTreeNode* Parent(BinTree* t,ElemType key)
{
	return Parent(t->root,key);
}
BinTreeNode* Parent(BinTreeNode* t,ElemType key)
{
	if(t==NULL)
		return NULL;
	BinTreeNode* p=Find(t,key);
	if(p==NULL||p==t)
		return NULL;
	if(t->leftChild==p||t->rightChild==p)
		return t;
	BinTreeNode* q=Parent(t->leftChild,key);
	if(q)
		return q;
	return Parent(t->rightChild,key);
}

































