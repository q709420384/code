/*************************************************************************
> File Name: test.cpp
> Author:Sanjingye 
> Mail: 
> Created Time: 2017年12月10日 星期日 22时16分24秒
************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

void twoSum(vector<int>& nums, int target) 
{
    for(int i = 0; i < nums.size(); i++)
        for(int j = i + 1; j < nums.size(); j++)
        {
            if(nums[i] + nums[j] == target)
            {
                cout << "i = " << i << " j = " << j <<endl;
                break;
            }
        }
    return;
}

int main()
{
    vector<int> arr(3);
    arr[0] = 3;
    arr[1] = 2;
    arr[2] = 4;
    twoSum(arr, 6);
}
