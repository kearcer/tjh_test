/*
 * @Author: Jiahui Tang
 * @Date: 2023-04-14 23:14:44
 * @LastEditors:
 * @LastEditTime: 2023-04-14 23:14:45
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
using namespace std;
int main()
{
    unordered_map<int, int> hash;
    int a;
    cin >> a;

    int b, c;
    for (int i = 0; i < a; i++)
    {
        cin >> b >> c;
        hash[b] += c;
    }

    vector<int> V;
    for (auto it : hash)
        V.push_back(it.first);
    sort(V.begin(), V.end());
    for (int i = 0; i < hash.size(); i++)
        cout << V[i] << " " << hash[V[i]] << endl;

    system("pause");

    return 0;
}