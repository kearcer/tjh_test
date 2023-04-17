/*
 * @Author: Jiahui Tang
 * @Date: 2023-04-15 13:34:08
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-04-15 20:14:40
 * @Description:
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
#include <vector>
using namespace std;

bool Is_brother(string s1, string s2)
{
    if (s1 == s2 || s1.size() != s2.size())
        return false;
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());
    return (s1 == s2);
}
int main()
{
    string s = "6 cab ad abcd cba abc bca abc 1";
    vector<string> v;
    vector<string> res_v;
    // getline(cin, s);
    regex pattern("[a-z]+");
    int size = stoi(s.substr(0));
    int index = stoi(s.substr(s.size() - 1));
    for (auto it = sregex_iterator(s.begin(), s.end(), pattern); it != sregex_iterator(); ++it)
    {
        string s_temp = it->str();
        v.push_back(s_temp);
    }
    int ele_count = v.size();
    string target = v[ele_count - 1];
    int res_count = 0;
    for (int i = 0; i < ele_count; i++)
    {
        if (Is_brother(target, v[i]))
        {
            res_v.push_back(v[i]);
        }
    }
    cout << res_v.size() << endl;
    if (index - 1 < res_v.size())
        cout << res_v[index - 1] << endl;
    return 0;
}