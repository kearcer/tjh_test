/*
 * @Author: Jiahui Tang
 * @Date: 2023-03-18 23:59:07
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-03-19 01:30:54
 * @Description:
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
    int threeSumClosest(vector<int> &nums, int target)
    {
        sort(nums.begin(), nums.end());
        int sum_out = 0;
        int min_value = -1;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] + nums[i + 1] + nums[i + 2] > target)
                return nums[i] + nums[i + 1] + nums[i + 2];
            int left = i + 1;
            int right = nums.size() - 1;

            if (i > 0 && nums[i] == nums[i - 1])
            {
                continue;
            }
            while (left < right)
            {
                int sum = nums[i] + nums[left] + nums[right];
                int diff = abs(sum - target);
                if (diff == 0)
                    return target;
                else
                {
                    if (min_value == -1)
                    {
                        min_value = diff;
                        sum_out = sum;
                    }
                    else if (min_value != min(min_value, diff))
                    {
                        min_value = min(min_value, diff);
                        sum_out = sum;
                    }
                }
                if (sum < target)
                    left++;
                else
                    right--;
            }
        }

        return sum_out;
    }
};

int main()
{
    // Create a vector of integers
    vector<int> nums = {0, 0, 0};

    // Create a target value
    int target = 1;

    // Create an object of Solution class
    Solution sol;

    // Call the threeSumClosest method and store the result
    int result = sol.threeSumClosest(nums, target);

    // Print the result
    cout << "The closest sum to " << target << " is: " << result << endl;

    return 0;
}