/*
 * @Author: Jiahui Tang
 * @Date: 2023-04-15 22:42:40
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-04-15 22:56:45
 * @Description:
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>
#include <regex>
#include <climits>
#include <stack>
using namespace std;
class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param A string字符串
     * @return int整型
     */

    bool analysis(string A, int i, int j)
    {
        int count = j - i + 1;
        bool equal = (count % 2 ? 1 : 0);
        while (A[i] == A[j])
        {
            if (i < j)
            {
                i++;
                j--;
            }
            else
            {
                break;
            }
        }
        if (equal == 0 && (i - j) == 1)
            return true;
        if (equal == 1 && i == j)
            return true;
        return false;
    }
    int getLongestPalindrome(string A)
    {
        int n = A.size();
        if (n == 0)
            return 0;
        else if (n == 1)
            return 1;
        int res = 0;
        bool dp[n][n];
        memset(dp, false, sizeof(dp));
        for (int d = 0; d < n; d++)
        {
            for (int i = 0; i < n - d; i++)
            {
                int j = i + d;
                if (A[i] != A[j])
                    continue;
                bool a = analysis(A, i, j);
                if (a)
                {
                    res = max(d + 1, res);
                }
            }
        }
        return res;
    }
};

int main()
{
    Solution s;
    string A = "a";
    cout << s.getLongestPalindrome(A) << endl;
    return 0;
}