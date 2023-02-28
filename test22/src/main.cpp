/*
 * @Author: Jiahui Tang
 * @Date: 2022-08-13 09:00:04
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2022-08-31 16:12:10
 * @Description:
 */
// Test11.cpp:定义控制台的应用程序的入口点
//

#include <iostream>
#include <thread>
#include <mutex>
#include <stdio.h>
using namespace std;

class father
{
public:
	int wallet = 1;
	int car = 1;

protected:
	int money = 1;
	int house = 1;

private:
	int wife = 1;
};

class son : public father
{
public:
	int changewallet(int val)
	{
		wallet = 2;
		return wallet;
	}

	int changemoney(int val)
	{
		money = -100;
		return money;
	}
	// the son cannot visit the private
	// int changewife(int val)
	// {
	// 	wife = 2;
	// 	return wife;
	// }
};

int main()
{
	father dad;
	dad.car = 100;
	// dad.money = 100; // money cannot be change in internal;

	printf("hello word!\n");
	return 0;
}