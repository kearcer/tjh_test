#include <stdlib.h> // 包含标准库的头文件
#include <stdio.h> // 包含输入输出的头文件
#include <string> // 包含字符串操作的头文件
#include <iostream> // 包含输入输出流的头文件
#include <math.h> // 包含数学函数的头文件
#include <algorithm> // 包含算法函数的头文件
#include <climits> // 包含整数类型的极限值的头文件
#include <unordered_map> // 包含无序映射的头文件
#include <vector> // 包含向量容器的头文件

using namespace std; // 使用命名空间std

int main()
{
    int a; // 声明整数变量a
    int size; // 声明整数变量size
    unordered_map<int, int> hash; // 声明一个无序映射，用于存储整数的出现次数
    vector<int> v; // 声明一个向量容器，用于存储不重复的整数
    cin >> size; // 从标准输入读取整数，赋值给变量size
    for (int i = 0; i < size; i++) // 循环读取size次
    {
        cin >> a; // 从标准输入读取整数，赋值给变量a
        hash[a]++; // 将a作为键，将其出现次数加1作为值存储到hash中
    }

    for (auto it : hash) // 遍历hash中的键值对
        v.push_back(it.first); // 将键（不重复的整数）添加到向量容器v中
    sort(v.begin(), v.end()); // 对向量容器v中的整数进行升序排序
    for (auto i : v) // 遍历向量容器v中的整数
        printf("%d\n", i); // 以整数的格式输出到标准输出

    return 0; // 返回0，表示程序成功结束
}
