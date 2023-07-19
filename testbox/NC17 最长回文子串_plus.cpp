/*
 * @Author: Jiahui Tang
 * @Date: 2023-04-15 22:42:40
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-04-15 23:01:20
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
    int getLongestPalindrome(string A)
    {
        int n = A.size();
        int res = 0;
        bool dp[n][n];
        memset(dp, false, sizeof(dp));
        for (int d = 0; d < n; d++)
        {
            for (int i = 0; i < n - d; i++)
            {
                int j = i + d;
                if (A[i] == A[j])
                {
                    if (d == 0 || d == 1)
                    {
                        dp[i][j] = true;
                    }
                    else
                    {
                        dp[i][j] = dp[i + 1][j - 1];
                    }
                    if (dp[i][j])
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
    string A = "cabaio";
    cout << s.getLongestPalindrome(A) << endl;
    return 0;
}