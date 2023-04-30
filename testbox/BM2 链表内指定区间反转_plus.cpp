#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        if(!binary_search(nums.begin(), nums.end(), target))
            return -1;
        return lower_bound(nums.begin(), nums.end(), target) - nums.begin();
    }
};

int main()
{
    Solution s;
    vector<int> nums = {9};
    int target = 8;
    cout << s.search(nums,target) << endl;
}