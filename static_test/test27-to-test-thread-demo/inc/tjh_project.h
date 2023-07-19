/*
 * @Author: Jiahui Tang
 * @Date: 2022-06-25 22:24:03
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2022-06-25 23:09:06
 * @Description:
 */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        vector<int> result;
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (nums[i] + nums[j] == target)
                {
                    return {i, j};
                }
            }
        }
        //        return result;
    }
};