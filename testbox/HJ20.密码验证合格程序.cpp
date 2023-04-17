/*
 * @Author: Jiahui Tang
 * @Date: 2023-04-12 22:20:43
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-04-12 22:51:18
 * @Description:
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <climits>
#include <regex>
#include <math.h>

using namespace std;
int main()
{
    string s;
    while (cin >> s)
    {
        int size = s.size();
        if (size < 8)
        {
            printf("NG\n");
            continue;
        }
        int cnt[4] = {0, 0, 0, 0};
        for (int i = 0; i < size; i++)
        {
            if (s[i] >= 'a' && s[i] <= 'z')
                cnt[0] = 1;
            else if (s[i] >= 'A' && s[i] <= 'Z')
                cnt[1] = 1;
            else if (s[i] >= '0' && s[i] <= '9')
                cnt[2] = 1;
            else
                cnt[3] = 1;
        }

        if (cnt[0] + cnt[1] + cnt[2] + cnt[3] < 3)
        {
            printf("NG\n");
            continue;
        }

        bool flag = true;
        for (int i = 0; i < size; i++)
        {
            for (int j = i + 3; j < size; j++)
                if (s.substr(i, 3) == s.substr(j, 3))
                {
                    flag = false;
                    printf("NG\n");
                    break;
                }
            if (flag == false)
            {
                break;
            }
        }
        if (flag == true)
        {
            printf("OK\n");
        }
    }

    return 0;
}