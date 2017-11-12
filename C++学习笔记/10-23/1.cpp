/*************************************************************************
	> File Name: 1.cpp
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年10月23日 星期一 17时43分36秒
 ************************************************************************/

#include<iostream>
using namespace std;

class Test
{
public:
    void Setdata(int data = 0)
    {
        this->data = data;
    }
    int Getdata(void)
    {
    	return data;
    }
private:
    int data;
};
int main()
{
    Test A;
    A.Setdata(10);
    Test B;
    B = A;
}
