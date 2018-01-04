/*************************************************************************
	> File Name: test.cpp
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年11月25日 星期六 19时55分08秒
 ************************************************************************/

#include<iostream>
#include<limits.h>
using namespace std;
class Solution {
public:
    int reverse(int x){
        long long sum = 0;
        while(x!=0){
            sum = sum * 10 + x%10;
            x /= 10;
            if(abs(sum) > INT_MAX)
                return 0;
        }
        return sum;
    }
};
int main()
{
    Solution a;
    cout<<a.reverse(-123)<<endl;
}
