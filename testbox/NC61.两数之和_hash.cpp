#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <climits>
#include <unordered_map>
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
        unordered_map<int, int> hashmap;

        for (int i = 0; i < numbers.size(); i++)
        {
            int complement = target - numbers[i];
            int include_ele = hashmap.count(complement);
            if (include_ele)
                return {hashmap[complement], i};
            else
                hashmap[numbers[i]] = i;
        }

        return {};
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