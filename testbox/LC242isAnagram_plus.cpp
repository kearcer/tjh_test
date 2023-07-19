/*
 * @Author: Jiahui Tang
 * @Date: 2023-04-04 16:23:03
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-04-06 12:33:41
 * @Description:这个程序的功能是判断两个字符串是否是由相同的字符组成的，但是顺序不同。如果是，则返回true，否则返回false
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <climits>
#include <algorithm>
#include <stack>

class Solution
{
public:
    bool isAnagram(std::string s, std::string t)
    {
        std::sort(s.begin(), s.end());
        std::sort(t.begin(), t.end());

        int s_size = s.size();
        int t_size = t.size();
        if (s_size != t_size)
            return false;
        for (int i = 0; i < s_size; i++)
        {
            if (s[i] != t[i])
                return false;
        }
        return true;
    };
};

int main()
{
    Solution sol;
    std::string s = "aacc";
    std::string t = "ccaa";
    bool res = sol.isAnagram(s, t);
    std::cout << res << std::endl;
    return 0;
}