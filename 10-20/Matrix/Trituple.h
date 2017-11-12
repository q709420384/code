#pragma once
#define MAXSIZE 1000
#define ElemType int
typedef struct
{
	int row ;
	int col ;
	ElemType value ;
}Triple ;
class TSMatrix
{
private:
	int row ;
	int col ;
	int num ;
	Triple data[MAXSIZE+1] ;
public:
	int InitMatrix(int row ,int col);
	int InitMatrix(int row ,int col ,int num);
	void SetMatrix(void);
	void SetMatrix(int row , int col ,ElemType value);
	void PrintMatrix(void);
	int Getrow(void);
	int Getcol(void);
	int Getnum(void);
	TSMatrix TransposeTSMatrix(void);
};

