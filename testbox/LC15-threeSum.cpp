#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<std::vector<int>> threeSum(std::vector<int> &nums)
    {
        std::vector<int> V;
        std::vector<std::vector<int>> result;

        std::sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); i++)
        {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            int left = i + 1;
            int right = nums.size() - 1;

            while (left < right)
            {
                if (nums[i] + nums[left] + nums[right] == 0)
                {

                    result.push_back({nums[i], nums[left], nums[right]});

                    while (right > left && nums[right] == nums[right - 1])
                        right--;
                    while (right > left && nums[left] == nums[left + 1])
                        left++;
                    left--;
                    right++;
                }
                else if (nums[i] + nums[left] + nums[right] > 0)
                {
                    right--;
                }
                else
                {
                    left++;
                }
            }
        }
        return result;
    }
};

int main()
{
    // Create a vector of integers
    std::vector<int> nums = {-1, 0, -1, -2, 1, -4};

    // Create an object of Solution class
    Solution sol;

    // Call the threeSum method and store the result
    std::vector<std::vector<int>> result = sol.threeSum(nums);

    // Print the result
    std::cout << "The triplets that sum to zero are: \n";
    for (auto v : result)
    {
        std::cout << "[";
        for (auto n : v)
        {
            std::cout << n << " ";
        }
        std::cout << "]\n";
    }

    return 0;
}