int Assign(TSMatrix A,ElemType &x,int i,int j)
{
    int k=0;
    if (i>=A.rows || j>=A.cols)
        return 0;                       //失败时返回false
    while (k<A.nums && i>A.data[k].row)
        k++;                            //查找行
    while (k<A.nums && i==A.data[k].row && j>A.data[k].col) 
        k++;                            //查找列
    if (A.data[k].row==i && A.data[k].col==j)
        x=A.data[k].value;
    else
        x=0;                //在三元组中没有找到表示是零元素
    return 1;            //成功时返回true
}

int Value(TSMatrix &t,ElemType x,int i,int j)  //三元组元素赋值
{
    int k=0,k1;
    if (i>=t.rows || j>=t.cols)
        return 0;               //失败时返回false
    while (k<t.nums && i>t.data[k].row) k++;                  //查找行
    while (k<t.nums && i==t.data[k].row && j>t.data[k].col) k++;//查找列
    if (t.data[k].row==i && t.data[k].col==j)   //存在这样的元素
        t.data[k].value=x;
    else                                    //不存在这样的元素时插入一个元素
    {
        for (k1=t.nums-1; k1>=k; k1--)
        {
            t.data[k1+1].row=t.data[k1].row;
            t.data[k1+1].col=t.data[k1].col;
            t.data[k1+1].value=t.data[k1].value;
        }
        t.data[k].row=i;
        t.data[k].col=j;
        t.data[k].value=x;
        t.nums++;
    }
    return 1;                        //成功时返回true
}

int MatAdd(TSMatrix a,TSMatrix b,TSMatrix &c)
{
    int i,j;
    ElemType va,vb,vc;
    if (a.rows!=b.rows || a.cols!=b.cols)
        return 0;                        //行数或列数不等时不能进行相加运算
    c.rows=a.rows;
    c.cols=a.cols;       //c的行列数与a的相同
    c.nums=0;
    for(i=0; i<a.rows; i++)
        for(j=0; j<a.cols; j++)
        {
            Assign(a,va,i,j);
            Assign(b,vb,i,j);
            vc=va+vb;
            if(vc)
                Value(c,vc,i,j);
        }
    return 1;
}
