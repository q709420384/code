#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 500
#define ElemType int

typedef struct 
{
    int row ,col ;
    ElemType value ;
}Triple;

typedef struct
{
    Triple data[MAXSIZE+1];
    int rows , cols ,nums;
}TSMatrix;

int InitMatrix(TSMatrix *A, int rows ,int cols)
{
    if(rows > 20 || cols > 20)
        return 0 ;
    A->rows = rows;
    A->cols = cols;
    A->nums = 0;
    return 1;
}
void SetMatrix(TSMatrix *A)
{
    int row , col;
    ElemType value;
    printf("Input row col value (0 return) \n");
    scanf("%d %d %d",&row,&col,&value);
    while(value != 0 && row > 0 && col > 0 && row <= A->rows && col <= A->cols)
    {
        ++(A->nums);
        A->data[A->nums].row = row;
        A->data[A->nums].col = col;
        A->data[A->nums].value = value;
        scanf("%d %d %d",&row,&col,&value);
    }
}
void TransposeTSMatrix(const TSMatrix *A ,TSMatrix *B)
{
    int i ,j ,k ;
    B->rows = A->cols;
    B->cols = A->rows;
    B->nums = A->nums;
    if(B->nums > 0)
    {
        j = 1;
        for(k = 1; k <= A->cols; k++)
        for(i = 1; i <= A->nums; i++)
        if(A->data[i].col == k)
        {
            B->data[j].row = A->data[i].col;
            B->data[j].col = A->data[i].row;
            B->data[j].value = A->data[i].value;
            j++;
        }

    }
}
int AddMatrix(TSMatrix A, TSMatrix B, TSMatrix *C)
{
    if(A.rows != B.rows || A.cols != B.cols)
        return 0;
    C->rows = A.rows;
    C->cols = A.cols;
    int i = 1, j = 1, k = 0;
    while(i <= A.nums && j <= B.nums)
    {
        if(A.data[i].row < B.data[i].row)
        {
            ++k;
            C->data[k].row = A.data[i].row;
            C->data[k].col = A.data[i].col;
            C->data[k].value = A.data[i].value;
            ++i;
        }
        else if(A.data[i].row == B.data[i].row)
        {
            if(A.data[i].col < B.data[i].col)
            {
                ++k;
                C->data[k].row = A.data[i].row;
                C->data[k].col = A.data[i].col;
                C->data[k].value = A.data[i].value;
                ++i;
            }
            else if(A.data[i].col == B.data[i].col)
            {
                ++k;
                C->data[k].row = A.data[i].row;
                C->data[k].col = A.data[i].col;
                C->data[k].value = A.data[i].value + B.data[j].value;
                ++i;
                ++j;
            }
            else
            {
                ++k;
                C->data[k].row = A.data[j].row;
                C->data[k].col = A.data[j].col;
                C->data[k].value = A.data[j].value;
                ++j;
            }
        }
        else
        {
            ++k;
            C->data[k].row = B.data[j].row;
            C->data[k].col = B.data[j].col;
            C->data[k].value = B.data[j].value;
            ++j;
        }
    }
    while(i <= A.nums)
    {
        ++k;
        C->data[k].row = B.data[i].row;
        C->data[k].col = B.data[i].col;
        C->data[k].value = B.data[i].value;
        ++i;
    }
    while(j <= B.nums)
    {
        ++k;
        C->data[k].row = B.data[j].row;
        C->data[k].col = B.data[j].col;
        C->data[k].value = B.data[j].value;
        ++j;
	}
    C->nums = k;
    return 1;
}

void PrintMatrix(TSMatrix A)
{
    int i;
    for(i = 1 ;i <= A.nums ; i++)
    printf("%d %d %d\n",A.data[i].row ,A.data[i].col ,A.data[i].value);
}

int main()
{
    TSMatrix A ,B ,C;
    int rows ,cols ;
    printf("Please input rows and cols :");
    scanf("%d %d",&rows,&cols);
    if(InitMatrix(&A,rows,cols)==0)
    {
        printf("Out of range \n");
        return -1;
    }
    SetMatrix(&A);
    printf("\nA is :\n");
    PrintMatrix(A);
    TransposeTSMatrix(&A,&B);
    printf("\nB is :\n");
    PrintMatrix(B);
    AddMatrix(A,B,&C);
    printf("\nC is :\n");
    PrintMatrix(C);


}
