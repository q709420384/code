/*************************************************************************
	> File Name: 2.cpp
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年10月17日 星期二 14时57分31秒
 ************************************************************************/

#include<iostream>
using namespace std;
int main()
{
    int carrots;
    cout << "how many carrots do you have ?" << endl;
    cin >> carrots;
    cout << "here are two more.";
    carrots = carrots + 2;
    cout << "Now you have " << carrots << " carrots." << endl;
    return 0;
}
