#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <climits>
#include <regex>
#include <vector>
using namespace std;

int main()
{
    int a;
    int b;
    string s;
    vector<int> v = {};

    cin >> a;
    cin.ignore();
    getline(cin, s);
    cin >> b;
    regex pattern("[0-9]+");
    for (auto it = sregex_iterator(s.begin(), s.end(), pattern); it != sregex_iterator(); ++it)
    {
        v.push_back(stoi(it->str()));
    }
    if (b == 0)
        sort(v.begin(), v.end());
    else
        sort(v.end(), v.begin(), greater<int>());
    for (int i = 0; i < a; i++)
        printf("%d ", v[i]);
}