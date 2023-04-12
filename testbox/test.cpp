/*
 * @Author: Jiahui Tang
 * @Date: 2023-04-12 12:35:53
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-04-12 12:51:01
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
    regex pattern("[^ | !;][ADWS][0-9]{1,2}[;]");
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
    }
    printf("(%d,%d)\n", x, y);
}
// 这段代码好像会把B10A11当成A11进行计算，这是不对的，请修改
// A10;S20;W10;D30;X;A1A;B10A11;;A10;/^(;|[^;].*)[ADWS][0-9]{1,2}[;]/。其

// #include <iostream>
// #include <string>
// #include <regex>

// using namespace std;

// int main()
// {
//     string input_str;
//     cin >> input_str;
//     regex pattern("[ADWS][0-9]{1,2}");
//     int x = 0, y = 0;
//     for (auto it = sregex_iterator(input_str.begin(), input_str.end(), pattern); it != sregex_iterator(); ++it)
//     {
//         string s = it->str();
//         if (s[0] == 'A')
//         {
//             x -= stoi(s.substr(1));
//         }
//         else if (s[0] == 'D')
//         {
//             x += stoi(s.substr(1));
//         }
//         else if (s[0] == 'W')
//         {
//             y += stoi(s.substr(1));
//         }
//         else if (s[0] == 'S')
//         {
//             y -= stoi(s.substr(1));
//         }
//     }
//     cout << "(" << x << ", " << y << ")" << endl;
//     return 0;
// }