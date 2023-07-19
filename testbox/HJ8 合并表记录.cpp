/*
 * @Author: Jiahui Tang
 * @Date: 2023-04-14 23:14:44
 * @LastEditors:
 * @LastEditTime: 2023-04-14 23:14:45
 * @Description: 这是一个用于统计输入数据的简单程序
 */
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <regex>
#include <climits>
#include <unordered_map>
using namespace std;

int main()
{
    // 创建一个无序映射容器，用于存储整数键和整数值之间的映射关系
    unordered_map<int, int> hash;
    
    // 从标准输入读取一个整数
    int a;
    cin >> a;

    int b, c;
    // 循环读取a组键值对，将键存储在b中，值存储在c中，并将键值对存储在映射容器中
    for (int i = 0; i < a; i++)
    {
        cin >> b >> c;
        hash[b] += c;
    }

    vector<int> V;
    // 遍历映射容器中的所有键，并将键存储在向量容器V中
    for (auto it : hash)
        V.push_back(it.first);

    // 对向量容器V进行排序，按键的升序排列
    sort(V.begin(), V.end());

    // 遍历向量容器V，输出键和对应的值
    for (int i = 0; i < hash.size(); i++)
        cout << V[i] << " " << hash[V[i]] << endl;

    // 暂停程序的执行，等待用户按下任意键继续
    system("pause");

    // 程序执行完毕，返回0表示成功执行
    return 0;
}
