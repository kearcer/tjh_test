/*
 * @Author: Jiahui Tang
 * @Date: 2023-02-26 10:34:31
 * @LastEditors:
 * @LastEditTime: 2023-02-26 10:34:31
 * @Description:
 */
// 引入头文件
#include <iostream> // 用于输入输出流
#include <stack>    // 用于栈数据结构
#include <string>   // 用于字符串操作
#include <sstream>  // 用于字符串流

// 定义一个函数来判断是否为操作数
bool is_operand(const std::string &s)
{
    std::istringstream iss(s);      // 创建一个字符串流对象，以便从字符串中读取数据
    double d;                       // 定义一个浮点数变量，用于存储转换后的结果
    return (iss >> d) && iss.eof(); // 尝试从字符串流中读取浮点数，并检查是否到达末尾，如果是，则返回true，否则返回false
}

// 定义一个函数来计算后缀表达式
double evaluate_postfix(const std::string &expression)
{
    std::stack<double> stack;           // 创建一个空栈，用于存储操作数和中间结果
    std::istringstream iss(expression); // 创建一个字符串流对象，以便从表达式字符串中读取数据
    std::string token;                  // 定义一个字符串变量，用于存储每个元素（操作数或运算符）
    while (iss >> token)
    { // 从字符串流中读取每个元素，直到结束或出错为止
        if (is_operand(token))
        {                                 // 如果是操作数
            stack.push(std::stod(token)); // 将其转换为浮点数并压入栈中
        }
        else
        { // 如果是运算符
            double b = stack.top();
            stack.pop(); // 弹出栈顶元素作为右操作数，并将其赋值给b变量
            double a = stack.top();
            stack.pop(); // 弹出次顶元素作为左操作数，并将其赋值给a变量
            if (token == "+")
            { // 根据运算符进行相应的计算，并将结果压入栈中
                stack.push(a + b);
            }
            else if (token == "-")
            {
                stack.push(a - b);
            }
            else if (token == "*")
            {
                stack.push(a * b);
            }
            else if (token == "/")
            {
                stack.push(a / b);
            }
            else
            { // 如果遇到无效的运算符，则抛出异常并结束程序
                throw std::invalid_argument("Invalid operator: " + token);
            }
        }
    }
    return stack.top(); // 返回栈顶元素作为最终结果
}

// 测试代码：
int main()
{
    std::string expression = "21 3 * 52 4 * + 10 -"; // 后缀表达式字符串

    double result = evaluate_postfix(expression); // 调用函数计算结果

    std::cout << "The result of " << expression << " is " << result << "\n"; // 打印结果

    return 0;
}

// 输出：
// The result of 21 3 * 52 4 * +10 - is 445.0