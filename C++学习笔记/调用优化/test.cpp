/*************************************************************************
	> File Name: test.cpp
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年10月26日 星期四 20时03分52秒
 ************************************************************************/

#include<iostream>
using namespace std;

class Test
{
public:
    Test(int d = 0): data(d)  //构造
    {
        cout<<"Create Test Object :"<<this<<endl;
    }
    Test(const Test &t)
    {
        cout<<"Copy Create Test Object :"<<this<<endl;
        data = t.data;
    }
    Test& operator=(const Test &t)
    {
        cout<<"Assign: "<<this<<" = "<<&t<<endl;
        if(this != &t)
        {
            data = t.data;
        }
        return *this;
    }
    ~Test()
    {
        cout<<"Free Test Object :"<<this<<endl;
    }
public:
    int GetData()const
    {
        return data;
    }
private:
    int data;
};

Test fun(Test& x)
{
    int value = x.GetData();
    //Test tmp(value);
    return Test(value);
}
int main()
{
    Test t1(100);
    Test t2(fun(t1));
    //t2 = fun(t1);
}
