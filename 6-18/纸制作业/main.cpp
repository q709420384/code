#include<iostream>
using namespace std;
#include"Tree.h"

int main()
{
	const char *p="ABC##DE##F##G#H##";
	BinTreeNode* Targe,*par;
	BinTree T;
	InitBinTree(&T);
	CreateBinTree(&T,p);
	cout<<"Pre:";
	PreOrder(&T);
	cout<<endl;
	/*
	cout<<"In:";
	InOrder(&T);
	cout<<endl;
	cout<<"Pos:";
	PosOrder(&T);
	cout<<endl;
	cout<<"Size:"<<Size(&T)<<endl;
	cout<<"Height:"<<Height(&T)<<endl;
	Targe=Find(&T,'E');
	cout<<"Find:"<<Targe->data<<endl;
	par=Parent(&T,'E');
	cout<<"Parent of E:"<<par->data<<endl;
	*/
}
