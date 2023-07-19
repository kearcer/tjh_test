/*
 * @Author: Jiahui Tang
 * @Date: 2022-08-13 09:00:04
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2022-09-06 22:20:33
 * @Description:
 */
// Test11.cpp:定义控制台的应用程序的入口点
//

#include <iostream>
#include <type_traits>
#include <memory>
#include <stdio.h>
#include <stack>
using namespace std;

bool Ismatch(string s)
{
	stack<char> st;
	int len = s.size();
	for (int i = 0; i < len; i++)
	{
		if (s[i] == '(' || s[i] == '{' || s[i] == '[')
			st.push(s[i]);
		else if (s[i] == ')' && st.top() == '(' ||
				 s[i] == ']' && st.top() == '[' ||
				 s[i] == '}' && st.top() == '{')
		{
			st.pop();
		}
	}
	if (st.empty())
		return true;
	else
		return false;
}

int main()
{
	string s = "{[}]{}";
	bool result = Ismatch(s);
	printf("result:%d\n", result);
	return 0;
}