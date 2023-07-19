/*
 * @Author: Jiahui Tang
 * @Date: 2023-04-14 23:33:38
 * @LastEditors:
 * @LastEditTime: 2023-04-14 23:33:38
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
int main()
{
    int count;
    cin >> count;
    vector<string> V;
    cin.ignore();
    for (int i = 0; i < count; i++)
    {
        string s;
        getline(cin, s);
        V.push_back(s);
    }

    sort(V.begin(), V.end());
    for (auto it : V)
        cout << it << endl;
    system("pause");
    return 0;
}