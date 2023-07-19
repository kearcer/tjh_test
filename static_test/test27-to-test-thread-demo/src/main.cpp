/*
 * @Author: Jiahui Tang
 * @Date: 2022-08-13 09:00:04
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2022-09-12 21:40:59
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
#include <cstring>
#include <math.h>
#include <mutex>
#include <thread>
using namespace std;

volatile int tickets = 100;
mutex mtx;

void sellTickets(string name)
{
	while (tickets > 0)
	{
		mtx.lock();
		if (tickets > 0)
		{
			cout << name << "售出第" << tickets << "张票" << endl;
			tickets--;
		}
		mtx.unlock();
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

int main()
{
	thread t1(sellTickets, "windows 1");
	thread t2(sellTickets, "windows 2");
	thread t3(sellTickets, "windows 3");
	t1.join();
	t2.join();
	t3.join();

	return 0;
}