/*
 * @Author: Jiahui Tang
 * @Date: 2023-04-03 14:30:29
 * @LastEditors:
 * @LastEditTime: 2023-04-03 14:30:30
 * @Description:
 */
#include <iostream>
#include <unordered_map> // 包含哈希表所需的头文件

using namespace std;

int main()
{
    unordered_map<string, int> my_map; // 创建一个键为字符串，值为整数的哈希表
    my_map["apple"] = 10;              // 在哈希表中插入键值对
    my_map["banana"] = 20;
    my_map["cherry"] = 30;

    cout << "Size of my_map: " << my_map.size() << endl;   // 输出哈希表的大小
    cout << "Value of apple: " << my_map["apple"] << endl; // 输出特定键的值

    if (my_map.find("banana") != my_map.end())
    { // 检查某个键是否在哈希表中
        cout << "banana is in the map!" << endl;
    }

    for (auto it = my_map.begin(); it != my_map.end(); it++)
    { // 迭代哈希表
        cout << it->first << ": " << it->second << endl;
    }

    return 0;
}