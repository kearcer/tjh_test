/*
 * @Author: Jiahui Tang
 * @Date: 2023-04-04 16:23:03
 * @LastEditors:
 * @LastEditTime: 2023-04-04 16:23:03
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
        int s_size = s.size();
        int t_size = t.size();

        if (s_size != t_size)
            return false;
        std::stack<char>
            stk;
        for (int i = 0; i < s_size; i++)
            stk.push(s[i]);

        for (int i = 0; i < t_size; i++)
        {
            int a = -1;
            a = t.find(stk.top());
            if (a != -1)
            {
                t.erase(a, 1);
                stk.pop();
            }
        }
        if (stk.empty())
            return true;
        else
            return false;
    }
};

int main()
{
    Solution sol;
    std::string s = "aacc";
    std::string t = "ccac";
    bool res = sol.isAnagram(s, t);
    std::cout << res << std::endl;
    return 0;
}