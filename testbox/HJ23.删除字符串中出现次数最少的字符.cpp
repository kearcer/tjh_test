#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <climits>
#include <regex>
// #include <math.h>
#include <unordered_map>

using namespace std;

int main()
{
    string s;
    unordered_map<char, int> hash;
    int minele = INT_MAX;
    while (cin >> s)
    {
        for (int i = 0; i < s.size(); i++)
        {
            hash[s[i]]++;
        }

        for (auto it : hash)
        {
            minele = min(minele, it.second);
        }

        for (int i = 0; i < s.size(); i++)
        {
            if (hash[s[i]] != minele)
            {
                printf("%c", s[i]);
            }
        }
    }
}