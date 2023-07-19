/*
 * @Author: Jiahui Tang
 * @Date: 2022-06-26 13:29:12
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2022-12-08 13:55:35
 * @Description:
 */
// constructing vectors
#include <tjh_project.h>

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

void print_list(const list<int> &l)
{
	//注意这里调用的是list的begin()const,返回list的const_iterator对象
	for (list<int>::const_iterator it = l.begin(); it != l.end(); ++it)
	{
		cout << *it << " ";
		//*it = 10编译不通过
	}

	cout << endl;
}

void PrintList(list<int> &l)
{
	for (auto &e : l)
		cout << e << " ";
	cout << endl;
}

void TestList1()
{
	int array[] = {1, 2, 3};
	list<int> L(array, array + sizeof(array) / sizeof(array[0]));
	// 在list的尾部插入4，头部插入0
	L.push_back(4);
	L.push_front(0);
	PrintList(L);
	// 删除list尾部节点和头部节点
	L.pop_back();
	L.pop_front();
	PrintList(L);
}

void TestList3()
{
	int array1[] = {1, 2, 3};
	list<int> L(array1, array1 + sizeof(array1) / sizeof(array1[0]));
	// 获取链表中第二个节点
	auto pos = ++L.begin();
	cout << *pos << endl;
	// 在pos前插入值为4的元素
	L.insert(pos, 4);
	PrintList(L);
	// 在pos前插入5个值为5的元素
	L.insert(pos, 5, 5);
	PrintList(L);
	// 在pos前插入[v.begin(), v.end)区间中的元素
	vector<int> v{7, 8, 9};
	L.insert(pos, v.begin(), v.end());
	PrintList(L);
	// 删除pos位置上的元素
	L.erase(pos);
	PrintList(L);
	// 删除list中[begin, end)区间中的元素，即删除list中的所有元素
	L.erase(L.begin(), L.end());
	PrintList(L);
}

void TestList4()
{
	// 用数组来构造list
	int array1[] = {1, 2, 3};
	int array2[] = {4, 5, 6};
	list<int> l1(array1, array1 + sizeof(array1) / sizeof(array1[0]));
	list<int> l2(array2, array2 + sizeof(array2) / sizeof(int));
	PrintList(l1);
	print_list(l2);
	// 交换l1和l2中的元素
	l1.swap(l2);
	PrintList(l1);
	PrintList(l2);
	// 将l2中的元素清空
	l2.clear();
	cout << l2.size() << endl;
}

int Printhash(int *hash, int len)
{
	for (int i = 0; i < 500; i++)
	{
		printf("%d ", *(hash + i)); // 0 0 0 0 0 0 0 0 0 0
	}
	printf("\n");
}

// 动态分配内存，没有释放就return
void memoryLeak1()
{
	string *str = new string("动态分配内存！");
	return;
}

// 动态分配内存，虽然有些释放内存的代码，但是被半路截胡return了
int memoryLeak2()
{
	string *str = new string("内存泄露！");

	// ...此处省略一万行代码

	// 发生某些异常，需要结束函数
	if (1)
	{
		return -1;
	}
	// 另外，使用try、catch结束函数，也会造成内存泄漏！

	delete str; // 虽然写了释放内存的代码，但是遭到函数中段返回，使得指针没有得到释放
	return 1;
}

void CreateTree(TreeNode **T)
{
	// TreeNode *T;
	// T = S;
	int c;
	cin >> c;

	if ('#' == c)
		*T = NULL; //当遇到#时，令树的根节点为NULL，从而结束该分支的递归
	else
	{
		(*T) = (TreeNode *)malloc(sizeof(TreeNode));
		(*T)->val = c;			  //给根节点赋值
		CreateTree(&(*T)->left);  //创建左子树
		CreateTree(&(*T)->right); //创建右子树
	}
}

void Merge(int arr[], int start, int mid, int end, int *temp)
{
	//合并两个有序序列
	int length = 0;
	//表示辅助空间有多少个元素
	int i_start = start;
	int i_end = mid;
	int j_start = mid + 1;
	int j_end = end;
	while (i_start <= i_end && j_start <= j_end)
	{
		if (arr[i_start] < arr[j_start])
		{
			temp[length] = arr[i_start];
			length++;
			i_start++;
		}
		else
		{
			temp[length] = arr[j_start];
			length++;
			j_start++;
		}
	}
	while (i_start <= i_end)
	{
		temp[length] = arr[i_start];
		i_start++;
		length++;
	}

	while (j_start <= j_end)
	{
		temp[length] = arr[j_start];
		length++;
		j_start++;
	}

	//把辅助空间的数据放到原空间
	for (int i = 0; i < length; i++)
	{
		arr[start + i] = temp[i];
	}
}

void MergeSort(int arr[], int start, int end, int *temp)
{
	if (start >= end)
		return;
	int mid = (start + end) / 2;
	MergeSort(arr, start, mid, temp);
	MergeSort(arr, mid + 1, end, temp);
	Merge(arr, start, mid, end, temp);
}

template <typename T>
void Swap(T &left, T &right)
{
	T temp = left;
	left = right;
	right = temp;
}

template <class T>
T Add(const T &left, const T &right)
{
	return left + right;
}

int main()
{
	int test_flag;
	// printf("分层调试id:");
	// scanf("%d", &test_flag);
	test_flag = 27;
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
		// v.resize(100, 8);

		// reserve的作用就是改变扩容大小但不改变有效元素个数，操作期间可能会引起底层容量改变
		// v.reserve(100);

		// 插入元素期间，可能会引起扩容，而导致原空间被释放
		// v.insert(v.begin(), 0);
		// v.push_back(8);

		// 给vector重新赋值，可能会引起底层容量改变
		v.assign(100, 8);

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
	else if (test_flag == 9)
	{
		int a[] = {1, 2, 3, 4};
		vector<int> v(a, a + sizeof(a) / sizeof(int));
		// 使用find查找3所在位置的iterator
		vector<int>::iterator pos = find(v.begin(), v.end(), 3);
		// 删除pos位置的数据，导致pos迭代器失效。
		v.erase(pos);
		cout << *pos << endl; // 此处会导致非法访问
		return 0;
	}
	else if (test_flag == 10)
	{
		vector<int> v{1, 2, 3, 4};
		auto it = v.begin();
		while (it != v.end())
		{
			if (*it % 2 == 0)
				it = v.erase(it);
			else
				++it;
		}
		PrintVector(v);
		return 0;
	}
	else if (test_flag == 11)
	{
		std::list<int> l1;		   //构造空的l1
		std::list<int> l2(4, 100); // 12中放4个值为100的元素

		std::list<int> l3(l2.begin(), l2.end()); // 用l2的左闭右开区间构造L3
		std::list<int> l4(l3);					 //用l3拷贝构造l4

		//以数组为迭代器区间构造l5
		int array[] = {16, 2, 77, 29};
		std::list<int> l5(array, array + sizeof(array) / sizeof(int));

		//用迭代器方式打印l5中的元素
		for (std::list<int>::iterator it = l5.begin(); it != l5.end(); it++)
			std::cout << *it << " ";
		std::cout << endl;

		// C++范围for的方式遍历
		for (auto &e : l5)
			std::cout << e << " ";

		std::cout << endl;
		return 0;
	}
	else if (test_flag == 12)
	{
		int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		list<int> l(array, array + sizeof(array) / sizeof(array[10]));
		//使用正向迭代器正向list中的元素
		for (list<int>::iterator it = l.begin(); it != l.end(); ++it)
			cout << *it << " ";
		cout << endl;

		//使用反向迭代器逆向打印list中的元素
		for (list<int>::reverse_iterator it = l.rbegin(); it != l.rend(); ++it)
			cout << *it << " ";
		cout << endl;

		return 0;
	}
	else if (test_flag == 13)
	{
		TestList1();
		TestList3();
		TestList4();
	}
	else if (test_flag == 14)
	{
		if (0)
		{
			int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
			list<int> l(array, array + sizeof(array) / sizeof(array[0]));

			auto it = l.begin();
			while (it != l.end())
			{
				// erase()函数执行后，it所指向的节点已被删除，因此it无效，在下一次使用it时，必须先给其赋值
				l.erase(it);
				++it;
			}
		}

		//改正
		{
			int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
			list<int> l(array, array + sizeof(array) / sizeof(array[0]));

			auto it = l.begin();
			while (it != l.end())
			{
				l.erase(it++); // it = l.erase(it);
			}
		}
	}
	else if (test_flag == 15)
	{
		{
			int a1 = 10, a2 = 20;
			double d1 = 10.0, d2 = 20.0;
			int a = Add(a1, a2);
			double d = Add(d1, d2);

			/*
			该语句不能通过编译，因为在编译期间，当编译器看到该实例化时，需要推演其实参类型
			通过实参a1将T推演为int，通过实参d1将T推演为double类型，但模板参数列表中只有一个T，
			编译器无法确定此处到底该将T确定为int 或者 double类型而报错
			注意：在模板中，编译器一般不会进行类型转换操作，因为一旦转化出问题，编译器就需要背黑锅
			*/
			// Add(a1, d1);

			// 此时有两种处理方式：1. 用户自己来强制转化 2. 使用显式实例化
			int c = Add(a, (int)d);
		}
		{
			int a = 10;
			double b = 20.0;

			// 显式实例化
			Add<int>(a, b);
		}
		return 0;
	}
	else if (test_flag == 16)
	{
		{
			std::deque<int> mydeque(3, 100);   // deque with 3 elements
			std::vector<int> myvector(2, 200); // vector with 2 elements

			std::stack<int> first;			 // empty stack
			std::stack<int> second(mydeque); // stack initialized to copy of deque

			std::stack<int, std::vector<int>> third; // empty stack using vector
			std::stack<int, std::vector<int>> fourth(myvector);

			std::cout << "size of first: " << first.size() << '\n';
			std::cout << "size of second: " << second.size() << '\n';
			std::cout << "size of third: " << third.size() << '\n';
			std::cout << "size of fourth: " << fourth.size() << '\n';
		}
		{
			std::stack<int> mystack;
			int sum(0);

			for (int i = 1; i <= 10; i++)
				mystack.push(i);

			while (!mystack.empty())
			{
				sum += mystack.top();
				mystack.pop();
			}

			std::cout << "total: " << sum << '\n';
		}
		{
			std::stack<int> myints;
			std::cout << "0. size: " << myints.size() << '\n';

			for (int i = 0; i < 5; i++)
				myints.push(i);
			std::cout << "1. size: " << myints.size() << '\n';

			myints.pop();
			std::cout << "2. size: " << myints.size() << '\n';
		}
		{
			std::stack<int> mystack;

			mystack.push(10);
			mystack.push(20);

			mystack.top() -= 5;

			std::cout << "mystack.top() is now " << mystack.top() << '\n';
		}
		{

			std::stack<int> mystack;

			for (int i = 0; i < 5; ++i)
				mystack.push(i);

			std::cout << "Popping out elements...";
			while (!mystack.empty())
			{
				std::cout << ' ' << mystack.top();
				mystack.pop();
			}
			std::cout << '\n';

			return 0;
		}

		return 0;
	}
	else if (test_flag == 17)
	{
		{
			std::queue<int> myqueue;
			int sum(0);

			for (int i = 1; i <= 10; i++)
				myqueue.push(i);

			while (!myqueue.empty())
			{
				sum += myqueue.front();
				myqueue.pop();
			}
			std::cout << "total: " << sum << '\n';
		}
		{
			std::queue<int> myints;
			std::cout << "0. size: " << myints.size() << '\n';

			for (int i = 0; i < 5; i++)
				myints.push(i);
			std::cout << "1. size: " << myints.size() << '\n';

			myints.pop();
			std::cout << "2. size: " << myints.size() << '\n';
		}
		{
			std::queue<int> myqueue;

			myqueue.push(77);
			myqueue.push(16);

			myqueue.front() -= myqueue.back(); // 77-16=61

			std::cout << "myqueue.front() is now " << myqueue.front() << '\n';

			return 0;
		}

		return 0;
	}
	else if (test_flag == 18)
	{
		{
			int myints[] = {10, 60, 50, 20};

			std::priority_queue<int> first;
			std::priority_queue<int> second(myints, myints + 4);
			std::priority_queue<int, std::vector<int>, std::greater<int>>
				third(myints, myints + 4);
			// using mycomparison:
			typedef std::priority_queue<int, std::vector<int>, mycomparison> mypq_type;

			mypq_type fourth;					 // less-than comparison
			mypq_type fifth(mycomparison(true)); // greater-than comparison

			return 0;
		}
		{
			std::priority_queue<int> mypq;
			int sum(0);

			for (int i = 1; i <= 10; i++)
				mypq.push(i);

			while (!mypq.empty())
			{
				sum += mypq.top();
				mypq.pop();
			}

			std::cout << "total: " << sum << '\n';
		}
		{
			std::priority_queue<int> mypq;

			mypq.push(10);
			mypq.push(20);
			mypq.push(15);

			std::cout << "mypq.top() is now " << mypq.top() << '\n';
		}
		{
			std::priority_queue<int> mypq;

			mypq.push(30);
			mypq.push(100);
			mypq.push(25);
			mypq.push(40);

			std::cout << "Popping out elements...";
			while (!mypq.empty())
			{
				std::cout << ' ' << mypq.top();
				mypq.pop();
			}
			std::cout << '\n';

			return 0;
		}
	}
	else if (test_flag == 21)
	{
		{
			std::unordered_set<std::string> first;								 // empty
			std::unordered_set<std::string> second({"red", "green", "blue"});	 // init list
			std::unordered_set<std::string> third({"orange", "pink", "yellow"}); // init list
			std::unordered_set<std::string> fourth(second);						 // copy
			std::unordered_set<std::string> fifth(cmerge(third, fourth));		 // move
			std::unordered_set<std::string> sixth(fifth.begin(), fifth.end());	 // range

			std::cout << "sixth contains:";
			for (const std::string &x : sixth)
				std::cout << " " << x;
			std::cout << std::endl;
		}
		{
			string s = "abbccdd";
			if (s.size() == 0)
				return 0;
			unordered_set<char> lookup;
			int maxStr = 0;
			int left = 0;
			for (int i = 0; i < s.size(); i++)
			{
				while (lookup.find(s[i]) != lookup.end())
				{
					lookup.erase(s[left]);
					left++;
				}
				maxStr = max(maxStr, i - left + 1);
				lookup.insert(s[i]);
			}
			// return maxStr;
		}
		{
			string str;
			while (cin >> str)
			{
				int sum = 0;
				int len = str.size();
				for (int i = len - 1; i >= 0; --i)
				{
					if (str[i] >= '0' && str[i] <= '9')
					{
						sum += (str[i] - 48) * pow(16, len - i - 1);
					}
					else if (str[i] >= 'A' && str[i] <= 'F')
					{
						sum += (str[i] - 55) * pow(16, len - i - 1);
					}
				}
				cout << sum << endl;
				// return 0;
			}
		}
	}
	else if (test_flag == 22)
	{
		{
			// calloc与malloc的区别
			// 1.参数的使用方式不同
			// 2.calloc会在返回起始地址之前，把在堆区申请的动态内存空间的每个字节都初始化为0
			int *p = (int *)malloc(10);
			int *q = (int *)calloc(10, sizeof(int));
			if (p == NULL || q == NULL)
			{
				printf("%s\n", strerror(errno));
			}
			else
			{
				for (int i = 0; i < 10; i++)
				{
					printf("%d ", *(p + i)); // 0 0 0 0 0 0 0 0 0 0
				}
				printf("\n");
				for (int i = 0; i < 10; i++)
				{
					printf("%d ", *(q + i)); // 0 0 0 0 0 0 0 0 0 0
				}
				printf("\n");
			}
			//注意要释放calloc申请的那块空间
			//还给操作系统，并把指针置为空
			free(p);
			p = NULL;
			// return 0;
		}
		{
			int n = 0;
			while (scanf("%d", &n))
			{
				int *nums = (int *)malloc(sizeof(int) * n);
				int *hash = (int *)calloc(501, sizeof(int));
				int i = 1;
				for (; i < n + 1; i++)
				{
					scanf("%d", &nums[i]);
					hash[nums[i]] += i;
					// Printhash(hash, 500);
				}
				printf("\n");
				int j = 0;

				printf("\n");
				for (i = 1; i <= 500; i++)
				{
					if (hash[i] != 0)
						printf("%d\n", i);
				}
			}
		}
	}
	else if (test_flag == 23)
	{
		if (0)
		{
			string str;
			int result = 0;
			cin >> str;
			int len = str.size();
			int *hash = (int *)calloc(128, sizeof(int));
			for (int i = 0; i < len; i++)
			{
				if (str[i] >= 0 && str[i] <= 128)
				{
					hash[str[i]] += 1;
				}
			}

			for (int i = 0; i < 128; i++)
			{
				if (hash[i] != 0)
					result++;
			}
			cout << result << endl;
			return 0;
		}
		if (0)
		{
			Jumpfloor jmpflor;
			int num;
			int result = 0;
			while (cin >> num)
			{
				result = jmpflor.jumpFloor(num);
				cout << result << endl;
			}
		}
		{
			string str;

			int result[2] = {0, 0};
			char pos[4] = {0, 0, 0, 0};

			while (getline(cin, str))
			{
				int sum = 0;
				int len = str.size();
				int sublen = 0;

				for (int i = 0; i <= len; i++)
				{
					sublen++;
					if (str[i] == ';')
					{
						string substring(str, i - (sublen - 1), sublen - 1);

						if (substring[0] != 'A' && substring[0] != 'W' && substring[0] != 'D' && substring[0] != 'S')
						{
							sublen = 0;
							continue;
						}
						for (int i = 1; i <= sublen - 2; i++)
						{
							if (substring[i] >= '0' && substring[i] <= '9')
							{
								sum += (substring[i] - '0') * pow(10, sublen - 2 - i);
							}
							else
							{
								sum = 0;
								sublen = 0;
								continue;
							}
						}
						if (substring[0] == 'A')
							result[0] -= sum;
						else if (substring[0] == 'W')
							result[1] += sum;
						else if (substring[0] == 'S')
							result[1] -= sum;
						else if (substring[0] == 'D')
							result[0] += sum;

						sublen = 0;
						sum = 0;
					}
				}
				cout << "(" << result[0] << "," << result[1] << ")" << endl;
			}
		}
	}
	else if (test_flag == 24)
	{
		if (1)
		{
			FILE *fp;
			char *name[] = {"文件1", "文件2", "文件3", "file4", "file4"};
			fp = fopen("./test.txt", "w");
			for (int i = 0; i < 5; i++)
			{
				fprintf(fp, "%s\n", name[i]);
			}
			fclose(fp);
		}
		if (0)
		{
			memoryLeak1();

			memoryLeak2();
		}
		if (0)
		{
			Test_create *test = new Test_create;

			auto_ptr<Test_create> test1(new Test_create);

			cout << "test->debug：" << test1->getDebug() << endl;
			cout << "(*test).debug：" << (*test1).getDebug() << endl;
			{
				Test_create *tmp = test1.get(); // 获取指针返回
				// Test_create *tmp = test1.release(); // 获取指针返回
				cout << "tmp->debug：" << tmp->getDebug() << endl;
			}
			{
				test1.reset();					// 释放掉智能指针托管的指针内存，并将其置NULL
				test1.reset(new Test_create()); // 释放掉智能指针托管的指针内存，并将参数指针取代之
			}

			// 调用三次构造但是调用两次析构
			{
				// 没有意义，全局变量也是一样
				auto_ptr<Test_create> *tp = new auto_ptr<Test_create>(new Test_create);
				auto_ptr<Test_create> t1(new Test_create);
				auto_ptr<Test_create> t2(new Test_create);
				t1 = t2; // 不要这样操作...
			}
		}
		if (0)
		{
			// auto_ptr 被C++11抛弃的主要原因
			auto_ptr<string> p1(new string("I'm Li Ming!"));
			auto_ptr<string> p2(new string("I'm age 22."));

			cout << "p1：" << p1.get() << endl;
			cout << "p2：" << p2.get() << endl;

			// p2赋值给p1后，首先p1会先将自己原先托管的指针释放掉，然后接收托管p2所托管的指针，
			// 然后p2所托管的指针制NULL，也就是p1托管了p2托管的指针，而p2放弃了托管。
			p1 = p2;
			cout << "p1 = p2 赋值后：" << endl;
			cout << "p1：" << p1.get() << endl;
			cout << "p2：" << p2.get() << endl;
		}
		if (0)
		{
			vector<auto_ptr<string>> vec;
			auto_ptr<string> p3(new string("I'm P3"));
			auto_ptr<string> p4(new string("I'm P4"));

			// 必须使用std::move修饰成右值，才可以进行插入容器中
			vec.push_back(std::move(p3));
			vec.push_back(std::move(p4));

			cout << "vec.at(0)：" << *vec.at(0) << endl;
			cout << "vec[1]：" << *vec[1] << endl;

			// 风险来了：
			vec[0] = vec[1]; // 如果进行赋值，问题又回到了上面一个问题中。
			cout << "vec.at(0)：" << *vec.at(0) << endl;
			cout << "vec[1]：" << *vec[1] << endl;
		}

		// auto_ptr<int[]> array(new int[5]); // 不能这样定义
		return 0;
	}
	else if (test_flag == 25)
	{
		if (0)
		{
			unique_ptr<string> p1(new string("I'm Li Ming!"));
			unique_ptr<string> p2(new string("I'm age 22."));

			cout << "p1：" << p1.get() << endl;
			cout << "p2：" << p2.get() << endl;

			// p1 = p2;				   // 禁止左值赋值
			// unique_ptr<string> p3(p2); // 禁止左值赋值构造

			unique_ptr<string> p3(std::move(p1));
			p1 = std::move(p2); // 使用move把左值转成右值就可以赋值了，效果和auto_ptr赋值一样

			cout << "p1 = p2 赋值后：" << endl;
			cout << "p1：" << p1.get() << endl;
			cout << "p2：" << p2.get() << endl;
		}

		if (0)
		{
			vector<unique_ptr<string>> vec;
			unique_ptr<string> p3(new string("I'm P3"));
			unique_ptr<string> p4(new string("I'm P4"));

			vec.push_back(std::move(p3));
			vec.push_back(std::move(p4));

			cout << "vec.at(0)：" << *vec[0] << endl;
			cout << "vec.at(0)：" << *vec.at(0) << endl;
			cout << "vec[1]：" << *vec[1] << endl;
			cout << "vec[1]：" << *vec.at(1) << endl;

			// vec[0] = vec[1];			/* 不允许直接赋值 */
			vec[0] = std::move(vec[1]); // 需要使用move修饰，使得程序员知道后果

			cout << "vec.at(0)：" << *vec.at(0) << endl;
			// cout << "vec[1]：" << *vec[1] << endl;
		}
		if (0)
		{
			// unique_ptr<T> up; 空的unique_ptr，可以指向类型为T的对象
			unique_ptr<Test> t1;

			// unique_ptr<T> up1(new T());	定义unique_ptr,同时指向类型为T的对象
			unique_ptr<Test> t2(new Test);

			// unique_ptr<T[]> up;	空的unique_ptr，可以指向类型为T[的数组对象
			unique_ptr<int[]> t3;

			// unique_ptr<T[]> up1(new T[]);	定义unique_ptr,同时指向类型为T的数组对象
			unique_ptr<int[]> t4(new int[5]);

			// unique_ptr<T, D> up();	空的unique_ptr，接受一个D类型的删除器D，使用D释放内存
			unique_ptr<Test, DestructTest> t5;

			// unique_ptr<T, D> up(new T());	定义unique_ptr,同时指向类型为T的对象，接受一个D类型的删除器D，使用删除器D来释放内存
			unique_ptr<Test, DestructTest> t6(new Test);
		}
		if (0)
		{
			unique_ptr<Test> t7(new Test);
			unique_ptr<Test> t8(new Test);
			t7 = std::move(t8); // 必须使用移动语义，结果，t7的内存释放，t8的内存交给t7管理
			t7->doSomething();

			unique_ptr<Test> t9(new Test);
			t9 = NULL;
			t9 = nullptr;
			t9.reset();

			Test *t10 = t9.release();

			t9.reset(new Test);
		}
		if (0)
		{
			int len = 0;
			int strlen = 0;
			string str;
			bool Sort_falg = false;
			cin >> len;
			cin.get();
			getline(cin, str);
			cin >> Sort_falg;

			int substrlen = 0;
			int element = 0;
			strlen = str.size();
			if (Sort_falg == 1)
			{
				priority_queue<int, vector<int>, less<int>> result;
				for (int i = 0; i < strlen + 1; i++)
				{
					if (str[i] != ' ' && i != strlen)
						substrlen++;
					else if (str[i] == ' ' || i == strlen)
					{
						string substr(str, i - substrlen, substrlen);
						int a = stoi(substr);
						result.push(a);
						substrlen = 0;
					}
				}
				strlen = str.size();

				int printsize = result.size();
				for (int i = 0; i < printsize; i++)
				{
					cout << result.top() << ' ';
					result.pop();
				}
			}
			else
			{
				priority_queue<int, vector<int>, greater<int>> result;
				for (int i = 0; i < strlen + 1; i++)
				{
					if (str[i] != ' ' && i != strlen)
						substrlen++;
					else if (str[i] == ' ' || i == strlen)
					{
						string substr(str, i - substrlen, substrlen);
						int a = stoi(substr);
						result.push(a);
						substrlen = 0;
					}
				}
				strlen = str.size();

				int printsize = result.size();
				for (int i = 0; i < printsize; i++)
				{
					cout << result.top() << ' ';
					result.pop();
				}
			}
		}
		if (0)
		{
			int num = 0;
			cin >> num;
			cin.get();
			int *hash = (int *)calloc(sizeof(int), 500);

			for (int i = 0; i < num; i++)
			{
				string substr;
				int subnum[2] = {0};
				getline(cin, substr);
				int sublen = substr.size();
				int sub_count = 0;
				int substr_count = 0;
				for (int j = 0; j < sublen + 1; j++)
				{
					if (substr[j] != ' ' && j != sublen)
						sub_count++;
					else if (substr[j] == ' ' || j == sublen)
					{
						string str(substr, j - sub_count, j);
						subnum[substr_count] = stoi(str);
						substr_count++;
						sub_count = 0;
					}
				}
				hash[subnum[0]] += subnum[1];
			}
			for (int n = 0; n <= 500; n++)
			{
				if (hash[n] != 0)
					cout << n << ' ' << hash[n] << endl;
			}
		}
		if (0)
		{
			auto_ptr<string> p1;
			string *str = new string("智能指针的内存管理陷阱");
			p1.reset(str); // p1托管str指针
			{
				auto_ptr<string> p2;
				p2.reset(str); // p2接管str指针时，会先取消p1的托管，然后再对str的托管
			}

			// 此时p1已经没有托管内容指针了，为NULL，在使用它就会内存报错！
			cout << "str：" << *p1 << endl;
		}
		if (0)
		{
			class Person
			{
			public:
				Person(int v)
				{
					this->no = v;
					cout << "构造函数 \t no = " << this->no << endl;
				}

				~Person()
				{
					cout << "析构函数 \t no = " << this->no << endl;
				}

			private:
				int no;
			};

			// 仿函数，内存删除
			class DestructPerson
			{
			public:
				void operator()(Person *pt)
				{
					cout << "DestructPerson..." << endl;
					delete pt;
				}
			};

			shared_ptr<Person> sp1;

			shared_ptr<Person> sp2(new Person(2));

			// 获取智能指针管控的共享指针的数量	use_count()：引用计数
			cout << "sp1	use_count() = " << sp1.use_count() << endl;
			cout << "sp2	use_count() = " << sp2.use_count() << endl
				 << endl;

			// 共享
			sp1 = sp2;

			cout << "sp1	use_count() = " << sp1.use_count() << endl;
			cout << "sp2	use_count() = " << sp2.use_count() << endl
				 << endl;

			shared_ptr<Person> sp3(sp1);
			cout << "sp1	use_count() = " << sp1.use_count() << endl;
			cout << "sp2	use_count() = " << sp2.use_count() << endl;
			cout << "sp3	use_count() = " << sp3.use_count() << endl
				 << endl;
		}
		if (0)
		{
			class Girl;

			class Boy
			{
			public:
				Boy()
				{
					cout << "Boy 构造函数" << endl;
				}

				~Boy()
				{
					cout << "~Boy 析构函数" << endl;
				}

				void setGirlFriend(shared_ptr<Girl> _girlFriend)
				{
					this->girlFriend = _girlFriend;
				}

			private:
				shared_ptr<Girl> girlFriend;
			};

			class Girl
			{
			public:
				Girl()
				{
					cout << "Girl 构造函数" << endl;
				}

				~Girl()
				{
					cout << "~Girl 析构函数" << endl;
				}

				void setBoyFriend(shared_ptr<Boy> _boyFriend)
				{
					this->boyFriend = _boyFriend;
				}

			private:
				shared_ptr<Boy> boyFriend;
			};

			shared_ptr<Boy> spBoy(new Boy());
			shared_ptr<Girl> spGirl(new Girl());

			// 陷阱用法
			spBoy->setGirlFriend(spGirl);
			spGirl->setBoyFriend(spBoy);
			// 此时boy和girl的引用计数都是2

			system("pause");
			return 0;
		}
	}
	else if (test_flag == 26)
	{
		if (0)
		{
			struct classcomp
			{
				bool operator()(const char &lhs, const char &rhs) const
				{
					return lhs < rhs;
				}
			};

			std::map<char, int> first;
			first['a'] = 10;
			first['b'] = 30;
			first['c'] = 50;
			first['d'] = 70;
			{
				std::map<char, int>::iterator iter = first.find('d');
				// if (iter != first.end())
				printf("first.end():%d\n", first.end());
			}
			// {
			// 	ComCodecHandleEx handle_ex = (ComCodecHandleEx)malloc(sizeof(ComCodecHandleEx));
			// 	memset(handle_ex, 0, sizeof(ComCodecHandleEx));

			// 	INSAMPLEPARAM *pNewFrame = (INSAMPLEPARAM *)malloc(sizeof(INSAMPLEPARAM));
			// 	memset(pNewFrame, 0, sizeof(INSAMPLEPARAM));
			// 	pNewFrame->pbYUV[0] = (unsigned char *)malloc(3110400);
			// 	pNewFrame->pbYUV[1] = (unsigned char *)malloc(3110400);
			// 	pNewFrame->pbYUV[2] = (unsigned char *)malloc(3110400);
			// 	char *charparam = "123";
			// 	void *input = (void *)charparam;
			// 	handle_ex->p_in_frame_list.insert(std::pair<void *, InputFrameHandle>((void *)pNewFrame->pbYUV[0], (InputFrameHandle)pNewFrame));
			// 	printf("go this pos\n");
			// }

			std::map<char, int>
				second(first.begin(), first.end());

			std::map<char, int> third(second);

			std::map<char, int, classcomp> fourth; // class as Compare

			bool (*fn_pt)(char, char) = fncomp;
			std::map<char, int, bool (*)(char, char)> fifth(fn_pt); // function pointer as Compare
		}
		if (0)
		{
			std::map<char, int> mymap;

			mymap['b'] = 100;
			mymap['a'] = 200;
			mymap['c'] = 300;

			// show content:
			for (std::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';
			std::cout << "mymap.size() is " << mymap.size() << '\n';
		}
		if (0)
		{
			int n;
			cin >> n;
			map<int, int> m;
			map<int, int>::iterator it;
			for (int i = 0; i < n; i++)
			{
				int a, b;
				cin >> a >> b;
				it = m.find(a);
				if (it != m.end())
				{
					m[a] = it->second + b;
				}
				else
				{
					m[a] = b;
				}
			}
			for (it = m.begin(); it != m.end(); it++)
				cout << it->first << " " << it->second << endl;
			return 0;
		}

		if (0)
		{
			class Solution_Tree
			{
			public:
				vector<int> levelOrder(TreeNode *root)
				{
					queue<TreeNode *> que;
					vector<int> vec;
					vector<int>::iterator it;
					que.push(root);		 //先将整个二叉树放入队列
					while (!que.empty()) //当队列非空进行循环
					{
						TreeNode *p;
						p = que.front(); //先读取队列的首元素
						que.pop();		 //弹出队列的首元素
						if (p == NULL)
							continue; //所有元素存入vec后，由于队列中存放着空指针，依然进入循环，但此时p的值为NULL，不执行下面的操作，跳出循环结束
						que.push(p->left);
						que.push(p->right);
						vec.push_back(p->val);
					}
					for (it = vec.begin(); it != vec.end(); it++)
						cout
							<< *it - 48 << ' ';

					return vec;
				}
			};

			TreeNode *T;
			T = (TreeNode *)malloc(sizeof(TreeNode));

			CreateTree(&T);
			Solution_Tree so;
			so.levelOrder(T);
			return 0;
		}
		if (0)
		{
			class Solution
			{
			public:
				bool isValid(string s)
				{
					stack<char> stk;
					for (int i = 0; i < s.size(); i++)
					{
						switch (s[i])
						{
						case '(':
						case '[':
						case '{':
							stk.push(s[i]);
							break;
						case ')':
							if (stk.empty() || stk.top() != '(')
								return false;
							stk.pop();
							break;
						case ']':
							if (stk.empty() || stk.top() != '[')
								return false;
							stk.pop();
							break;
						case '}':
							if (stk.empty() || stk.top() != '{')
								return false;
							stk.pop();
							break;
						}
					}
					return stk.empty() ? true : false;
				}
			};
			string s = "([])";
			Solution slution;
			bool result = slution.isValid(s);
			cout << result << endl;
		}
		if (0)
		{
			int num = 1, a[6] = {1, 2, 3, 4, 5};
			while (next_permutation(a, a + 5))
			{
				for (int i = 0; i < 5; i++)
					cout << a[i] << " ";
				// if (num == 5)
				// 	break;
				num++;
				cout << endl;
			}
			return 0;
		}
		if (0)
		{

			class Solution
			{
			public:
				int lengthOfLastWord(string s)
				{
					int count = 0;
					int pre_id = 0;
					for (int i = s.length() - 1; i >= 0; i--)
					{
						if (s[i] != ' ')
						{
							pre_id = i;
							break;
						}
					}
					for (int j = pre_id; j >= 0; j--)
					{
						if (s[j] != ' ')
							count++;
						else
							return count;
					}
					return count;
				}
			};
			string s = "123 asd";
			Solution computation;
			computation.lengthOfLastWord(s);
		}
		if (0)
		{
			class Solution
			{
			public:
				vector<int> plusOne(vector<int> &digits)
				{
					int len = digits.size();
					for (int i = len - 1; i >= 0; i--)
					{
						if (digits[i] != 9)
						{
							digits[i]++;
							return digits;
						}
						else
						{
							digits[i] = 0;
						}
					}
					vector<int> tmp(len + 1);
					tmp[0] = 1;
					return tmp;
				}
			};

			Solution computaion;
			vector<int> v = {9};
			computaion.plusOne(v);
		}
		if (0)
		{
			class Solution
			{
			public:
				int mySqrt(int x)
				{
					int left = 1, right = x;
					int mid = 0;
					while (left <= right)
					{
						mid = left + (right - left) / 2;
						if (mid > x / mid)
						{
							right = mid - 1;
						}
						else if (mid < x / mid)
						{
							left = mid + 1;
						}
						else
						{
							return mid;
						}
					}
					return right;
				}
			};
			Solution computaion;
			computaion.mySqrt(8);
		}
		if (0)
		{
			class Solution
			{
			public:
				vector<int> inorderTraversal(TreeNode *root)
				{
					vector<int> res;
					if (!root)
						return res;
					stack<TreeNode *> st;
					TreeNode *curr = root;
					while (curr || !st.empty())
					{
						while (curr)
						{
							st.push(curr);
							curr = curr->left;
						}
						curr = st.top();
						st.pop();
						res.push_back(curr->val);
						curr = curr->right;
					}
					return res;
				}
			};
		}

		if (0)
		{
			int a = 0;
			a |= 1;
			a |= 2;
			a |= 4;
			a |= 8;
			printf("a:%d\n", a);
		}

		if (0) //冒泡排序法
		{
			int arr[] = {1, 6, 4, 2, 9};
			vector<int> v_arr1(arr, arr + sizeof(arr) / sizeof(int));
			vector<int> v_arr2{1, 6, 4, 2, 9};
			vector<int>::iterator it;
			for (int i = 0; i < v_arr1.size(); i++)
			{
				for (int j = 0; j < v_arr1.size() - i - 1; j++)
				{
					if (v_arr1[j] > v_arr1[j + 1])
					{
						swap(v_arr1[j], v_arr1[j + 1]);
					}
				}
			}

			for (it = v_arr1.begin(); it != v_arr1.end(); ++it)
				cout << *it << endl;
			return 0;
		}
		//鸡尾酒排序法，正反向排序同时进行
		//最差时间复杂度O(n^2)
		//最优时间复杂度接近O(n)
		if (0)
		{
			int arr1[] = {2, 4, 1, 3, 8, 10};
			vector<int> v_arr11(arr1, arr1 + sizeof(arr1) / sizeof(int));
			vector<int> v_arr12{2, 4, 1, 3, 8, 10};
			vector<int>::iterator it;
			int i = 0, temp = 0;
			int low = 0, up = v_arr11.size() - 1;
			while (up > low)
			{
				for (i = up; i > low; i--)
				{
					if (v_arr11[i] > v_arr11[i - 1])
					{
						swap(v_arr11[i], v_arr11[i - 1]);
					}
				}
				low++;

				for (i = low; i < up; i++)
				{
					if (v_arr11[i + 1] > v_arr11[i])
					{
						swap(v_arr11[i + 1], v_arr11[i]);
					}
				}
				up--;
			}
			for (it = v_arr11.begin(); it != v_arr11.end(); ++it)
				cout << *it << endl;
		}

		if (0) //选择排序
		{
			int arr1[] = {2, 4, 1, 3, 8, 10};
			vector<int> v_arr11(arr1, arr1 + sizeof(arr1) / sizeof(int));
			vector<int> v_arr12{2, 4, 1, 3, 8, 10};
			vector<int>::iterator it;
			int len = v_arr11.size();
			for (int i = 0; i < len; i++)
			{
				int index = i;
				for (int j = i + 1; j < len; j++)
				{
					if (v_arr11[j] < v_arr11[index])
					{
						index = j;
					}
				}
				if (index == i)
					continue;
				else
				{
					swap(v_arr11[i], v_arr11[index]);
				}
			}
			for (it = v_arr11.begin(); it != v_arr11.end(); ++it)
				cout << *it << endl;
		}

		if (0) //插入排序
		{
			int arr1[] = {2, 4, 1, 3, 8, 10};
			vector<int> v_arr11(arr1, arr1 + sizeof(arr1) / sizeof(int));
			vector<int> v_arr12{2, 4, 1, 3, 8, 10};
			vector<int>::iterator it;
			int len = v_arr11.size();
			int i = 0, j = 0;
			int target = 0;
			for (i = 1; i < len; i++)
			{
				j = i;
				target = v_arr11[i];
				while (j > 0 && target < v_arr11[j - 1])
				{
					v_arr11[j] = v_arr11[j - 1];
					j--;
				}
				v_arr11[j] = target;
			}
			for (it = v_arr11.begin(); it != v_arr11.end(); ++it)
				cout << *it << endl;
		}

		if (0) //二分法插入排序
		{
			int arr1[] = {6, 5, 4, 3, 2, 1};
			vector<int> v_arr11(arr1, arr1 + sizeof(arr1) / sizeof(int));
			vector<int> v_arr12{2, 4, 1, 3, 8, 10};
			vector<int>::iterator it;
			int len = v_arr11.size();
			for (int i = 1; i < len; i++)
			{
				if (v_arr11[i] < v_arr11[i - 1])
				{
					int temp = v_arr11[i];
					int left = 0;
					int right = i - 1;
					while (left <= right)
					{
						int mid = (left + right) / 2;
						if (v_arr11[mid] < temp)
							left = left + 1;
						else
							right = right - 1;
					}
					for (int j = i; j > left; j--)
					{
						v_arr11[j] = v_arr11[j - 1];
					}
					v_arr11[left] = temp;
				}
			}
			for (it = v_arr11.begin(); it != v_arr11.end(); ++it)
				cout << *it << endl;
		}
		if (0) //希尔排序
		{
			int arr[] = {6, 5, 4, 3, 2, 1};
			vector<int> arr_v(arr, arr + sizeof(arr) / sizeof(int));
			vector<int>::iterator it;
			int len = arr_v.size();
			int increasement = len;
			int i, j, k;
			do
			{
				//确定分组的增量
				increasement = increasement / 3 + 1;
				for (i = 0; i < increasement; i++)
				{
					for (j = i + increasement; j < len; j += increasement)
					{
						if (arr_v[j] < arr_v[j - increasement])
						{
							int temp = arr_v[j];
							for (k = j - increasement; k >= 0 && temp < arr_v[k]; k -= increasement)
							{
								arr_v[k + increasement] = arr_v[k];
							}
							arr_v[k + increasement] = temp;
						}
					}
				}
			} while (increasement > 1);

			for (int v : arr_v)
				cout << v << endl;
		}
		if (0)
		{
			FILE *fin;
			int i, n = 0, k;
			int v[100];
			unsigned char c;
			fin = fopen("/home/code/tjh_code/tjh_test/test19/obj/bbb.txt", "r");
			while (1)
			{
				if (fscanf(fin, "%c", &c) == EOF)
					break; // 找冒号
				if (c == ':')
				{
					if (fscanf(fin, "%d", &v[n]) != 1)
						break;
					else
						n++; // 找到一个冒号读一个数
				}
			}
			fclose(fin);
			for (i = 0; i < n; i++)
				printf("%d ", v[i]);
			return 0;
		}

		if (0) //归并排序
		{
			int a[8] = {6, 5, 3, 1, 8, 7, 2, 4};
			int b[8] = {0};
			MergeSort(a, 0, 8 - 1, b); //要-1
			for (int i = 0; i < 8; ++i)
			{
				cout << b[i] << " ";
			}
			return 0;
		}
		if (0) //匿名函数和lambda
		{
			vector<int> v = {1, 2, 3, 4, 5, 6};
			auto f = [](int n) -> int
			{
				cout << n << endl;
			};

			for_each(v.begin(), v.end(), f);

			for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
			{
				f(*it);
			}

			for (int a : v)
			{
				f(a);
			}

			for (auto it = v.begin(); it != v.end(); ++it)
			{
				f(*it);
			}
		}

		if (0)
		{
			char **first;
			char second[16];

			int a = sizeof(first);
			int b = sizeof(second);
			int c = sizeof(int);

			int stop = 0;
		}
	}
	else if (test_flag == 27)
	{
		if (0)
		{
			std::map<char, int> mymap;
			std::map<char, int>::iterator it;

			mymap['a'] = 50;
			mymap['b'] = 100;
			mymap['c'] = 150;
			mymap['d'] = 200;

			it = mymap.find('k');
			if (it != mymap.end())
				mymap.erase(it);

			// print content:
			std::cout << "elements in mymap:" << '\n';
			std::cout << "a => " << mymap.find('a')->second << '\n';
			std::cout << "b => " << mymap.find('b')->second << '\n';
			std::cout << "c => " << mymap.find('c')->second << '\n';
			std::cout << "d => " << mymap.find('d')->second << '\n';
			std::cout << "end => " << mymap.end()->second << '\n';
		}

		if (0)
		{
			int a = 0;
			do
			{
				a++;
				printf("a:%d\n", a);
			} while (a == 100);
		}

		if (1)
		{
			int value = 0;
			pthread_t ps1;
			pthread_t ps2;
			pthread_t ps3;
			pthread_t ps4;
			pthread_t ps5;
			sem_init(&sem, 0, 0);
			pthread_create(&ps1, NULL, testfunc1, NULL);
			pthread_create(&ps2, NULL, testfunc2, NULL);
			pthread_create(&ps3, NULL, testfunc3, NULL);
			pthread_create(&ps3, NULL, testfunc4, NULL);
			pthread_create(&ps4, NULL, testfunc5, NULL);
			sleep(3);
			sem_getvalue(&sem, &value);	   // Ubuntu6.04
			printf("value = %d\n", value); // 0

			pthread_join(ps1, NULL);
			pthread_join(ps2, NULL);
			pthread_join(ps3, NULL);
			pthread_join(ps4, NULL);
			pthread_join(ps5, NULL);
			return 0;
		}
	}
	return 0;
}
