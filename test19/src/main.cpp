/*
 * @Author: Jiahui Tang
 * @Date: 2022-06-26 13:29:12
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2022-06-26 22:41:46
 * @Description:
 */
// constructing vectors
#include <tjh_project.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

void PrintVector(const vector<int> &v)
{
	// const对象使用const迭代器进行遍历打印
	vector<int>::const_iterator it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

int main()
{
	int test_flag;
	printf("分层调试id:");
	scanf("%d", &test_flag);
	if (test_flag == 1)
	{
		// constructors used in the same order as described above:
		vector<int>
			first;										 // empty vector of ints
		vector<int> second(4, 100);						 // four ints with value 100
		vector<int> third(second.begin(), second.end()); // iterating through second
		vector<int> fourth(third);						 // a copy of third
		// 下面涉及迭代器初始化的部分，我们学习完迭代器再来看这部分
		// the iterator constructor can also be used to construct from arrays:
		int myints[] = {16, 2, 77, 29};
		vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));
		cout << "The contents of fifth are:";
		for (vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
			cout << ' ' << *it;
		cout << '\n';
	}
	else if (test_flag == 2)
	{
		// 使用push_back插入4个数据
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		// 使用迭代器进行遍历打印
		vector<int>::iterator it = v.begin();
		while (it != v.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
		// 使用迭代器进行修改
		it = v.begin();
		while (it != v.end())
		{
			*it *= 2;
			++it;
		}
		// 使用反向迭代器进行遍历再打印
		vector<int>::reverse_iterator rit = v.rbegin();
		while (rit != v.rend())
		{
			cout << *rit << " ";
			++rit;
		}
		cout << endl;
		PrintVector(v);
		return 0;
	}
	else if (test_flag == 3)
	{

		size_t sz;
		std::vector<int> foo;
		sz = foo.capacity();
		std::cout << "making foo grow:\n";
		for (int i = 0; i < 100; ++i)
		{
			foo.push_back(i);
			if (sz != foo.capacity())
			{
				sz = foo.capacity();
				std::cout << "capacity changed: " << sz << '\n';
			}
		}
	}
	else if (test_flag == 4)
	{
		size_t sz;
		std::vector<int> foo;
		sz = foo.capacity();
		std::cout << "making foo grow:\n";
		for (int i = 0; i < 100; ++i)
		{
			foo.push_back(i);

			if (sz != foo.capacity())
			{
				sz = foo.capacity();
				std::cout << "capacity changed: " << sz << '\n';
			}
		}
		std::vector<int> bar;
		sz = bar.capacity();
		bar.reserve(100); // this is the only difference with foo above
		std::cout << "making bar grow:\n";
		for (int i = 0; i < 100; ++i)
		{
			bar.push_back(i);
			if (sz != bar.capacity())
			{
				sz = bar.capacity();
				std::cout << "capacity changed: " << sz << '\n';
			}
		}
	}
	else if (test_flag == 5)
	{
		std::vector<int> myvector;
		// set some initial content:
		for (int i = 1; i < 10; i++)
			myvector.push_back(i);
		myvector.resize(5);
		myvector.resize(8, 100);
		myvector.resize(12);
		std::cout << "myvector contains:";
		for (int i = 0; i < myvector.size(); i++)
			std::cout << ' ' << myvector[i];
		std::cout << '\n';
		return 0;
	}
	else if (test_flag == 6)
	{
		int a[] = {1, 2, 3, 4};
		vector<int> v(a, a + sizeof(a) / sizeof(int));
		vector<int>::iterator it = v.begin();
		PrintVector(v);
		while (it != v.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
		v.pop_back();
		v.pop_back();
		it = v.begin();
		while (it != v.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
		return 0;
	}
	else if (test_flag == 7)
	{
		int a[] = {1, 2, 3, 4};
		vector<int> v(a, a + sizeof(a) / sizeof(int));
		PrintVector(v);
		// 使用find查找3所在位置的iterator
		vector<int>::iterator pos = find(v.begin(), v.end(), 3);

		// 在pos位置之前插入30
		v.insert(pos, 30);
		vector<int>::iterator it = v.begin();
		while (it != v.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
		pos = find(v.begin(), v.end(), 3);
		// 删除pos位置的数据
		v.erase(pos);
		it = v.begin();
		while (it != v.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}
	else if (test_flag == 8)
	{
		vector<int> v{1, 2, 3, 4, 5, 6};

		auto it = v.begin();

		PrintVector(v);
		// 将有效元素个数增加到100个，多出的位置使用8填充，操作期间底层会扩容
		v.resize(100, 8);

		// reserve的作用就是改变扩容大小但不改变有效元素个数，操作期间可能会引起底层容量改变
		// v.reserve(100);

		// 插入元素期间，可能会引起扩容，而导致原空间被释放
		// v.insert(v.begin(), 0);
		// v.push_back(8);

		// 给vector重新赋值，可能会引起底层容量改变
		// v.assign(100, 8);

		/*
		出错原因：以上操作，都有可能会导致vector扩容，也就是说vector底层原理旧空间被释放掉，
	   而在打印时，it还使用的是释放之间的旧空间，在对it迭代器操作时，实际操作的是一块已经被释放的
	   空间，而引起代码运行时崩溃。
		解决方式：在以上操作完成之后，如果想要继续通过迭代器操作vector中的元素，只需给it重新
	   赋值即可。
		*/
		PrintVector(v);
		// while (it != v.end())
		// {
		// 	cout << *it << " ";
		// 	++it;
		// }
		// cout << endl;
		return 0;
	}

	return 0;
}