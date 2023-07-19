/*
 * @Author: Jiahui Tang
 * @Date: 2023-02-23 18:42:45
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-02-23 21:00:05
 * @Description:
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <sstream>

//将获取到的一个操作符和两个操作数进行计算
int docalc(char optor, int op1, int op2)
{
    if (optor == '*')
        return op1 * op2;
    else if (optor == '+')
        return op1 + op2;
    else if (optor == '-')
        return op2 - op1;
    else if (optor == '/')
        return op2 / op1;
}

//检查进来的字符是什么属性的，如果是操作数，返回1,如果是操作符号返回2
int whichelement(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return 2;
    else if (c >= '0' && c <= '9')
        return 1;
    else
        return 0;
}

int main()
{
    std::string s = "23*54*+9-";
    std::stack<int> stk;
    for (int i = 0; i < s.size(); i++)
    {
        int a = whichelement(s[i]);
        if (a == 1)
        {
            int value = s[i] - '0';
            stk.push(value);
        }
        else if (a == 2)
        {
            char opor = s[i];
            int op1 = stk.top();
            stk.pop();
            int op2 = stk.top();
            stk.pop();
            int res = docalc(opor, op1, op2);
            printf("stk %d\n", res);
            stk.push(res);
        }
        else
        {
            printf("not a regular math expression!\n");
        }
    }
    printf("result:%d\n", stk.top());
    stk.pop();
    if (stk.empty())
        return 0;
    else
        printf("not regular\n");

    return 0;
}