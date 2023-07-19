#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <regex>
#include <climits>
#include <unordered_map>
#include <vector>
using namespace std;

// 判断两个字符串是否是兄弟字符串（兄弟字符串具有相同的字符集合，但字符顺序可以不同）
bool Is_brother(string s1, string s2)
{
    if (s1 == s2 || s1.size() != s2.size())
        return false;
    sort(s1.begin(), s1.end()); // 对字符串s1进行排序
    sort(s2.begin(), s2.end()); // 对字符串s2进行排序
    return (s1 == s2); // 判断排序后的字符串是否相同
}

int main()
{
    string s = "6 cab ad abcd cba abc bca abc 1";
    vector<string> v; // 存储输入的字符串序列
    vector<string> res_v; // 存储兄弟字符串序列
    // getline(cin, s); // 从标准输入中读取字符串，本例中直接使用预设字符串

    regex pattern("[a-z]+"); // 定义正则表达式，用于匹配小写字母组成的单词
    int size = stoi(s.substr(0)); // 提取字符串中的数字，表示字符串序列的长度
    int index = stoi(s.substr(s.size() - 1)); // 提取字符串中的数字，表示要输出的兄弟字符串的索引位置

    // 使用正则表达式匹配字符串中的所有单词，并将其存入向量v中
    for (auto it = sregex_iterator(s.begin(), s.end(), pattern); it != sregex_iterator(); ++it)
    {
        string s_temp = it->str(); // 提取匹配到的单词
        v.push_back(s_temp); // 将单词存入向量v中
    }

    int ele_count = v.size(); // 获取向量v中的元素个数
    string target = v[ele_count - 1]; // 获取目标字符串，即最后一个字符串
    int res_count = 0; // 存储兄弟字符串的个数

    // 遍历向量v中的每个字符串，如果与目标字符串是兄弟字符串，则存入res_v中
    for (int i = 0; i < ele_count; i++)
    {
        if (Is_brother(target, v[i]))
        {
            res_v.push_back(v[i]); // 将兄弟字符串存入向量res_v中
        }
    }

    cout << res_v.size() << endl; // 输出兄弟字符串的个数
    if (index - 1 < res_v.size())
        cout << res_v[index - 1] << endl; // 输出指定索引位置的兄弟字符串

    return 0;
}
