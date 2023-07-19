/*
 * @Author: Jiahui Tang
 * @Date: 2022-08-13 09:00:04
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2022-09-04 10:10:23
 * @Description:
 */
// Test11.cpp:定义控制台的应用程序的入口点
//

#include <iostream>
#include <type_traits>
#include <memory>
#include <stdio.h>
using namespace std;

template <class T>

class Construct
{
public:
	typedef typename remove_reference<T>::type U; // removeing the reference
	Construct() : m_ptr(new U)
	{
	}
	typename add_lvalue_reference<U>::type // add left reference
	Get() const
	{
		return *m_ptr.get();
	}

private:
	unique_ptr<U> m_ptr;
};

int main()
{
	Construct<int> c;
	int a = c.Get();
	cout << a << endl;
	printf("hello word!\n");
	return 0;
}