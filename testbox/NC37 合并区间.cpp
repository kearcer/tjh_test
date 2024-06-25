/*
 * @Author: Jiahui Tang
 * @Date: 2023-04-15 13:30:56
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-04-15 13:46:55
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
    int start;
    int end;
};
class Solution
{
public:
    static bool cmp(const Interval &a, const Interval &b)
    {
        return a.start > b.start;
    }

    vector<Interval> merge(vector<Interval> &intervals)
    {
        sort(intervals.begin(), intervals.end(), cmp);
        vector<Interval> res;
        int i = 0;
        int size = intervals.size();
        while (i < size)
        {
            Interval intval;
            int left = intervals[i].start;
            int right = intervals[i].end;
            while (i < size - 1 && intervals[i + 1].start <= right)
            {
                right = max(right, intervals[i + 1].end);
                i++;
            }
            intval.start = left;
            intval.end = right;
            res.push_back(intval);
            i++;
        }
        return res;
    }
};

int main()
{
    Solution s;
    vector<Interval> intervals{{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    vector<Interval> res = s.merge(intervals);
    for (auto i : res)
    {
        cout << "[" << i.start << "," << i.end << "]" << endl;
    }
    return 0;
}