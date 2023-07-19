/*
 * @Author: Jiahui Tang
 * @Date: 2022-08-13 09:00:04
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2022-09-03 17:09:11
 * @Description:
 */
// Test11.cpp:定义控制台的应用程序的入口点
//

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

std::mutex g_mtx;
int g_nData = 0;
void foo()
{
	g_mtx.lock();
	for (int i = 0; i < 100000; i++)
	{
		g_nData++;
	}
	g_mtx.unlock();
}

int _tmain(int argc, char *argv[])
{
	std::thread t(foo);
	g_mtx.lock();
	for (int i = 0; i < 100000; i++)
	{
		g_nData++;
	}
	g_mtx.unlock();
	t.join();
	cout << "g_nData: " << g_nData << endl;

	system("pause");
	return 0;
}