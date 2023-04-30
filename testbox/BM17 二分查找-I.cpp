#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param nums int整型vector 
     * @param target int整型 
     * @return int整型
     */

    int BrinarySearch(vector<int>& nums, int left, int right, int target)
    {
        
        int mid = left + (right - left)/2;
        if(nums[left] == nums[right])  
        {
            if(target == nums[left])
                return left;
            else 
                return -1;
        }
        else if(target == nums[mid])
            return mid;
        else if(target < nums[mid])
            return BrinarySearch(nums, left, mid - 1, target);
        else if(target > nums[mid])
            return BrinarySearch(nums, mid + 1,  right, target);
        return 0;
    }
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        if(nums.size() == 0)
            return -1;
            
        return BrinarySearch(nums, left, right, target);
    }
};

int main()
{
    Solution s;
    vector<int> nums = {9};
    int target = 8;
    cout << s.search(nums,target) << endl;
}