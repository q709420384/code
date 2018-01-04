/*************************************************************************
	> File Name: test.cpp
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年12月11日 星期一 21时08分43秒
 ************************************************************************/

#include<iostream>
#include<limits.h>
using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 0)
            return false;
        int n = x;
        long long sum = 0;
        while(n != 0)
        {
            sum = sum * 10 + n % 10;
            n /= 10;
        }
        return x == sum;
    }
};

int main()
{
    Solution a;
    //int n;
    //cin >> n;
    if(a.isPalindrome(-2147447412))
        cout << "Yes!" << endl;
    else
        cout << "No!" << endl;
}
