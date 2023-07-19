/*
 * @Author: Jiahui Tang
 * @Date: 2022-06-25 23:19:31
 * @LastEditors:
 * @LastEditTime: 2022-06-25 23:19:32
 * @Description:
 */
#include <iostream>	 //c++中标准的输入和输出流
using namespace std; // std是标准的statard的缩写
#include <vector>	 //引用vector容器必须要包含vector的头文件
#include <algorithm> //因为for_each的使用必须要包含算法的头文件
void print(int val)	 //打印输出vector容器内的每一个元素
{
	cout << val << endl;
}
void test01()
{
	vector<int> v;	 //在STL中使用哪个容器必须将容器的头文件包含进去
	v.push_back(10); //利用尾插法向容器差插入数据
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	//遍历的方式：第一种
	vector<int>::iterator itbegin = v.begin();
	// v.begin()是起始迭代器的意思
	//注意：起始迭代器指向容器中的第一个元素
	vector<int>::iterator itend = v.end();
	// v.end()是终止迭代器，指向容器中最后一个元素
	//	的下一个位置
	while (itbegin != itend)
	{
		cout << *itbegin << endl;
		//因为指向的迭代器终究是一个指针，
		//所以要进行解引用的操作
		itbegin++; //一定要注意指针要++当itbegin==itend
				   //的时候就退出循环了，就不再打印了
	}
}
void test02()
{
	//便利的第二种方式：利用for_each循环进行遍历
	vector<int> v;	 //首先创建一个容器
	v.push_back(10); //利用尾插法向容器插入数据
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}
}
void test03()
{ //便利的第三种方式，用算法进行遍历
	//注意用算法进行遍历的时候必须要包含算法的头文件
	vector<int> v;	 //首先创建一个容器
	v.push_back(10); //利用尾插法向容器差插入数据
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	for_each(v.begin(), v.end(), print);
	//他的本质上就是以for循环
	//前两个参数分别是起始容器的迭代器的位置，和结束容器，是一个区间，
	//第三个参数是一个函数名称（要在函数的外面对他进行实现）
}
int main(void)
{ //用三种不同的方式来打印出vector容器中的内置数据类型的方式
	test01();
	test02();
	test03();
	system("pause");
	// system("PAUSE")和system("pause")作用和效果一样，因为dos命令是不区分大小写的。
	//该语句是暂停的意思：等待用户信号；不然控制台程序会一闪即过，你来不及看到执行结果
	return 0; //程序正常运行返回一个0
}
/*打印内置的数据类型1.可以用for_each这个算法
2.while循环
3.for循环
*/
