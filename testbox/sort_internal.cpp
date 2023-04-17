/*
 * @Author: Jiahui Tang
 * @Date: 2023-04-15 13:34:08
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-04-15 13:40:32
 * @Description:
 */
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <regex>
#include <climits>
#include <unordered_map>
#include <vector>
using namespace std;
struct Interval
{
    int satrt;
    int end;
};
class Solution
{

public:
    static bool cmp(const Interval &a, const Interval &b)
    {
        return a.satrt < b.satrt;
    }
    vector<Interval> inter_sort(vector<Interval> &intervals)
    {
        sort(intervals.begin(), intervals.end(), cmp);
        return intervals;
    }
};

int main()
{
    Solution s;
    vector<Interval> intervals{{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    vector<Interval> res = s.inter_sort(intervals);
    for (auto i : res)
    {
        cout << "[" << i.satrt << "," << i.end << "]" << endl;
    }
    return 0;
}