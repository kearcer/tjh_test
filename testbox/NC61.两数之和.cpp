/*
 * @Author: Jiahui Tang
 * @Date: 2023-04-11 21:22:03
 * @LastEditors:
 * @LastEditTime: 2023-04-11 21:22:04
 * @Description:
 */
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;
class Solution
{
public:
    /**
     *
     * @param numbers int整型vector
     * @param target int整型
     * @return int整型vector
     */
    vector<int> twoSum(vector<int> &numbers, int target)
    {
        vector<int> v;
        int size = numbers.size();
        for (int i = 0; i < size; i++)
        {
            for (int j = i + 1; j < size; j++)
            {
                if (numbers[i] + numbers[j] == target)
                {
                    return {i, j};
                }
            }
        }

        return v;
    }
};

int main()
{
    Solution s;
    vector<int> numbers = {2, 7, 11, 15};
    int target = 13;
    vector<int> result = s.twoSum(numbers, target);
    cout << "[" << result[0] << ", " << result[1] << "]" << endl;
    return 0;
}