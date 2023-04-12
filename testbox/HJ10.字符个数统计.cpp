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
    string S;
    int a, b;
    cin >> S;
    int result = 0;
    int size = S.size();
    unordered_map<int, int> hash;
    for (int i = 0; i < size; i++)
    {
        hash[S[i]]++;
    }
    for (auto it : hash)
    {
        if (it.second != 0)
            result++;
    }
    printf("%d\n", result);
}