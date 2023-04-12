#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <climits>
#include <unordered_map>
#include <vector>

using namespace std;

int main()
{
    int a;
    int size;
    unordered_map<int, int> hash;
    vector<int> v;
    cin >> size;
    for (int i = 0; i < size; i++)
    {
        cin >> a;
        hash[a]++;
    }

    for (auto it : hash)
        v.push_back(it.first);
    sort(v.begin(), v.end());
    for (auto i : v)
        printf("%d\n", i);
}