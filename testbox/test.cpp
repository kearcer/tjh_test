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