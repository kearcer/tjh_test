/*
 * @Author: Jiahui Tang
 * @Date: 2023-04-12 12:35:53
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-04-13 23:07:59
 * @Description:
 */
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <climits>
#include <regex>

using namespace std;

int main()
{
    string S;
    cin >> S;
    int size = S.size();
    regex pattern("[ADWS][0-9]{1,2}[;]");
    int x = 0, y = 0;

    for (auto it = sregex_iterator(S.begin(), S.end(), pattern); it != sregex_iterator(); ++it)
    {
        string S_cut = it->str();
        if (S_cut[0] == 'A')
            x -= stoi(S_cut.substr(1));
        else if (S_cut[0] == 'D')
            x += stoi(S_cut.substr(1));
        else if (S_cut[0] == 'W')
            y += stoi(S_cut.substr(1));
        else if (S_cut[0] == 'S')
            y -= stoi(S_cut.substr(1));
        else if (S_cut.find(';') == string::npos) // skip invalid strings
            continue;
    }
    printf("(%d,%d)\n", x, y);
}
