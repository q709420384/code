#include<iostream>
#include"Trituple.h"
using namespace std;

int main()
{
	int row , col;
	TSMatrix A;
	cout<<"Please input row :" ;
	cin>>row;
	cout<<"Please input col :" ;
	cin>>col;
	if(A.InitMatrix(row , col)!=1)
	{
		cout<<"Over the limite"<<endl ;
		return -1 ;
	}
	A.SetMatrix();
	cout<<"A is :"<<endl;
	A.PrintMatrix();
	cout<<"B is :"<<endl;
    TSMatrix B = A.TransposeTSMatrix() ;
    B.PrintMatrix();

}
