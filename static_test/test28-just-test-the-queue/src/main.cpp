/*
 * @Author: Jiahui Tang
 * @Date: 2022-08-13 09:00:04
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2022-09-23 16:41:01
 * @Description:
 */
// Test11.cpp:定义控制台的应用程序的入口点
//

#include <iostream>
#include <type_traits>
#include <memory>
#include <stdio.h>
#include <stack>
#include <string>
#include <queue>
#include <cstring>
#include <math.h>
#include <mutex>
#include <thread>
using namespace std;

volatile int tickets = 100;
mutex mtx;

int main()
{
	queue<int> myqueue;
	int sum(0);

	for (int i = 0; i <= 10; i++)
	{
		myqueue.push(i);
	}

	while (!myqueue.empty())
	{
		sum += myqueue.front();
		myqueue.pop();
	}
	cout << "total:" << sum << endl;
}