#ifndef _TREE_H
#define _TREE_H

#define ElemType char
typedef struct BinTreeNode                //二叉树节点类型
{
	ElemType data;
	BinTreeNode* leftChild;
	BinTreeNode* rightChild;
}BinTreeNode;
typedef struct  		//二叉树根结点
{
	BinTreeNode* root;
	ElemType ref;
}BinTree;

void InitBinTree(BinTree *t);  		//初始化根结点
void CreateBinTree(BinTree* t); 	//创建二叉树
void CreateBinTree(BinTreeNode* &t);
void CreateBinTree(BinTree* t,const char* &p);
void CreateBinTree(BinTreeNode* &t,const char* &p);
void PreOrder(BinTree* t); 		//前序遍历
void PreOrder(BinTreeNode* t);
void InOrder(BinTree* t);
void InOrder(BinTreeNode* t);
void PosOrder(BinTree* t);
void PosOrder(BinTreeNode* t);
void LevelOrder(BinTree* t);
void LevelOrder(BinTreeNode* t);
int Height(BinTree* t);
int Height(BinTreeNode* t);
int Size(BinTree* t);
int Size(BinTreeNode* t);
BinTreeNode* Find(BinTree* t,char key);
BinTreeNode* Find(BinTreeNode* t,char key);
BinTreeNode* Parent(BinTree* t,char key);
BinTreeNode* Parent(BinTreeNode* t,char key);

#endif
