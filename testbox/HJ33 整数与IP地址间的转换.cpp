#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <climits>
#include <regex>
#include <vector>
#include <stack>
using namespace std;

int main()
{
    string s;
    string s1;
    getline(cin, s);
    // cin.ignore();
    getline(cin, s1);
    regex pattern("[0-9]+");
    vector<long long> v;
    for (auto it = sregex_iterator(s.begin(), s.end(), pattern); it != sregex_iterator(); ++it)
    {
        v.push_back(stoi(it->str()));
    }
    long long result;
    result = (v[0] << 24) | v[1] << 16 | v[2] << 8 | v[3];
    printf("%lld\n", result);

    long long data = stoll(s1);
    int v1[4] = {0, 0, 0, 0};
    v1[0] = data >> 24;
    v1[1] = (data & 0x00FF0000) >> 16;
    v1[2] = (data & 0x0000FF00) >> 8;
    v1[3] = (data & 0x000000FF);
    cout << v1[0] << '.' << v1[1] << '.' << v1[2] << '.' << v1[3] << endl;
}