#include<iostream>
using namespace std;
#include<assert.h>
#include<string.h>
#include"Tree.h"
#include"stack.h"
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
		assert(t != NULL);
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
	if(t == NULL)
		return;
	stack st;
	init_stack(&st);
	push(&st,t);
	BinTreeNode* p = NULL;
	while(!isempty(&st))
	{
		p = gettop(&st);
		pop(&st);
		cout<<p->data<<" ";
		if(p->rightChild != NULL)
			push(&st,p->rightChild);
		if(p->leftChild != NULL)
			push(&st,p->leftChild);
	}
}
void InOrder(BinTree* t)
{
	InOrder(t->root);
}
void InOrder(BinTreeNode* t)
{
	if(t == NULL)
		return;
	stack st;
	init_stack(&st);
	push(&st,t);
	BinTreeNode *p = NULL;
	while(!isempty(&st))
	{
		while(t->leftChild != NULL)
		{
			push(&st,t->leftChild);
			t = t->leftChild;        //相当于 p = gettop(&st);
		}
		p = gettop(&st);
		cout<<p->data<<" ";
		pop(&st);
		if(p->rightChild != NULL)
		{
			t = p->rightChild;
			push(&st, t);
		}
	}
}
void PosOrder(BinTree* t)
{
	PosOrder(t->root);
}
void PosOrder(BinTreeNode* t)
{
	if(t == NULL)
		return;
	stack st;
	init_stack(&st);
	BinTreeNode *p = t;
	int tag[20];   //栈，用于标识从左（0）或右（1）返回
	while(p != NULL || !isempty(&st))
	{
		while(p != NULL)
		{
			push(&st, p);
			tag[st.top-1] = 0;
			p = p->leftChild;
		}
		while(!isempty(&st) && tag[st.top-1]==1)
		{
			p = gettop(&st);
			pop(&st);
			cout<<p->data<<" ";
		}
		if(!isempty(&st))
		{
			tag[st.top-1] = 1;
			p = gettop(&st);
			p = p->rightChild;
		}
		else
			break;
	}
}
int Height(BinTree* t)
{
	return Height(t->root);
}
int Height(BinTreeNode* t)
{
	if(t==NULL)
		return 0;
	int leftHeight=Height(t->leftChild);
	int rightHeight=Height(t->rightChild);
	return (leftHeight>rightHeight?leftHeight:rightHeight)+1;
}
int Size(BinTree* t)
{
	return Size(t->root);
}
int Size(BinTreeNode* t)
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
void PrintBinTree(BinTree* t)
{
	PrintBinTree(t->root,0);
}
void PrintBinTree(BinTreeNode* t, int h)
{
	if(t == NULL)
		return;
	PrintBinTree(t->rightChild, h+1);
	for(int i=0; i<h; i++)
		cout<<"  ";
	cout<<t->data<<endl;
	PrintBinTree(t->leftChild, h+1);
}
int leaf(BinTree* t)
{
	return leaf(t->root);
}
int leaf(BinTreeNode* t)
{
	if(t == NULL)
		return 0;
	if(t->leftChild==NULL && t->rightChild==NULL)
		return 1;
	return leaf(t->leftChild) + leaf(t->rightChild);
}
void BinTreeFromOrderings(BinTree* t, const char* inorder, const char* preorder, int length)
{
	BinTreeFromOrderings(t->root, inorder, preorder, length);
}
void BinTreeFromOrderings(BinTreeNode* &t, const char* inorder, const char* preorder, int length)
{
	if(length ==0)
	{
		t = NULL;
		return;
	}
    t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
    t->data = *preorder;

    int rootIndex = strchr(inorder,*preorder) - inorder;
    BinTreeFromOrderings(t->leftChild, inorder, ++preorder, rootIndex);
    BinTreeFromOrderings(t->rightChild, inorder + rootIndex + 1, preorder + rootIndex + 1,length - (rootIndex + 1));
}
