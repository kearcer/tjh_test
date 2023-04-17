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
    stack<char> stk;
    getline(cin, s);
    int size = s.size();
    for (int i = 0; i < size; i++)
    {
        stk.push(s[i]);
    }

    for (int i = 0; i < size; i++)
    {
        printf("%c", stk.top());
        stk.pop();
    }
}