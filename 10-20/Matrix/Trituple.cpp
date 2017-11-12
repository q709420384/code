#include<iostream>
#include"Trituple.h"
using namespace std;

int TSMatrix::InitMatrix(int row , int col)
{
	num = 0;
	this->row = row ;
	this->col = col ;
	if(row > 20 || col > 20)
		return 0 ;
	return 1;
}
int TSMatrix::InitMatrix(int row , int col,int num)
{
	num = 0;
	this->row = row ;
	this->col = col ;
    this->num = num ;
	if(row > 20 || col > 20)
		return 0 ;
	return 1;
}
void TSMatrix::SetMatrix(void)
{
	int ROW , COL ;
	ElemType VALUE ;
	cout<<"Input row col value( 0 return) :"<<endl;
	cin >> ROW >> COL >> VALUE;
	while(VALUE != 0 && ROW > 0 && COL > 0 && ROW <= row && COL <= col)
	{
		++num;
		data[num].row = ROW ;
		data[num].col = COL ;
		data[num].value = VALUE;
		cin >> ROW >> COL >> VALUE;
	}
}
void TSMatrix::SetMatrix(int row ,int col ,ElemType value)
{
    ++num;
    data[num].row = row ;
    data[num].col = col ;
    data[num].value = value ;
}
void TSMatrix::PrintMatrix(void)
{
	int i ;
	for(i = 1 ; i <= num ; ++i)
		cout<<data[i].row<<" "<<data[i].col<<" "<<data[i].value<<endl;

}
int TSMatrix::Getrow(void)
{
	return row;
}
int TSMatrix::Getcol(void)
{
	return col;
}
int TSMatrix::Getnum(void)
{
    return num;
}
TSMatrix TSMatrix::TransposeTSMatrix(void)
{
	int i,j,k ;
	TSMatrix B ;
	B.InitMatrix(col ,row ,num) ;
    if(num > 0)
    {
        j=1;
        for(k = 1;k <= col;k++)
            for(i = 1;i <= num;i++)
                if(data[i].col == k)
                    B.SetMatrix(data[i].col ,data[i].row ,data[i].value) ;
    }
    return B;
}
