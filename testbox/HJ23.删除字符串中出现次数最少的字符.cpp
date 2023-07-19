#include <stdio.h>              // 导入标准输入输出库
#include <stdlib.h>             // 导入标准库
#include <iostream>             // 导入输入输出流库
#include <string>               // 导入字符串库
#include <algorithm>            // 导入算法库，主要用于 min 函数
#include <climits>              // 导入整型变量极值定义，主要用于初始化 minele
#include <unordered_map>        // 导入哈希表库

using namespace std;            // 使用标准命名空间

int main()
{
    string s;                   // 声明字符串 s 用来存储输入
    unordered_map<char, int> hash; // 定义一个哈希表来存储每个字符及其出现的次数
    int minele = INT_MAX;       // 初始化最小元素的值为整型的最大值

    while (cin >> s)            // 在循环中接收输入的字符串
    {
        // 对字符串中的每个字符进行统计
        for (int i = 0; i < s.size(); i++)
        {
            hash[s[i]]++;       // 每当字符出现时，将其在哈希表中的对应值加一
        }

        // 在哈希表中查找出现次数最少的字符
        for (auto it : hash)
        {
            minele = min(minele, it.second);  // 更新出现次数最少的字符的次数
        }

        // 在字符串中删除出现次数最少的字符
        for (int i = 0; i < s.size(); i++)
        {
            if (hash[s[i]] != minele)         // 如果该字符的出现次数不是最小的
            {
                printf("%c", s[i]);           // 打印该字符
            }
        }
        printf("\n"); 
    }
}
