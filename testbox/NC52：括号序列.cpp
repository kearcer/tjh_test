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
    bool isValid(string s)
    {
        int size = s.size();
        stack<char> stk;
        if (size == 0 || size % 2 != 0)
            return false;
        for (int i = 0; i < size; i++)
        {
            if (s[i] == '{' || s[i] == '[' || s[i] == '(')
                stk.push(s[i]);
            else if (stk.empty())
                return false;
            else if (s[i] == '}' && stk.top() == '{')
                stk.pop();
            else if (s[i] == ')' && stk.top() == '(')
                stk.pop();
            else if (s[i] == ']' && stk.top() == '[')
                stk.pop();
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
    std::string s1 = "}(])[{(}([[}])}]))})]]({{(])";
    std::cout << sol.isValid(s1) << '\n'; // true
}