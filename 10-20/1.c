#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<malloc.h>
#define ERROR    -1
#define OK     1
#define MAXSIZE    100
#define MAXRC    100
typedef int ElemType;
typedef struct {
    int i, j;
    ElemType e;
}Triple;
typedef struct {
    Triple data[MAXSIZE+1];
    int rpos[MAXRC+1];   //各行第一个非零元的位置表
    int mu, nu, tu;
}TSMatrix;
//初始化稀疏矩阵M
int InitSMatrix(TSMatrix &M) {
    TSMatrix *p;
    p=(TSMatrix *)malloc(sizeof(TSMatrix));
    if(!p)
    return ERROR;
    M=*p;
    M.mu=0; M.nu=0; M.tu=0;
    for(int l=0; l<=MAXRC+1; l++)
    M.rpos[l]=0;
    return OK;
}
//创建稀疏矩阵M
int CreateSMatrix(TSMatrix &M) {
    InitSMatrix(M);
    printf("Please input the TSMatrix's mu, nu, tu:\n");
    scanf("%d %d %d",&M.mu,&M.nu,&M.tu);
    printf("\nInput %d elements:\n",M.tu);
    for(int i=1; i<=M.tu; i++)
    scanf("%d %d %d",&M.data[i].i,&M.data[i].j,&M.data[i].e);
    return OK;
}
//销毁稀疏矩阵M
void DestroySMatrix(TSMatrix &M) {
    M.nu=0; M.mu=0; M.tu=0;
}
//输出稀疏矩阵M
int PrintSMatrix(TSMatrix M) {
    if(M.tu<=0) return ERROR;
    int p=1;
    for(int a=1; a<=M.mu; a++) {
        for(int b=1; b<=M.nu; b++) {
            if(p<=M.tu && M.data[p].i==a && M.data[p].j==b) {
                printf("%d ",M.data[p].e);
                p++;
            }
            else
            printf("0 ");
        }
        printf("\n");    //输出每一行数组后换行
    }
    //printf("Input any key to the menu.\n");
    getch();
    return OK;
}

//求稀疏矩阵的转置
int FastTransposeSMatrix(TSMatrix M,TSMatrix &T) {
    int col, t, p, q;
    int num[100], cpot[100];
    if(M.tu<=0 || M.mu<=0 || M.nu<=0)
    return ERROR;
    //T=(TSMatrix *)malloc(sizeof(TSMatrix));
    T.mu=M.nu;
    T.nu=M.mu;
    T.tu=M.tu;
    if(T.tu) {
        for(col=1; col<=M.nu; ++col) num[col]=0;
        for(t=1; t<=M.tu; ++t) ++num[M.data[t].j]; //求M中每一列含非零元个数
        cpot[1]=1;
        //求第col列中第一个非零元在b.data中的序号
        for(col=2; col<=M.nu; ++col) cpot[col]=cpot[col-1]+num[col-1];
        for(p=1; p<=M.nu; ++p) {
            col=M.data[p].j; q=cpot[col];
            T.data[q].i=M.data[p].j; T.data[q].j=M.data[p].i;
            T.data[q].e=M.data[p].e; ++cpot[col];
        }
    }
    printf("FastTransposeSMatrix success!\nThe FastTransposeSMatrix is:\n");
    PrintSMatrix(T);
    return OK;
}
void GetRpos(TSMatrix &M) {
    int row,t,num[MAXSIZE];
    for (row=1;row<=MAXSIZE;++row) num[row]=0; 
    for (t=1;t<=M.tu;++t) ++num[M.data[t].i];
    M.rpos[1]=1;
    for (row=2;row<=M.mu;++row) M.rpos[row]=M.rpos[row-1]+num[row-1];
}

//求稀疏矩阵的乘积
int MultSMatrix(TSMatrix M, TSMatrix N, TSMatrix &Q) {
    //求矩阵乘积Q=M X N，采用行逻辑链接存储表示
    if(M.nu!=N.mu)
    return ERROR;
    Q.mu=M.mu; Q.nu=N.nu; Q.tu=0;
    int arow, brow, tp, p, q, t, ccol, k=1;
    GetRpos(M); GetRpos(N);
    if(M.tu*N.tu!=0) {     //Q是非零矩阵
                      for(arow=1; arow<=M.mu; ++arow) { //处理M的每一行
                                                       int ctemp[50]={0};    //当前行各元素累加器清零
                                                       Q.rpos[arow]=Q.tu+1;
                                                       if(arow<M.mu)
                                                       tp=M.rpos[arow+1];
                                                       else { tp=M.tu+1; }
                                                       for(p=M.rpos[arow]; p<tp; ++p) {  //对当前行中每一个非零元
                                                                                       brow=M.data[p].j;     //找到对应元在N中的行号
                                                                                       if(brow<N.mu) t=N.rpos[brow+1];
                                                                                       else { t=N.tu+1; }
                                                                                       for(q=N.rpos[brow]; q<t; ++q) {
                                                                                           ccol=N.data[q].j;    //乘积元素在Q中列号
                                                                                           ctemp[ccol] += M.data[p].e * N.data[q].e;
                                                                                       }
                                                                                      } //求得Q中第crow（=arow）行的非零元
                                                       for(ccol=1; ccol<=Q.nu; ++ccol)   //压缩存储该行非零元
                                                       if(ctemp[ccol]) {
                                                           if(++Q.tu>MAXSIZE) return ERROR;
                                                           //Q.data[Q.tu]=(arow,ccol,ctemp[ccol]);
                                                           Q.data[Q.tu].i=arow;
                                                           Q.data[Q.tu].j=ccol;
                                                           Q.data[Q.tu].e=ctemp[ccol];
                                                       }
                                                      }
                     }
    PrintSMatrix(Q);
    getch();
    return OK;
}
int AddSMatrix(TSMatrix M, TSMatrix N, TSMatrix &Q) {
    if(M.mu!=N.mu||M.nu!=N.nu)
    return ERROR;
    Q.mu=M.mu;
    Q.nu=M.nu;
    Q.tu=0;
    int x=0,y=0;
    for(int i=1;i<=Q.mu;i++){
        for(int j=1;j<=Q.nu;j++){
            for(int p=1;p<=M.tu;p++){
                if((i==M.data[p].i)&&(j==M.data[p].j)){
                    x=M.data[p].e;
                    break;
                }
                else x=0; 
            }//for p
            for(int q=1;q<=N.tu;q++){
                if((i==N.data[q].i)&&(j==N.data[q].j)){
                    y=N.data[q].e;
                    break;
                }
                else y=0;   
            }//for q
            if((x+y)!=0){
                Q.data[Q.tu+1].i=i;
                Q.data[Q.tu+1].j=j;
                Q.data[Q.tu+1].e=x+y;
                Q.tu++;
            }//if
        }//for j
    }//for i 
    PrintSMatrix(Q);
    return OK;
}

void menu() {
    printf("\t************************************************************\n");
    printf("\t         菜单选项\n");
    printf("\t************************************************************\n\n\n\n");
    printf("\t\t\t1. CreateSMatrix.\n");
    printf("\t\t\t2. DestroySMatrix.\n");
    printf("\t\t\t3. PrintSMatrix.\n");
    printf("\t\t\t4. AddSMatrix.\n");
    printf("\t\t\t5. MultSMatrix.\n");
    printf("\t\t\t6. FastTransposeSMatrix.\n");
    printf("\t\t\t0. exit.\n\n");
    printf("\t\t\tInput your choose:\n\t\t\t");
}
void main(){
    int swh;
    TSMatrix M, N, Q, T;
    do {
        menu();
        scanf("%d", &swh);
        switch(swh) {
            case(1):
            InitSMatrix(M);
            CreateSMatrix(M);
            break;
            case(2):
            DestroySMatrix(M);
            break;
            case(3):
            PrintSMatrix(M);
            break;
            case(4):
            InitSMatrix(Q);
            printf("Input M:\n");
            CreateSMatrix(M);
            printf("Input N:\n");
            CreateSMatrix(N);
            AddSMatrix(M,N,Q);
            break;
            case(5):
            InitSMatrix(Q);
            printf("Input M:\n");
            CreateSMatrix(M);
            printf("Input N:\n");
            CreateSMatrix(N);
            MultSMatrix(M,N,Q);
            break;
            case(6):
            InitSMatrix(T);
            FastTransposeSMatrix(M,T);
            break;
            case(0):
            exit(0);
            default:
            menu();
        }

    }while(1);
}
