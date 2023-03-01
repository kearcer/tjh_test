// 引入头文件
#include <iostream>
#include <stack>
#include <string>
using namespace std;

// 定义运算符的优先级
int precedence(char c)
{
    switch (c)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return -1;
    }
}

// 定义一个函数，判断一个字符是否是数字
bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}

// 定义一个函数，判断一个字符是否是运算符
bool is_operator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// 定义一个函数，将中缀表达式转换为后缀表达式
string infix_to_postfix(string infix)
{
    // 初始化一个空栈，用于存放运算符
    stack<char> stack;
    // 初始化一个空字符串，用于存放后缀表达式
    string postfix = "";
    // 遍历中缀表达式的每个字符
    for (char c : infix)
    {
        // 如果是数字，直接添加到后缀表达式中
        if (is_digit(c))
        {
            postfix += c;
        }
        // 如果是左括号，压入栈中
        else if (c == '(')
        {
            stack.push(c);
        }
        // 如果是右括号，弹出栈中的运算符，并添加到后缀表达式中，直到遇到左括号为止
        else if (c == ')')
        {
            while (!stack.empty() && stack.top() != '(')
            {
                postfix += stack.top();
                stack.pop();
            }
            // 弹出左括号，并丢弃它
            if (!stack.empty())
            {
                stack.pop();
            }
        }
        // 如果是运算符，弹出栈中的运算符，并添加到后缀表达式中，直到遇到优先级更低或者左括号为止。然后压入当前的运算符到栈中。
        else if (is_operator(c))
        {
            while (!stack.empty() && stack.top() != '(' && precedence(c) <= precedence(stack.top()))
            {
                postfix += stack.top();
                stack.pop();
            }
            stack.push(c);
        }
    }
    // 弹出栈中剩余的运算符，并添加到后缀表达式中。
    while (!stack.empty())
    {
        postfix += stack.top();
        stack.pop();
    }
    // 返回后缀表达式。
    return postfix;
}

// 测试代码：
int main()
{
    string infix = "((18+7)*4-16)*9";
    string postfix = infix_to_postfix(infix);
    cout << postfix << endl; // 输出：187+4*16-9*
}