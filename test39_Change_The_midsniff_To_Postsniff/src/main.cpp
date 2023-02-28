/*
 * @Author: Jiahui Tang
 * @Date: 2023-02-26 12:21:37
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-02-26 21:41:57
 * @Description:test39_Change_The_midsniff_To_Postsniff
 */
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stack>
#include <sstream>
#include <iostream>

bool IsNumb(char chr)
{
    if (chr >= '0' && chr <= '9')
        return true;
    else
        return false;
}

int PermissionLevel(char C)
{
    if (C == '+' || C == '-')
        return 1;
    else if (C == '*' || C == '/')
        return 2;
    else
        return -1;
}

bool IsHigherPermission(char ch1, char ch2)
{
    int a = PermissionLevel(ch1);
    int b = PermissionLevel(ch2);
    if (b > a)
        return 1;
    else
        return 0;
}

/*
0:当前运算符push进栈
1:当前运算符以括号结束
2：当前运算符号因优先级到达结束
*/
int Elementlevel(char chr, std::stack<char> stk)
{
    if (chr == '(')
        return 0;
    else if (chr == ')')
        return 1;
    else if (stk.empty() == 1)
        return 0;
    else if (IsHigherPermission(chr, stk.top()))
        return 2;
}

std::string ChangeMidtoPostsniff(std::string S)
{
    std::stack<char> stk;
    std::string tmp;
    std::string res;
    int i;
    int size = S.size();
    for (i = 0; i < size; i++)
    {
        if (IsNumb(S[i]))
        {
            res += S[i];
            if (IsNumb(S[i + 1]) && (i + 1 <= size))
                continue;
            else
                res += ' ';
        }
        else
        {
            int level = Elementlevel(S[i], stk);
            if (level == 0)
                stk.push(S[i]);
            else if (level == 1)
            {
                while (stk.top() != '(')
                {
                    res += stk.top();
                    stk.pop();
                }
                stk.pop(); // 弹出左括号
                res += ' ';
            }
            else if (level == 2)
            {
                while (stk.empty() != 1 && stk.top() != '(')
                {
                    res += stk.top();
                    stk.pop();
                }
                stk.push(S[i]);
            }
        }
    }

    while (stk.empty() != 1)
    {
        res += stk.top();
        stk.pop();
    }

    return res;
}

int main()
{
    std::string s = "((18+7)*4-16)*9";
    std::string res;

    res = ChangeMidtoPostsniff(s);

    printf("%s\n", res.c_str());
}