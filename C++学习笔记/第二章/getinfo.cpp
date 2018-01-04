/*************************************************************************
	> File Name: getinfo.cpp
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年11月15日 星期三 22时14分17秒
 ************************************************************************/

#include<iostream>
using namespace std;

int main()
{
    int carrots;

    cout << "How many carrots do you have?" << endl;
    cin >> carrots;
    cout << "Here are two more.";
    carrots = carrots + 2;
    cout << "Now you have " << carrots << " carrots." << endl;
    return 0;
}
